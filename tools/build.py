#!/usr/bin/env python3
"""Build and byte-verify the current source-plus-assembly reconstruction."""

from __future__ import annotations

import hashlib
import json
import re
import subprocess
from pathlib import Path

from match import compile_historical_object, profile_command
from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
EXPECTED_SHA256 = "77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876"


def run(command: list[str]) -> None:
    subprocess.run(command, cwd=ROOT, check=True)


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
    for source in assembly_sources:
        if not source.is_file():
            raise SystemExit(f"missing generated input: {source.relative_to(ROOT)}; run configure.py --split")
        relative = source.relative_to(ROOT / "asm")
        assemble(source, ROOT / "build/asm" / relative.with_suffix(".o"))

    source_entries: dict[str, list[dict[str, object]]] = {}
    for entry in reconstructed:
        source_entries.setdefault(str(entry["source"]), []).append(entry)

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

    output = ROOT / "build/current"
    output.mkdir(parents=True, exist_ok=True)
    bss_header = ".cod_bss (NOLOAD) :"
    if generated_linker.count(bss_header) != 1:
        raise SystemExit("unexpected generated BSS linker section")
    linker = generated_linker.replace(bss_header, ".cod_bss 0x001ED080 (NOLOAD) :")
    linker_path = output / "chulip.us.ld"
    linker_path.write_text(linker)
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

    promoted = json.loads((ROOT / "config/matched.json").read_text())
    print(f"FULL IMAGE MATCH: {len(actual)} bytes")
    print(f"sha256: {digest}")
    print(f"source-reconstructed functions in build: {len(reconstructed)}")
    print(f"promoted matching functions: {len(promoted)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
