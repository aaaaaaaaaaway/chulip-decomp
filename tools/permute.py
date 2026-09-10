#!/usr/bin/env python3
"""Prepare a decomp-permuter directory using the historical compile adapter.

Source variations can change register allocation and instruction scheduling.
Every output still needs semantic review and complete byte verification before
promotion. The optional direct-call target removes symbolic-call scoring noise
only after its linked bytes reproduce the full selected retail range.

This tool prepares files without running a search or vendoring decomp-permuter.
"""

from __future__ import annotations

import argparse
import json
import shutil
import struct
import subprocess
import sys
from pathlib import Path

import match

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
RECONSTRUCTED = ROOT / "config/reconstructed.json"
TARGET = ROOT / "original/SLUS_207.42.rom"
TEXT_VRAM = 0x00100000
DEFAULT_ROOT = ROOT / "work/permuter"


def catalog_entry(function: str) -> dict[str, object]:
    for entry in json.loads(CATALOG.read_text())["functions"]:
        if entry["name"] == function:
            return entry
    raise SystemExit(f"unknown function: {function}")


def ledger_entry(function: str) -> dict[str, object] | None:
    for entry in json.loads(RECONSTRUCTED.read_text()):
        if entry["function"] == function:
            return entry
    return None


def verified_candidate(function: str) -> dict[str, object] | None:
    """The best campaign candidate for a function nobody has landed yet."""
    directory = ROOT / "work/campaign/verified"
    if not directory.is_dir():
        return None
    for path in sorted(directory.glob(f"{function}-*.json")):
        record = json.loads(path.read_text())
        if record.get("function") == function and record.get("source"):
            return record
    return None


def retail_bytes(entry: dict[str, object], range_end: int | None = None) -> bytes:
    address = int(str(entry["address"]), 16)
    size = int(entry["size"])
    if range_end is not None:
        if range_end < address + size:
            raise ValueError("explicit range must include the whole catalog function")
        size = range_end - address
    image = TARGET.read_bytes()
    offset = address - TEXT_VRAM
    body = image[offset : offset + size]
    if len(body) != size:
        raise SystemExit("function range is outside the retail load image")
    return body


def direct_call_listing(function: str, body: bytes, address: int) -> str:
    """Represent reviewed instruction-only text using real external JAL symbols.

    This opt-in mode does not infer data, jump tables, HI16/LO16 pairs or aliases.
    Call destinations come only from retail instruction fields and the catalog,
    never from candidate code or candidate relocation positions.
    """
    if address % 4 or len(body) % 4:
        raise ValueError("direct-call target requires complete aligned MIPS words")
    known = {int(str(row["address"]), 16): row["name"]
             for row in json.loads(CATALOG.read_text())["functions"]}
    lines = [".section .text", ".set noreorder", ".align 2",
             f".globl {function}", f".type {function}, @function", f"{function}:"]
    for offset in range(0, len(body), 4):
        word = struct.unpack_from("<I", body, offset)[0]
        if word >> 26 == 3:
            target = ((address + offset + 4) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)
            if address <= target < address + len(body):
                raise ValueError("internal JAL requires explicit local-label support")
            if target not in known:
                raise ValueError(f"JAL target 0x{target:08X} is absent from the catalog")
            lines.append(f"jal {known[target]}")
        else:
            lines.append(f".word 0x{word:08X}")
    lines.append(f".size {function}, . - {function}")
    return "\n".join(lines) + "\n"


def verify_target_object(obj: Path, directory: Path, address: int, body: bytes) -> None:
    """Fail unless the diagnostic target links back to every supplied retail byte."""
    directory = directory.resolve()
    script, derived = directory / "target.ld", directory / "target_derived.ld"
    linked, binary = directory / "target_linked.elf", directory / "target_linked.bin"
    script.write_text(match.linker_script(address, None, match.SDATA_VRAM))
    match.write_derived_symbols(obj.resolve(), derived)
    subprocess.run(
        ["mipsel-linux-gnu-ld", "-EL", "-m", "elf32ltsmip", "--no-check-sections",
         "-T", str(script), "-T", str(derived), "-T", "config/linker_aliases.ld",
         "-T", "build/undefined_funcs_auto.txt", "-T", "build/undefined_syms_auto.txt",
         "-o", str(linked), str(obj.resolve())], cwd=ROOT, check=True)
    subprocess.run(
        ["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", str(linked), str(binary)],
        cwd=ROOT, check=True)
    if binary.read_bytes() != body:
        raise ValueError("relocated target failed full retail-byte verification")


