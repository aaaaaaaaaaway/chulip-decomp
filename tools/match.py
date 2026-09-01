#!/usr/bin/env python3
"""Compile one reconstructed function and compare its complete retail bytes."""

from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
from pathlib import Path

from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
TOOLCHAINS = ROOT / "config/toolchains.json"
TARGET = ROOT / "original/SLUS_207.42.rom"
TEXT_VRAM = 0x00100000


def run(command: list[str]) -> None:
    subprocess.run(command, cwd=ROOT, check=True)


def profile_command(profile: dict[str, object], source: Path, output: Path) -> list[str]:
    compiler = str(ROOT / str(profile["compiler"]))
    flags = [str(flag) for flag in profile["flags"]]
    if profile["runner"] == "linux32-cc1":
        runtime = ROOT / "tools/compilers/runtime/root/usr/lib32"
        return [
            str(runtime / "ld-linux.so.2"),
            "--library-path",
            str(runtime),
            compiler,
            str(source),
            *flags,
            "-o",
            str(output),
        ]
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
    run(
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
        run(profile_command(profile, source, assembly))
        normalized.write_text(normalize(assembly.read_text()))
        run(
            [
                str(ROOT / "tools/compilers/wibo"),
                str(ROOT / str(profile["assembler"])),
                small_data_flag(object_flags),
                "-o",
                str(raw),
                str(normalized),
            ]
        )
    elif profile.get("assembler_runner") == "ps2eeas":
        assemble_with_bundled_assembler(profile, source, raw, object_flags)
    else:
        command = profile_object_command(profile, source, raw, object_flags)
        if command is None:
            return False
        run(command)
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


def linker_script(address: int) -> str:
    return f"""OUTPUT_ARCH(mips)
SECTIONS
{{
  _gp = 0x001F4870;
  . = 0x{address:08X};
  .text : {{ *(.text) *(.text.*) }}
  .sdata 0x001EC880 : {{ *(.sdata) *(.sdata.*) }}
  /DISCARD/ : {{ *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.gnu.attributes) }}
}}
"""


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
        match = re.search(r"_([0-9A-Fa-f]{8})$", name)
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
        work = ROOT / "build/match" / args.function / profile_name
        work.mkdir(parents=True, exist_ok=True)
        assembly = work / "compiled.s"
        normalized = work / "compiled.normalized.s"
        obj = work / "compiled.o"
        linked = work / "compiled.elf"
        binary = work / "compiled.bin"
        script = work / "function.ld"
        derived = work / "derived_symbols.ld"

        run(profile_command(profile, source, assembly))
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
        script.write_text(linker_script(address))
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
        if result == "MATCH":
            matched.append(profile_name)

    print(f"verified {len(matched)} / {len(requested)} requested profiles")
    return 0 if matched else 1


if __name__ == "__main__":
    raise SystemExit(main())
