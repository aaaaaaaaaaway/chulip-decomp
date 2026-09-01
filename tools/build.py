#!/usr/bin/env python3
"""Build and byte-verify the current source-plus-assembly reconstruction."""

from __future__ import annotations

import hashlib
import json
import re
import struct
import subprocess
from pathlib import Path

from match import (
    TEXT_VRAM,
    compile_historical_object,
    jump_table_address,
    parse_address,
    profile_command,
    run_compiler,
)
from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
EXPECTED_SHA256 = "77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876"


def run(command: list[str]) -> None:
    subprocess.run(command, cwd=ROOT, check=True)


ADDRESS_SUFFIX = re.compile(r"_([0-9A-Fa-f]{8})$")
BRANCH_LABEL = re.compile(r"^\.L([0-9A-Fa-f]{8})$")
RELOCATION_SECTION = re.compile(r"^Relocation section '(\S+)'")


def data_referenced_labels(obj: Path) -> set[str]:
    """Branch labels this object reaches from data rather than from code.

    A disassembled `.rodata` blob holds a `switch` table whose entries relocate
    against the labels of the function the table belongs to. Those are the only
    references that may be answered from the label's own name, and the test is
    the relocation section they live in, not where the object sits on disk.
    """
    listing = subprocess.run(
        ["mipsel-linux-gnu-readelf", "-rW", str(obj)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    labels: set[str] = set()
    from_data = False
    for line in listing.splitlines():
        section = RELOCATION_SECTION.match(line)
        if section:
            from_data = not section.group(1).startswith(".rel.text")
            continue
        if not from_data:
            continue
        fields = line.split()
        if len(fields) >= 5 and BRANCH_LABEL.match(fields[-1]):
            labels.add(fields[-1])
    return labels


def symbols(obj: Path) -> tuple[set[str], set[str]]:
    """Defined and undefined symbol names in one object.

    `--special-syms` is required: GNU nm hides `.L` local labels by default, so
    without it the branch labels a data blob still needs look like nothing at
    all and the link fails with unresolved references instead.
    """
    listing = subprocess.run(
        ["mipsel-linux-gnu-nm", "--special-syms", str(obj)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    defined: set[str] = set()
    undefined: set[str] = set()
    for line in listing.splitlines():
        fields = line.split()
        if len(fields) < 2:
            continue
        kind, name = fields[-2], fields[-1]
        (undefined if kind == "U" else defined).add(name)
    return defined, undefined


def derived_symbols(objects: list[Path], provided: list[Path], output: Path) -> None:
    """Define address-named symbols that nothing in the link provides.

    A source file may legitimately name one address twice, because the retail
    assembler expands a small-data pseudo GP-relatively in a delay slot and
    absolutely elsewhere. The isolated verifier already resolves any symbol
    whose name ends in an eight-digit address; the whole-image link needs the
    same rule for the aliases that only C sources introduce.

    `.LXXXXXXXX` branch labels get a separate, deliberately narrow rule. Only a
    reference from a data relocation may claim one: a disassembled `.rodata`
    blob reaches a `switch` table's targets by label, and those labels stop
    being defined the moment the function around them becomes C. Scoping the
    rule to data references keeps it from quietly supplying a label that a text
    object should have defined, and `check_branch_labels` then proves after the
    link that every such label -- whoever defined it -- sits at the address its
    own name records, so the resolution is a function of the label name and of
    nothing else.
    """
    defined: set[str] = set()
    undefined: set[str] = set()
    from_data: set[str] = set()
    for obj in objects:
        found, missing = symbols(obj)
        defined |= found
        undefined |= missing
        if any(BRANCH_LABEL.match(name) for name in missing):
            from_data |= data_referenced_labels(obj)
    already = set()
    for script in provided:
        for line in script.read_text().splitlines():
            head = line.split("=", 1)[0].strip()
            if head:
                already.add(head)
    definitions = {
        name: ADDRESS_SUFFIX.search(name).group(1)
        for name in undefined - defined - already
        if ADDRESS_SUFFIX.search(name)
    }
    definitions.update(
        {
            name: BRANCH_LABEL.match(name).group(1)
            for name in from_data - defined - already
            if BRANCH_LABEL.match(name)
        }
    )
    output.write_text(
        "\n".join(f"{name} = 0x{address};" for name, address in sorted(definitions.items()))
        + "\n"
    )


def check_branch_labels(linked: Path) -> int:
    """Prove every `.LXXXXXXXX` in the link sits at the address it is named for.

    Whether a label comes from an assembly object or from `derived_symbols`
    depends on how sources happen to be grouped into translation units. This
    makes that irrelevant: both spellings must agree with the name, so no
    consolidation can change what a label resolves to without failing here.
    """
    listing = subprocess.run(
        ["mipsel-linux-gnu-nm", "--special-syms", str(linked)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    checked = 0
    for line in listing.splitlines():
        fields = line.split()
        if len(fields) != 3:
            continue
        value, _, name = fields
        named = BRANCH_LABEL.match(name)
        if not named:
            continue
        checked += 1
        if int(value, 16) != int(named.group(1), 16):
            raise SystemExit(
                f"branch label {name} resolved to 0x{int(value, 16):08X}, "
                "not the address its name records"
            )
    return checked


def check_ledger_agrees(linker: str, reconstructed: list[dict[str, object]]) -> None:
    """Refuse to link a generated script and a ledger from different generations.

    `build/chulip.us.ld` comes from `config/splat.us.yaml` via configure.py and
    the source list comes from `config/reconstructed.json`. Nothing tied the two
    together, so a consolidation pass that reached one before the other silently
    dropped an object from the link and moved every address after it. Every
    byte-level check downstream then reports that shift as its own failure.
    """
    listed = set(re.findall(r"build/(src/\S+?\.o)\(\.text\*\)", linker))
    expected = {
        "src/" + Path(str(entry["source"])).relative_to("src").with_suffix(".o").as_posix()
        for entry in reconstructed
    }
    if listed != expected:
        raise SystemExit(
            "generated linker script and reconstruction ledger disagree; "
            "re-run configure.py --split. "
            f"script only: {sorted(listed - expected)[:4]}; "
            f"ledger only: {sorted(expected - listed)[:4]}"
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
            f"    {section_name(obj)} 0x{address:08X} (INFO) : "
            f"{{ {relative}(.rodata*) }}\n"
        )
    marker = "    /DISCARD/ :"
    if marker not in linker:
        raise SystemExit("unexpected generated linker script: no discard rule")
    return linker.replace(marker, "".join(pinned) + "\n" + marker, 1)


def extend_bss_to_memory_end(linker: str, memory_end: int) -> str:
    """Retain the target PT_LOAD zero-fill extent after the generated BSS."""
    marker = "        cod_BSS_END = .;"
    if linker.count(marker) != 1:
        raise SystemExit("unexpected generated BSS linker section end")
    return linker.replace(
        marker,
        f"        . = 0x{memory_end:08X};\n{marker}",
        1,
    )


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
        expected = target[offset : offset + len(produced)]
        if produced != expected:
            raise SystemExit(
                f"jump table mismatch for {obj.relative_to(ROOT)} at 0x{address:08X}: "
                + first_difference(expected, produced)
                + uniform_shift(expected, produced)
            )


def uniform_shift(expected: bytes, produced: bytes) -> str:
    """Name the usual cause when every table entry is wrong by the same amount."""
    if len(expected) != len(produced) or len(produced) % 4:
        return ""
    deltas = {
        after - before
        for (before,), (after,) in zip(
            struct.iter_unpack("<I", expected), struct.iter_unpack("<I", produced)
        )
    }
    if len(deltas) != 1:
        return ""
    return (
        f"; every entry is offset by {deltas.pop():+d}, so the object's text did not"
        " land at its retail address -- this is a layout fault, not a table fault"
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
    check_ledger_agrees(generated_linker, reconstructed)
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
        run_compiler(profile_command(profile, source, generated))
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
    elf_config = json.loads((ROOT / "config/elf.json").read_text())
    load = elf_config["load_segment"]
    memory_end = int(load["vram"], 0) + int(load["memory_size"], 0)
    linker = extend_bss_to_memory_end(linker, memory_end)
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
    actual = image.read_bytes()
    digest = hashlib.sha256(actual).hexdigest()
    if actual != expected or digest != EXPECTED_SHA256:
        raise SystemExit(f"FULL IMAGE MISMATCH: {first_difference(expected, actual)}; sha256 {digest}")
    # Only once the image is proven can a table disagreement mean the table.
    labels = check_branch_labels(linked)
    verify_jump_tables(linked, jump_tables, expected)

    matched = json.loads((ROOT / "config/matched.json").read_text())
    print(f"FULL IMAGE MATCH: {len(actual)} bytes")
    print(f"sha256: {digest}")
    print(f"source-reconstructed functions in build: {len(reconstructed)}")
    print(f"compiled jump tables pinned at their retail addresses: {len(jump_tables)}")
    print(f"branch labels proven to sit at their named address: {labels}")
    print(f"exact matching functions: {len(matched)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
