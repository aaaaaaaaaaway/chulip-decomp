#!/usr/bin/env python3
"""Generate source/assembly text boundaries from the reconstruction ledger."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config/splat.us.yaml"
RECONSTRUCTED = ROOT / "config/reconstructed.json"
FUNCTIONS = ROOT / "config/functions.json"
TEXT_VRAM = 0x00100000
TEXT_END = 0x001A3000
START_MARKER = "      # generated-text-subsegments-start"
END_MARKER = "      # generated-text-subsegments-end"


def address(value: object) -> int:
    return value if isinstance(value, int) else int(str(value), 16)


def align(value: int, amount: int = 8) -> int:
    return (value + amount - 1) & -amount


def source_name(path: str) -> str:
    match = re.fullmatch(r"src/(.+)\.c", path)
    if not match:
        raise SystemExit(f"source path must be below src/ and end in .c: {path}")
    return match.group(1)


def source_units() -> list[dict[str, object]]:
    catalog = json.loads(FUNCTIONS.read_text())["functions"]
    by_name = {entry["name"]: entry for entry in catalog}
    reconstructed = json.loads(RECONSTRUCTED.read_text())
    grouped: dict[str, list[dict[str, object]]] = {}
    for entry in reconstructed:
        grouped.setdefault(str(entry["source"]), []).append(entry)

    units: list[dict[str, object]] = []
    for source, entries in grouped.items():
        starts = {
            address(entry.get("unit_start", by_name[entry["function"]]["address"]))
            for entry in entries
        }
        ends = {
            address(
                entry.get(
                    "unit_end",
                    address(by_name[entry["function"]]["address"])
                    + int(by_name[entry["function"]]["size"]),
                )
            )
            for entry in entries
        }
        if len(starts) != 1 or len(ends) != 1:
            names = ", ".join(str(entry["function"]) for entry in entries)
            raise SystemExit(f"source does not describe one unit: {source}: {names}")
        start = starts.pop()
        end = ends.pop()
        if not TEXT_VRAM <= start < end <= TEXT_END:
            raise SystemExit(f"source unit outside text: {source}: {start:#x}-{end:#x}")
        units.append({"source": source, "start": start, "end": end})

    units.sort(key=lambda unit: int(unit["start"]))
    previous_end = TEXT_VRAM
    for unit in units:
        start = int(unit["start"])
        if start < previous_end:
            raise SystemExit(f"overlapping source unit at {start:#x}: {unit['source']}")
        previous_end = align(int(unit["end"]))
    return units


def generated_lines() -> list[str]:
    lines = [START_MARKER]
    cursor = TEXT_VRAM
    for unit in source_units():
        start = int(unit["start"])
        end = align(int(unit["end"]))
        if cursor < start:
            offset = cursor - TEXT_VRAM
            lines.append(f"      - [0x{offset:06X}, asm, cod/text_{cursor:08X}]")
        offset = start - TEXT_VRAM
        lines.append(
            f"      - [0x{offset:06X}, c, {source_name(str(unit['source']))}]"
        )
        cursor = end
    if cursor < TEXT_END:
        offset = cursor - TEXT_VRAM
        lines.append(f"      - [0x{offset:06X}, asm, cod/text_{cursor:08X}]")
    lines.append(END_MARKER)
    return lines


def rendered_config() -> str:
    text = CONFIG.read_text()
    if text.count(START_MARKER) != 1 or text.count(END_MARKER) != 1:
        raise SystemExit("splat config must contain exactly one generated text marker pair")
    before, rest = text.split(START_MARKER, 1)
    _old, after = rest.split(END_MARKER, 1)
    return before + "\n".join(generated_lines()) + after


def main() -> int:
    parser = argparse.ArgumentParser()
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--check", action="store_true")
    mode.add_argument("--write", action="store_true")
    args = parser.parse_args()

    expected = rendered_config()
    current = CONFIG.read_text()
    if args.check:
        if current != expected:
            raise SystemExit("generated text subsegments are stale; run tools/gen_splat_config.py --write")
        print("SPLAT TEXT SUBSEGMENTS OK")
        return 0
    if current != expected:
        CONFIG.write_text(expected)
        print("SPLAT TEXT SUBSEGMENTS UPDATED")
    else:
        print("SPLAT TEXT SUBSEGMENTS UNCHANGED")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
