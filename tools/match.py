#!/usr/bin/env python3
"""Compile one reconstructed function and compare its complete retail bytes."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

from compiler_diagnostics import dangerous_diagnostics
from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
TOOLCHAINS = ROOT / "config/toolchains.json"
TARGET = ROOT / "original/SLUS_207.42.rom"
TEXT_VRAM = 0x00100000
# Retail `.sdata` begins here, and the camera translation unit owns its first
# aligned block. Nothing below 0x001EC880 is small data, so this is the origin
# to fall back on when a source defines no small data of its own.
SDATA_VRAM = 0x001EC880


def run(command: list[str]) -> None:
    subprocess.run(command, cwd=ROOT, check=True)


def run_compiler(command: list[str]) -> None:
    """Run a C compiler and reject successful output with unsafe diagnostics.

    Linkers and assemblers still use :func:`run`: their warnings describe
    different constraints and must not be mistaken for C ABI defects.
    """
    result = subprocess.run(
        command,
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if result.stdout:
        print(result.stdout, end="", file=sys.stdout)
    if result.stderr:
        print(result.stderr, end="", file=sys.stderr)
    if result.returncode:
        raise subprocess.CalledProcessError(
            result.returncode,
            command,
            output=result.stdout,
            stderr=result.stderr,
        )
    dangerous = dangerous_diagnostics(result.stdout + "\n" + result.stderr)
    if dangerous:
        raise SystemExit(
            "ABI-DANGEROUS COMPILER DIAGNOSTICS: " + ", ".join(dangerous)
        )


def linux32_command(executable: str, *arguments: str) -> list[str]:
    runtime = ROOT / "tools/compilers/runtime/root/usr/lib32"
    return [
        str(runtime / "ld-linux.so.2"),
        "--library-path",
        str(runtime),
        executable,
        *arguments,
    ]


def profile_command(profile: dict[str, object], source: Path, output: Path) -> list[str]:
    compiler = str(ROOT / str(profile["compiler"]))
    flags = [str(flag) for flag in profile["flags"]]
    if profile["runner"] == "linux32-cc1":
        return linux32_command(
            compiler,
            str(source),
            *flags,
            "-o",
            str(output),
        )
    if profile["runner"] == "wibo-driver":
        return [
            str(ROOT / "tools/compilers/wibo"),
            compiler,
            *flags,
            "-S",
            str(source),
            "-o",
            str(output),
        ]
    raise SystemExit(f"unknown toolchain runner: {profile['runner']}")


def profile_object_command(
    profile: dict[str, object], source: Path, output: Path, object_flags: list[str] | None = None
) -> list[str] | None:
    """Compile and assemble with the historical driver when it is available."""
    if profile["runner"] != "wibo-driver":
        return None
    compiler = str(ROOT / str(profile["compiler"]))
    flags = [str(flag) for flag in profile["flags"]]
    return [
        str(ROOT / "tools/compilers/wibo"),
        compiler,
        *flags,
        *(object_flags or []),
        "-c",
        str(source),
        "-o",
        str(output),
    ]


def small_data_flag(object_flags: list[str] | None) -> str:
    """Recover the assembler small-data threshold from -Wa,-G object flags."""
    requested = [flag for flag in (object_flags or []) if flag.startswith("-Wa,-G")]
    return requested[-1].split(",", 1)[1] if requested else "-G8"


def assemble_with_bundled_assembler(
    profile: dict[str, object],
    source: Path,
    raw: Path,
    object_flags: list[str] | None,
) -> None:
    """Assemble driver output with the bundled PS2 assembler instead of GNU as.

    Ps2EeAs expands a small-data pseudo that lands in a branch delay slot to the
    single-instruction GP-relative form, where the bundled GNU as emits the
    two-instruction absolute macro and warns. Retail contains the former, so
    this assembler is authoritative wherever both forms appear for one symbol.
    """
    assembly = raw.with_suffix(".driver.s")
    run_compiler(
        [
            str(ROOT / "tools/compilers/wibo"),
            str(ROOT / str(profile["compiler"])),
            *[str(flag) for flag in profile["flags"]],
            "-S",
            str(source),
            "-o",
            str(assembly),
        ]
    )
    run(
        [
            str(ROOT / "tools/compilers/wibo"),
            str(ROOT / str(profile["assembler"])),
            small_data_flag(object_flags),
            "-o",
            str(raw),
            str(assembly),
        ]
    )


def compile_historical_object(
    profile: dict[str, object],
    source: Path,
    output: Path,
    object_flags: list[str] | None = None,
) -> bool:
    """Use the original driver/assembler and repair its obsolete ELF metadata."""
    raw = output.with_name(output.stem + ".historical.o")
    if profile["runner"] == "linux32-cc1" and profile.get("assembler"):
        assembly = raw.with_suffix(".driver.s")
        normalized = raw.with_suffix(".normalized.s")
        run_compiler(profile_command(profile, source, assembly))
        normalized.write_text(normalize(assembly.read_text()))
        assembler = str(ROOT / str(profile["assembler"]))
        assembler_runner = profile.get("assembler_runner")
        if assembler_runner == "linux32":
            run(
                linux32_command(
                    assembler,
                    small_data_flag(object_flags),
                    "-o",
                    str(raw),
                    str(normalized),
                )
            )
        elif assembler_runner == "wibo":
            run([
                str(ROOT / "tools/compilers/wibo"),
                assembler,
                small_data_flag(object_flags),
                "-o",
                str(raw),
                str(normalized),
            ])
        else:
            raise SystemExit(
                f"linux32 profile has unknown assembler runner: {assembler_runner!r}"
            )
    elif profile.get("assembler_runner") == "ps2eeas":
        assemble_with_bundled_assembler(profile, source, raw, object_flags)
    else:
        command = profile_object_command(profile, source, raw, object_flags)
        if command is None:
            return False
        run_compiler(command)
    run(["mipsel-linux-gnu-objcopy", "--remove-section=.mdebug", str(raw), str(output)])
    return True


def function_record(name: str) -> dict[str, object]:
    functions = json.loads(CATALOG.read_text())["functions"]
    found = [entry for entry in functions if entry["name"] == name]
    if len(found) != 1:
        raise SystemExit(f"function not found uniquely in catalog: {name}")
    return found[0]


def reconstruction_record(name: str) -> dict[str, object] | None:
    entries = json.loads((ROOT / "config/reconstructed.json").read_text())
    found = [entry for entry in entries if entry["function"] == name]
    if len(found) > 1:
        raise SystemExit(f"function duplicated in reconstruction ledger: {name}")
    return found[0] if found else None


def parse_address(value: object) -> int:
    return value if isinstance(value, int) else int(str(value), 16)


BASELINE_TEXT = ROOT / "asm-baseline/cod/text.s"
LINE_VRAM = re.compile(r"/\* [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) ")
JUMP_TABLE = re.compile(r"\bjtbl_([0-9A-Fa-f]{8})\b")
SYMBOL_ADDRESS = re.compile(r"_([0-9A-Fa-f]{8})$")


def jump_table_address(start: int, end: int) -> int | None:
    """Lowest retail jump-table address referenced inside a verification range.

    A `switch` puts its table in `.rodata`, and the compiler addresses that
    table with `%hi`/`%lo` against the section, so the immediates only match
    once the section sits where retail put it. The baseline disassembly already
    names every table after its address, so the placement is derivable without
    any new configuration.
    """
    if not BASELINE_TEXT.is_file():
        return None
    tables: list[int] = []
    for line in BASELINE_TEXT.read_text().splitlines():
        position = LINE_VRAM.search(line)
        if position is None or not start <= int(position.group(1), 16) < end:
            continue
        tables.extend(int(name, 16) for name in JUMP_TABLE.findall(line))
    return min(tables) if tables else None


SMALL_SECTIONS = {".sdata": "*(.sdata) *(.sdata.*)", ".sbss": "*(.sbss) *(.sbss.*) *(.scommon)"}


def defined_section_symbols(obj: Path, section: str) -> list[tuple[str, int, int]]:
    """Address-named symbols an object defines in `section`, as (name, offset, address)."""
    listing = subprocess.run(
        ["mipsel-linux-gnu-objdump", "-t", str(obj)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    ).stdout
    found: list[tuple[str, int, int]] = []
    for line in listing.splitlines():
        fields = line.replace("\t", " ").split()
        # objdump prints `<value> <flags> <section> <size> <name>`; the flag
        # column varies in width, so anchor on the ends rather than on it.
        if len(fields) < 4 or fields[-3] != section:
            continue
        name = fields[-1]
        named = SYMBOL_ADDRESS.search(name)
        if named:
            found.append((name, int(fields[0], 16), int(named.group(1), 16)))
    return found


def small_data_origin(obj: Path, section: str) -> tuple[int | None, list[str]]:
    """Retail origin implied by the small data an object defines.

    A `.sdata`/`.sbss` symbol is defined exactly once in the whole image, so a
    source that defines one claims the object that owns it -- the strongest
    translation-unit evidence available, because the definition cannot be moved
    elsewhere without moving the symbol. The retail address is already recorded
    in the symbol's name and the object records the offset the compiler chose
    for it inside the section, so the section's retail origin is
    `name address - section offset`. That makes the placement derivable the same
    way `jump_table_address` derives a table's, with no new configuration.

    Every defined symbol implies the same origin when the source models the
    layout correctly, so a disagreement is a finding about the source (usually a
    declared type whose alignment or size is not retail's) and is reported.
    """
    defined = defined_section_symbols(obj, section)
    if not defined:
        return None, []
    origins = {address - offset for _, offset, address in defined}
    origin = min(origins)
    notes = []
    if len(origins) > 1:
        for name, offset, address in sorted(defined, key=lambda item: item[1]):
            if origin + offset != address:
                notes.append(
                    f"{section} symbol {name} lands at 0x{origin + offset:08X}, "
                    f"not the address its name records"
                )
    return origin, notes


def linker_script(
    address: int, rodata: int | None, sdata: int, sbss: int | None = None
) -> str:
    placement = (
        f"  .rodata 0x{rodata:08X} : {{ *(.rodata) *(.rodata.*) *(.rdata) }}\n"
        if rodata is not None
        else ""
    )
    small = f"  .sdata 0x{sdata:08X} : {{ {SMALL_SECTIONS['.sdata']} }}\n"
    if sbss is not None:
        small += f"  .sbss 0x{sbss:08X} : {{ {SMALL_SECTIONS['.sbss']} }}\n"
    return f"""OUTPUT_ARCH(mips)
SECTIONS
{{
  _gp = 0x001F4870;
  . = 0x{address:08X};
  .text : {{ *(.text) *(.text.*) }}
{small}{placement}  /DISCARD/ : {{ *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }}
}}
"""


def rodata_report(linked: Path, rodata: int | None, target: bytes) -> str | None:
    """Confirm a compiled jump table equals the retail bytes it is placed on."""
    if rodata is None:
        return None
    dumped = linked.with_suffix(".rodata.bin")
    run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".rodata", str(linked), str(dumped)])
    produced = dumped.read_bytes()
    if not produced:
        return None
    offset = rodata - TEXT_VRAM
    expected = target[offset : offset + len(produced)]
    if produced == expected:
        return f"jump table at 0x{rodata:08X}: {len(produced)} bytes MATCH"
    return f"jump table at 0x{rodata:08X}: {compare(expected, produced, verbose=False)}"


def write_derived_symbols(obj: Path, output: Path) -> None:
    """Resolve provisional address-named externs without target-byte input."""
    result = subprocess.run(
        ["mipsel-linux-gnu-nm", "-u", str(obj)],
        cwd=ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    definitions: list[str] = []
    for line in result.stdout.splitlines():
        name = line.split()[-1]
        match = SYMBOL_ADDRESS.search(name)
        if match:
            definitions.append(f"{name} = 0x{match.group(1)};")
    output.write_text("\n".join(sorted(set(definitions))) + "\n")


def words(data: bytes) -> list[str]:
    complete = len(data) // 4 * 4
    result = [f"{word:08X}" for (word,) in struct.iter_unpack("<I", data[:complete])]
    if complete != len(data):
        result.append(data[complete:].hex().upper())
    return result


def compare(expected: bytes, actual: bytes, verbose: bool = True) -> str:
    if expected == actual:
        return "MATCH"
    limit = min(len(expected), len(actual))
    offset = next((i for i in range(limit) if expected[i] != actual[i]), limit)
    if offset == limit and len(expected) != len(actual):
        detail = f"size expected {len(expected)}, actual {len(actual)}"
    else:
        detail = f"first byte +0x{offset:X}: expected {expected[offset]:02X}, actual {actual[offset]:02X}"
    summary = f"MISMATCH ({detail})"
    if not verbose:
        return summary
    return (
        f"{summary}\n"
        f"  expected words: {' '.join(words(expected))}\n"
        f"  actual words:   {' '.join(words(actual))}"
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function")
    parser.add_argument("--profile", action="append", help="profile name; repeatable (default: all)")
    parser.add_argument("--source", type=Path, help="default: src/game/<function>.c")
    parser.add_argument("--range-start", type=lambda value: int(value, 0))
    parser.add_argument("--range-end", type=lambda value: int(value, 0))
    parser.add_argument("--object-flag", action="append", default=[])
    parser.add_argument(
        "--rodata-start",
        type=lambda value: int(value, 0),
        help="place compiled .rodata here; default: the range's lowest jtbl_ address",
    )
    parser.add_argument("--no-rodata", action="store_true", help="ignore any derived jump table")
    parser.add_argument(
        "--sdata-start",
        type=lambda value: int(value, 0),
        help="place compiled .sdata here; default: derived from the D_ symbols the source defines",
    )
    parser.add_argument(
        "--sbss-start",
        type=lambda value: int(value, 0),
        help="place compiled .sbss here; default: derived from the D_ symbols the source defines",
    )
    parser.add_argument("--quiet", action="store_true", help="omit complete word dumps on mismatch")
    args = parser.parse_args()

    record = function_record(args.function)
    reconstructed = reconstruction_record(args.function)
    function_address = parse_address(record["address"])
    function_end = function_address + int(record["size"])
    address = args.range_start
    if address is None:
        address = parse_address(reconstructed.get("unit_start", record["address"])) if reconstructed else function_address
    end = args.range_end
    if end is None:
        end = parse_address(reconstructed.get("unit_end", function_end)) if reconstructed else function_end
    if address > function_address or end < function_end or end <= address:
        raise SystemExit("verification range must contain the requested function")
    size = end - address
    if args.source:
        source = ROOT / args.source
    elif reconstructed:
        source = ROOT / str(reconstructed["source"])
    else:
        source = ROOT / "src/game" / f"{args.function}.c"
    if not source.is_file():
        raise SystemExit(f"missing source: {source}")

    object_flags = args.object_flag
    if not object_flags and reconstructed:
        object_flags = [str(flag) for flag in reconstructed.get("object_flags", [])]

    rodata = args.rodata_start
    if rodata is None and reconstructed and reconstructed.get("rodata_start"):
        rodata = parse_address(reconstructed["rodata_start"])
    if rodata is None:
        rodata = jump_table_address(address, end)
    if args.no_rodata:
        rodata = None

    sdata = args.sdata_start
    if sdata is None and reconstructed and reconstructed.get("sdata_start"):
        sdata = parse_address(reconstructed["sdata_start"])
    sbss = args.sbss_start
    if sbss is None and reconstructed and reconstructed.get("sbss_start"):
        sbss = parse_address(reconstructed["sbss_start"])

    configuration = json.loads(TOOLCHAINS.read_text())
    profiles = configuration["profiles"]
    requested = args.profile or (
        [str(reconstructed["build_profile"])] if reconstructed else list(profiles)
    )
    unknown = sorted(set(requested) - set(profiles))
    if unknown:
        raise SystemExit("unknown profiles: " + ", ".join(unknown))

    target = TARGET.read_bytes()
    target_offset = address - TEXT_VRAM
    expected = target[target_offset : target_offset + size]
    if len(expected) != size:
        raise SystemExit("function range is outside the retail load image")

    matched: list[str] = []
    for profile_name in requested:
        profile = profiles[profile_name]
        # Two comparisons of one function under one profile but different
        # object flags, ranges or section origins are different experiments and
        # must not share a directory: a parallel sweep would otherwise read a
        # sibling's linked output and report the wrong answer for the flags it
        # thinks it tested.
        variant = hashlib.sha256(
            repr(
                (
                    str(source),
                    tuple(object_flags),
                    address,
                    end,
                    rodata,
                    sdata_origin if "sdata_origin" in dir() else None,
                )
            ).encode()
        ).hexdigest()[:12]
        work = ROOT / "build/match" / args.function / f"{profile_name}.{variant}"
        work.mkdir(parents=True, exist_ok=True)
        assembly = work / "compiled.s"
        normalized = work / "compiled.normalized.s"
        obj = work / "compiled.o"
        linked = work / "compiled.elf"
        binary = work / "compiled.bin"
        script = work / "function.ld"
        derived = work / "derived_symbols.ld"

        run_compiler(profile_command(profile, source, assembly))
        normalized.write_text(normalize(assembly.read_text()))
        if not compile_historical_object(profile, source, obj, object_flags):
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
        notes: list[str] = []
        placement: dict[str, int | None] = {".sdata": sdata, ".sbss": sbss}
        for section in SMALL_SECTIONS:
            if placement[section] is not None:
                continue
            derived_origin, disagreements = small_data_origin(obj, section)
            placement[section] = derived_origin
            notes.extend(disagreements)
            if derived_origin is not None:
                notes.append(f"{section} placed at 0x{derived_origin:08X} (derived)")
        script.write_text(
            linker_script(
                address,
                rodata,
                placement[".sdata"] if placement[".sdata"] is not None else SDATA_VRAM,
                placement[".sbss"],
            )
        )
        write_derived_symbols(obj, derived)
        run(
            [
                "mipsel-linux-gnu-ld",
                "-EL",
                "-m",
                "elf32ltsmip",
                "--no-check-sections",
                "-T",
                str(script),
                "-T",
                str(derived),
                "-T",
                "build/undefined_funcs_auto.txt",
                "-T",
                "build/undefined_syms_auto.txt",
                "-o",
                str(linked),
                str(obj),
            ]
        )
        run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", str(linked), str(binary)])
        actual = binary.read_bytes()
        result = compare(expected, actual, verbose=not args.quiet)
        print(f"{profile_name}: {result}")
        table = rodata_report(linked, rodata, target)
        if table:
            print(f"  {table}")
        for note in notes:
            print(f"  {note}")
        if result == "MATCH":
            matched.append(profile_name)

    print(f"verified {len(matched)} / {len(requested)} requested profiles")
    return 0 if matched else 1


if __name__ == "__main__":
    raise SystemExit(main())