def write_target_object(function: str, body: bytes, directory: Path, *,
                        address: int | None = None, relocate_direct_calls: bool = False) -> Path:
    """Build a raw target, or an explicitly reviewed direct-call relocation target."""
    output = directory / "target.o"
    output.unlink(missing_ok=True)
    try:
        binary = directory / "target.bin"
        binary.write_bytes(body)
        listing = directory / "target.s"
        if relocate_direct_calls:
            if address is None:
                raise ValueError("direct-call relocation requires the real text address")
            listing.write_text(direct_call_listing(function, body, address))
        else:
            listing.write_text(
                ".section .text\n.align 2\n"
                f".globl {function}\n.type {function}, @function\n{function}:\n"
                f'.incbin "{binary.name}"\n'
                f".size {function}, . - {function}\n")
        subprocess.run(
            ["mipsel-linux-gnu-as", "-EL", "-march=r5900", "-mabi=eabi", "-no-pad-sections",
             "-o", str(output.resolve()), listing.name], cwd=directory, check=True)
        if relocate_direct_calls:
            verify_target_object(output, directory, address, body)
    except BaseException:
        output.unlink(missing_ok=True)
        raise
    return output


def write_compile_script(
    directory: Path, profile: str, object_flags: list[str]
) -> Path:
    flags = "".join(f' --object-flag={flag}' for flag in object_flags)
    script = directory / "compile.sh"
    script.write_text(
        "#!/bin/sh\n"
        "# Delegates to the repository's own compile so a search cannot drift\n"
        "# from the verifier that decides whether a candidate matches.\n"
        'INPUT="$1"\n'
        'shift\n'
        'OUTPUT="out.o"\n'
        'while [ $# -gt 0 ]; do\n'
        '  case "$1" in\n'
        '    -o) OUTPUT="$2"; shift 2 ;;\n'
        '    *) shift ;;\n'
        '  esac\n'
        'done\n'
        f'exec python3 "{ROOT}/tools/permute_compile.py" "$INPUT" -o "$OUTPUT" '
        f'--profile {profile}{flags}\n'
    )
    script.chmod(0o755)
    return script


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("--source", type=Path, help="candidate C source")
    parser.add_argument("--profile", help="build profile; default is the ledger's")
    parser.add_argument("--object-flag", action="append", default=None)
    parser.add_argument("--output-dir", type=Path, default=None)
    parser.add_argument(
        "--permuter", type=Path, help="decomp-permuter checkout, to print its command"
    )
    parser.add_argument("--range-end", type=lambda value: int(value, 0),
                        help="explicit end of the complete emitted text range")
    parser.add_argument("--relocate-direct-calls", action="store_true",
                        help="reviewed instruction-only text: represent external JAL relocations")
    arguments = parser.parse_args()

    function = arguments.function
    entry = catalog_entry(function)
    known = ledger_entry(function) or verified_candidate(function) or {}

    source = arguments.source
    if source is None:
        recorded = known.get("source")
        if not recorded:
            raise SystemExit(
                f"no source for {function}; pass --source with a candidate to permute"
            )
        source = ROOT / str(recorded)
    if not source.is_file():
        raise SystemExit(f"source does not exist: {source}")

    profile = arguments.profile or known.get("build_profile")
    if not profile:
        raise SystemExit(f"no build profile for {function}; pass --profile")
    object_flags = (
        arguments.object_flag
        if arguments.object_flag is not None
        else [str(flag) for flag in (known.get("object_flags") or [])]
    )

    body = retail_bytes(entry, arguments.range_end)
    directory = (arguments.output_dir or (DEFAULT_ROOT / function)).resolve()
    directory.mkdir(parents=True, exist_ok=True)
    target = directory / "target.o"
    target.unlink(missing_ok=True)
    try:
        shutil.copyfile(source, directory / "base.c")
        write_target_object(function, body, directory, address=int(str(entry["address"]), 16),
                            relocate_direct_calls=arguments.relocate_direct_calls)
        write_compile_script(directory, str(profile), list(object_flags))
        (directory / "settings.toml").write_text(
            f'func_name = "{function}"\ncompiler_type = "gcc"\n'
            'objdump_command = "mipsel-linux-gnu-objdump -drz -m mips:5900"\n'
        )
    except BaseException:
        target.unlink(missing_ok=True)
        raise

    print(f"prepared {directory.relative_to(ROOT) if directory.is_relative_to(ROOT) else directory}")
    print(f"  function     {function} ({len(body)} bytes at {entry['address']})")
    print(f"  base.c       {source.relative_to(ROOT) if source.is_relative_to(ROOT) else source}")
    print(f"  profile      {profile}{' ' + ' '.join(object_flags) if object_flags else ''}")
    permuter = arguments.permuter
    command = (
        f"python3 {permuter}/permuter.py {directory}"
        if permuter
        else f"python3 <decomp-permuter>/permuter.py {directory}"
    )
    print(f"\nrun:  {command}")
    print("then: python3 tools/campaign.py harvest <output dir with source.c files>")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
