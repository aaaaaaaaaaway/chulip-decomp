#!/usr/bin/env python3
"""Validate the retail ELF, extract its PT_LOAD image, and optionally split it."""

from __future__ import annotations

import argparse
import hashlib
import importlib.metadata
import struct
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent
ELF = ROOT / "original/SLUS_207.42"
PAYLOAD = ROOT / "original/SLUS_207.42.rom"
CONFIG = ROOT / "config/splat.us.yaml"

EXPECTED_ELF_SHA256 = "057ef8c41d0216749bbd576c3c64580467dff7bda73ee0861c77a52689d19946"
EXPECTED_PAYLOAD_SHA256 = "77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876"
EXPECTED_TOOLS = {
    "splat64": "0.41.0",
    "spimdisasm": "1.42.2",
    "rabbitizer": "1.16.2",
}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def checked_load_image() -> bytes:
    if not ELF.is_file():
        raise SystemExit(f"missing user-supplied executable: {ELF}")
    blob = ELF.read_bytes()
    actual = sha256(blob)
    if actual != EXPECTED_ELF_SHA256:
        raise SystemExit(f"wrong executable sha256: {actual}")
    if blob[:7] != b"\x7fELF\x01\x01\x01":
        raise SystemExit("target is not a 32-bit little-endian ELF")

    header = struct.unpack_from("<16sHHIIIIIHHHHHH", blob, 0)
    phoff, phentsize, phnum = header[5], header[9], header[10]
    load_segments: list[tuple[int, int, int, int, int]] = []
    for index in range(phnum):
        offset = phoff + index * phentsize
        p_type, p_offset, p_vaddr, _p_paddr, p_filesz, p_memsz, _flags, _align = (
            struct.unpack_from("<IIIIIIII", blob, offset)
        )
        if p_type == 1:
            load_segments.append((p_offset, p_vaddr, p_filesz, p_memsz, index))
    if load_segments != [(0x1000, 0x00100000, 0xED014, 0x1E53AC, 0)]:
        raise SystemExit(f"unexpected PT_LOAD layout: {load_segments!r}")

    p_offset, _vaddr, p_filesz, _memsz, _index = load_segments[0]
    image = blob[p_offset : p_offset + p_filesz]
    actual_image = sha256(image)
    if actual_image != EXPECTED_PAYLOAD_SHA256:
        raise SystemExit(f"wrong PT_LOAD image sha256: {actual_image}")
    return image


def write_if_changed(path: Path, data: bytes) -> None:
    if path.is_file() and path.read_bytes() == data:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    partial = path.with_name(path.name + ".partial")
    partial.write_bytes(data)
    partial.replace(path)


def verify_tools() -> None:
    errors = []
    for package, expected in EXPECTED_TOOLS.items():
        try:
            actual = importlib.metadata.version(package)
        except importlib.metadata.PackageNotFoundError:
            errors.append(f"{package} is not installed")
            continue
        if actual != expected:
            errors.append(f"{package} {actual} != pinned {expected}")
    if errors:
        raise SystemExit("tool version check failed:\n  " + "\n  ".join(errors))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--split", action="store_true", help="run the pinned splat split")
    parser.add_argument(
        "--baseline-split",
        action="store_true",
        help="generate the independent zero-C assembly baseline",
    )
    args = parser.parse_args()

    image = checked_load_image()
    write_if_changed(PAYLOAD, image)
    print(f"ELF OK: {EXPECTED_ELF_SHA256}")
    print(f"PT_LOAD OK: {EXPECTED_PAYLOAD_SHA256}")

    if args.split:
        verify_tools()
        subprocess.run(
            [str(ROOT / ".venv/bin/python"), "-m", "splat", "split", str(CONFIG)],
            cwd=ROOT,
            check=True,
        )
        print("SPLIT OK")
    if args.baseline_split:
        verify_tools()
        subprocess.run(
            [
                str(ROOT / ".venv/bin/python"),
                "-m",
                "splat",
                "split",
                str(ROOT / "config/splat.baseline.yaml"),
            ],
            cwd=ROOT,
            check=True,
        )
        print("BASELINE SPLIT OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
