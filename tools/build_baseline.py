#!/usr/bin/env python3
"""Assemble, link, and byte-verify the generated zero-C baseline.

This proves that the split covers the complete loaded image and that modern
binutils can reproduce its bytes. It is scaffolding only: assembly carried
from the target contributes zero decompilation progress.
"""

from __future__ import annotations

import hashlib
import subprocess
from pathlib import Path

from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
SOURCES = (
    Path("asm-baseline/cod/text.s"),
    Path("asm-baseline/data/cod/vutext.s"),
    Path("asm-baseline/data/cod/data.data.s"),
    Path("asm-baseline/data/cod/rodata.rodata.s"),
    Path("asm-baseline/data/cod/sdata.sdata.s"),
    Path("asm-baseline/data/cod/sbss.sbss.s"),
    Path("asm-baseline/data/cod/bss.bss.s"),
)
EXPECTED_SHA256 = "77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876"


def run(command: list[str]) -> None:
    subprocess.run(command, cwd=ROOT, check=True)


def first_difference(expected: bytes, actual: bytes) -> str:
    limit = min(len(expected), len(actual))
    for offset in range(limit):
        if expected[offset] != actual[offset]:
            return (
                f"first difference at payload {offset:#x}: "
                f"expected {expected[offset]:#04x}, got {actual[offset]:#04x}"
            )
    if len(expected) != len(actual):
        return f"size differs: expected {len(expected):#x}, got {len(actual):#x}"
    return "no byte difference"


def main() -> int:
    for source in SOURCES:
        if not (ROOT / source).is_file():
            raise SystemExit(
                f"missing generated split input: {source}; run configure.py --baseline-split"
            )

    normalized_root = ROOT / "build/normalized"
    objects: list[Path] = []
    for source in SOURCES:
        normalized = normalized_root / source
        normalized.parent.mkdir(parents=True, exist_ok=True)
        normalized.write_text(normalize((ROOT / source).read_text()))

        obj = ROOT / "build/baseline-split" / source.with_suffix(".o")
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
        objects.append(obj)

    baseline = ROOT / "build/baseline"
    baseline.mkdir(parents=True, exist_ok=True)
    generated_linker = (ROOT / "build/baseline-split/chulip.baseline.ld").read_text()
    bss_header = ".cod_bss (NOLOAD) :"
    if generated_linker.count(bss_header) != 1:
        raise SystemExit("unexpected generated BSS linker section")
    # The ELF has a 0x6c-byte virtual-only gap between .sdata and .sbss.
    # Splat knows each NOBITS subsegment address but currently emits the grouped
    # NOLOAD output section without it, so make the proven address explicit.
    linker = generated_linker.replace(bss_header, ".cod_bss 0x001ED080 (NOLOAD) :")
    baseline_linker = baseline / "chulip.us.ld"
    baseline_linker.write_text(linker)
    linked = baseline / "chulip.us.elf"
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
            str(baseline_linker),
            "-T",
            "build/baseline-split/undefined_funcs_auto.txt",
            "-T",
            "build/baseline-split/undefined_syms_auto.txt",
            "-o",
            str(linked),
        ]
    )
    image_path = baseline / "chulip.us.rom"
    run(
        [
            "mipsel-linux-gnu-objcopy",
            "-O",
            "binary",
            "-j",
            ".cod",
            str(linked),
            str(image_path),
        ]
    )

    expected = (ROOT / "original/SLUS_207.42.rom").read_bytes()
    actual = image_path.read_bytes()
    digest = hashlib.sha256(actual).hexdigest()
    if digest != EXPECTED_SHA256 or actual != expected:
        raise SystemExit(f"BASELINE MISMATCH: {first_difference(expected, actual)}; sha256 {digest}")

    print(f"BASELINE MATCH: {len(actual)} bytes")
    print(f"sha256: {digest}")
    print("C progress: 0 bytes (generated retail assembly is not decompilation)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
