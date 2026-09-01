#!/usr/bin/env python3
"""Build and byte-verify the current source-plus-assembly reconstruction."""

from __future__ import annotations

import hashlib
import json
import re
import subprocess
from pathlib import Path

from match import (
    TEXT_VRAM,
    compile_historical_object,
    jump_table_address,
    parse_address,
    profile_command,
)
from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
EXPECTED_SHA256 = "77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876"


def run(command: list[str]) -> None:
    subprocess.run(command, cwd=ROOT, check=True)


ADDRESS_SUFFIX = re.compile(r"(?:_|^\.L)([0-9A-Fa-f]{8})$")


def derived_symbols(objects: list[Path], provided: list[Path], output: Path) -> None:
    """Define address-named symbols that nothing in the link provides.

    A source file may legitimately name one address twice, because the retail
    assembler expands a small-data pseudo GP-relatively in a delay slot and
    absolutely elsewhere. The isolated verifier already resolves any symbol
    whose name ends in an eight-digit address; the whole-image link needs the
    same rule for the aliases that only C sources introduce.

    The same rule covers `.LXXXXXXXX` branch labels. The disassembled `.rodata`
    blob reaches a `switch` table's targets by label, and those labels stop
    being defined the moment the function around them becomes C, so the blob
    needs the address its own label name already records.
    """
    defined: set[str] = set()
    undefined: set[str] = set()
    for obj in objects:
        listing = subprocess.run(
            ["mipsel-linux-gnu-nm", "--special-syms", str(obj)],
            cwd=ROOT,
            check=True,
            capture_output=True,
            text=True,
        ).stdout
        for line in listing.splitlines():
            fields = line.split()
            if len(fields) < 2:
                continue
            kind, name = fields[-2], fields[-1]
            (undefined if kind == "U" else defined).add(name)
    already = set()
    for script in provided:
        for line in script.read_text().splitlines():
            head = line.split("=", 1)[0].strip()
            if head:
                already.add(head)
    missing = sorted(
        name
        for name in undefined - defined - already
        if ADDRESS_SUFFIX.search(name)
    )
    output.write_text(
        "\n".join(
            f"{name} = 0x{ADDRESS_SUFFIX.search(name).group(1)};" for name in missing
        )
        + "\n"
    )


def assemble(source: Path, obj: Path) -> None:
    normalized = ROOT / "build/normalized" / source.relative_to(ROOT)
    normalized.parent.mkdir(parents=True, exist_ok=True)
    normalized.write_text(normalize(source.read_text()))
    obj.parent.mkdir(parents=True, exist_ok=True)
    run(
        [
            "mipsel-linux-gnu-as",
            "-EL",
            "-march=r5900",
            "-mabi=eabi",
            "-no-pad-sections",
            "-Iinclude",
            "-o",
            str(obj),
            str(normalized),
        ]
    )


def unit_range(entries: list[dict[str, object]], catalog: dict[str, dict[str, object]]) -> tuple[int, int]:
    """Retail address span a source file is responsible for."""
    starts: list[int] = []
    ends: list[int] = []
    for entry in entries:
        record = catalog[str(entry["function"])]
        address = parse_address(record["address"])
        starts.append(parse_address(entry.get("unit_start", address)))
        ends.append(parse_address(entry.get("unit_end", address + int(record["size"]))))
    return min(starts), max(ends)


