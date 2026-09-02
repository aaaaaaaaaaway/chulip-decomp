#!/usr/bin/env python3
"""Prepare a decomp-permuter working directory for one function.

The permuter searches source rewrites that keep behaviour and change register
allocation and scheduling. That is the work a lane currently does by hand: one
856-byte function landed only after a lane exhausted roughly 5,040 declaration
orders and 4,000 statement orders to settle a register-allocation tie, and 119
unmatched functions are larger than 1 KB.

This writes the four files the permuter expects and nothing else. It does not
vendor the permuter: point --permuter at a checkout, or run the printed command
yourself. The compile is delegated to tools/permute_compile.py so the search
optimises against the same object tools/match.py judges.
"""

from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
from pathlib import Path

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


def retail_bytes(entry: dict[str, object]) -> bytes:
    address = int(str(entry["address"]), 16)
    size = int(entry["size"])
    image = TARGET.read_bytes()
    offset = address - TEXT_VRAM
    body = image[offset : offset + size]
    if len(body) != size:
        raise SystemExit("function range is outside the retail load image")
    return body


def write_target_object(function: str, body: bytes, directory: Path) -> Path:
    """Assemble the retail bytes into an object carrying the function symbol.

    The permuter scores a candidate object against this one, so it needs the
    bytes under the right symbol rather than a bare blob.
    """
    binary = directory / "target.bin"
    binary.write_bytes(body)
    listing = directory / "target.s"
    listing.write_text(
        ".section .text\n"
        ".align 2\n"
        f".globl {function}\n"
        f".type {function}, @function\n"
        f"{function}:\n"
        f'.incbin "{binary.name}"\n'
        f".size {function}, . - {function}\n"
    )
    output = directory / "target.o"
    subprocess.run(
        [
            "mipsel-linux-gnu-as",
            "-EL",
            "-march=r5900",
            "-mabi=eabi",
            "-no-pad-sections",
            "-o",
            str(output),
            str(listing.name),
        ],
        cwd=directory,
        check=True,
    )
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

    directory = arguments.output_dir or (DEFAULT_ROOT / function)
    directory.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(source, directory / "base.c")
    body = retail_bytes(entry)
    write_target_object(function, body, directory)
    write_compile_script(directory, str(profile), list(object_flags))
    (directory / "settings.toml").write_text(
        f'func_name = "{function}"\ncompiler_type = "gcc"\n'
    )

    print(f"prepared {directory.relative_to(ROOT)}")
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
