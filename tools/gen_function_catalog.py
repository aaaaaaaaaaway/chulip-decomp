#!/usr/bin/env python3
"""Generate the provisional function catalog from Splat's text assembly."""

from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASM = ROOT / "asm/cod/text.s"
OUT = ROOT / "config/functions.json"

HEADER = re.compile(r"^nonmatching ([A-Za-z_.$][A-Za-z0-9_.$]*), 0x([0-9A-Fa-f]+)$")
INSTRUCTION = re.compile(r"/\*\s+([0-9A-F]+)\s+([0-9A-F]{8})\s+[0-9A-F]{8}\s+\*/")


def main() -> int:
    lines = ASM.read_text().splitlines()
    functions = []
    for index, line in enumerate(lines):
        match = HEADER.match(line)
        if not match:
            continue
        name, size_hex = match.groups()
        address = None
        for candidate in lines[index + 1 : index + 12]:
            instruction = INSTRUCTION.search(candidate)
            if instruction:
                address = int(instruction.group(2), 16)
                break
        if address is None:
            raise SystemExit(f"could not find address after line {index + 1}: {name}")
        handwritten = any(
            "Handwritten function" in candidate for candidate in lines[max(0, index - 3) : index]
        )
        functions.append(
            {
                "name": name,
                "address": f"0x{address:08X}",
                "size": int(size_hex, 16),
                "ownership": "unknown",
                "handwritten": handwritten,
            }
        )

    if not functions:
        raise SystemExit("no functions found")
    addresses = [int(entry["address"], 16) for entry in functions]
    if addresses != sorted(addresses) or len(addresses) != len(set(addresses)):
        raise SystemExit("function addresses are not unique and ascending")
    for current, following in zip(functions, functions[1:]):
        end = int(current["address"], 16) + current["size"]
        if end > int(following["address"], 16):
            raise SystemExit(f"overlap after {current['name']}")

    document = {
        "schema": 1,
        "source": "splat 0.41.0 / spimdisasm 1.42.2 provisional discovery",
        "text_start": "0x00100000",
        "text_end": "0x001A3000",
        "functions": functions,
    }
    OUT.write_text(json.dumps(document, indent=2) + "\n")
    print(f"wrote {OUT}")
    print(f"provisional functions: {len(functions)}")
    print(f"cataloged function bytes: {sum(entry['size'] for entry in functions)}")
    print(f"handwritten-marked functions: {sum(entry['handwritten'] for entry in functions)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