def has_rodata(obj: Path) -> bool:
    listing = subprocess.run(
        ["mipsel-linux-gnu-size", "-A", str(obj)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    for line in listing.splitlines():
        fields = line.split()
        if len(fields) >= 2 and fields[0] == ".rodata":
            return int(fields[1]) > 0
    return False


def section_name(obj: Path) -> str:
    return ".jtbl_" + obj.stem.replace(".", "_")


def pin_jump_tables(linker: str, tables: dict[Path, int]) -> str:
    """Give every compiled `switch` table the retail address retail gave it.

    GCC puts a jump table in `.rodata` and reaches it with `%hi`/`%lo`, so the
    immediates in `.text` are only retail's once the table sits where retail put
    it. The bytes themselves still come from the disassembled `.rodata` blob, so
    the table is pinned in its own output section outside `.cod`: the addresses
    resolve, nothing in `.cod` moves, and `build_jump_tables` then proves the
    compiled table is byte-identical to the retail one it was pinned onto.
    """
    if not tables:
        return linker
    pinned = []
    for obj, address in sorted(tables.items(), key=lambda item: item[1]):
        relative = obj.relative_to(ROOT).as_posix()
        listed = f"        {relative}(.rodata*);\n"
        if listed not in linker:
            raise SystemExit(f"generated linker script does not place {relative} rodata")
        linker = linker.replace(listed, "")
        pinned.append(
            f"    {section_name(obj)} 0x{address:08X} : {{ {relative}(.rodata*) }}\n"
        )
    marker = "    /DISCARD/ :"
    if marker not in linker:
        raise SystemExit("unexpected generated linker script: no discard rule")
    return linker.replace(marker, "".join(pinned) + "\n" + marker, 1)


def verify_jump_tables(linked: Path, tables: dict[Path, int], target: bytes) -> None:
    for obj, address in sorted(tables.items(), key=lambda item: item[1]):
        dumped = linked.with_suffix(f".{section_name(obj)}.bin")
        run(
            [
                "mipsel-linux-gnu-objcopy",
                "-O",
                "binary",
                "-j",
                section_name(obj),
                str(linked),
                str(dumped),
            ]
        )
        produced = dumped.read_bytes()
        offset = address - TEXT_VRAM
        if produced != target[offset : offset + len(produced)]:
            raise SystemExit(
                f"jump table mismatch for {obj.relative_to(ROOT)} at 0x{address:08X}: "
                + first_difference(target[offset : offset + len(produced)], produced)
            )


def first_difference(expected: bytes, actual: bytes) -> str:
    limit = min(len(expected), len(actual))
    for offset in range(limit):
        if expected[offset] != actual[offset]:
            return f"payload +0x{offset:X}: expected {expected[offset]:02X}, got {actual[offset]:02X}"
    return f"size differs: expected {len(expected)}, got {len(actual)}"


def main() -> int:
    toolchains = json.loads((ROOT / "config/toolchains.json").read_text())["profiles"]
    reconstructed = json.loads((ROOT / "config/reconstructed.json").read_text())

    generated_linker = (ROOT / "build/chulip.us.ld").read_text()
    object_paths = sorted(set(re.findall(r"build/asm/([^\s(]+\.o)", generated_linker)))
    assembly_sources = [ROOT / "asm" / Path(path).with_suffix(".s") for path in object_paths]
    objects: list[Path] = []
    for source in assembly_sources:
        if not source.is_file():
            raise SystemExit(f"missing generated input: {source.relative_to(ROOT)}; run configure.py --split")
        relative = source.relative_to(ROOT / "asm")
        obj = ROOT / "build/asm" / relative.with_suffix(".o")
        assemble(source, obj)
        objects.append(obj)

    source_entries: dict[str, list[dict[str, object]]] = {}

    for entry in reconstructed:
        source_entries.setdefault(str(entry["source"]), []).append(entry)

    catalog = {
        str(record["name"]): record
        for record in json.loads((ROOT / "config/functions.json").read_text())["functions"]
    }
    jump_tables: dict[Path, int] = {}

    for source_name, entries in source_entries.items():
        source = ROOT / source_name
        profile_names = {str(entry["build_profile"]) for entry in entries}
        object_flag_sets = {
            tuple(str(flag) for flag in entry.get("object_flags", [])) for entry in entries
        }
        if len(profile_names) != 1 or len(object_flag_sets) != 1:
            functions = ", ".join(str(entry["function"]) for entry in entries)
            raise SystemExit(f"inconsistent shared translation-unit settings: {functions}")
        profile = toolchains[profile_names.pop()]
        object_flags = list(object_flag_sets.pop())
        generated = ROOT / "build/compiled" / Path(source_name).with_suffix(".s")
        generated.parent.mkdir(parents=True, exist_ok=True)
        run(profile_command(profile, source, generated))
        obj = ROOT / "build" / Path(source_name).with_suffix(".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        if not compile_historical_object(profile, source, obj, object_flags):
            assemble(generated, obj)
        objects.append(obj)
        if has_rodata(obj):
            table = jump_table_address(*unit_range(entries, catalog))
            if table is None:
                raise SystemExit(f"{source_name} emits rodata with no retail jump table to pin it on")
            jump_tables[obj] = table

    output = ROOT / "build/current"
    output.mkdir(parents=True, exist_ok=True)
    bss_header = ".cod_bss (NOLOAD) :"
    if generated_linker.count(bss_header) != 1:
        raise SystemExit("unexpected generated BSS linker section")
    linker = generated_linker.replace(bss_header, ".cod_bss 0x001ED080 (NOLOAD) :")
    linker = pin_jump_tables(linker, jump_tables)
    linker_path = output / "chulip.us.ld"
    linker_path.write_text(linker)
    derived = output / "derived_syms.ld"
    derived_symbols(
        objects,
        [ROOT / "build/undefined_funcs_auto.txt", ROOT / "build/undefined_syms_auto.txt"],
        derived,
    )
    linked = output / "chulip.us.elf"
    run(
        [
            "mipsel-linux-gnu-ld",
            "-EL",
            "-m",
            "elf32ltsmip",
            "--no-check-sections",
            "-e",
            "_start",
            "-T",
            str(linker_path),
            "-T",
            "build/undefined_funcs_auto.txt",
            "-T",
            "build/undefined_syms_auto.txt",
            "-T",
            str(derived),
            "-o",
            str(linked),
        ]
    )
    image = output / "chulip.us.rom"
    run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".cod", str(linked), str(image)])

    expected = (ROOT / "original/SLUS_207.42.rom").read_bytes()
    verify_jump_tables(linked, jump_tables, expected)
    actual = image.read_bytes()
    digest = hashlib.sha256(actual).hexdigest()
    if actual != expected or digest != EXPECTED_SHA256:
        raise SystemExit(f"FULL IMAGE MISMATCH: {first_difference(expected, actual)}; sha256 {digest}")

    matched = json.loads((ROOT / "config/matched.json").read_text())
    print(f"FULL IMAGE MATCH: {len(actual)} bytes")
    print(f"sha256: {digest}")
    print(f"source-reconstructed functions in build: {len(reconstructed)}")
    print(f"compiled jump tables pinned at their retail addresses: {len(jump_tables)}")
    print(f"exact matching functions: {len(matched)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
