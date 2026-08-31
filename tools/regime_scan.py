#!/usr/bin/env python3
"""Report the callee-saved spill width of every retail function.

The executable was not produced by one compiler configuration. Functions below
a sharp address boundary spill `$s0`-`$s7` with `sq` (128-bit register
precision); functions above it use `sd` at the same sixteen-byte slot stride.
The boundary is independent evidence for the game-versus-SDK frontier, so this
scan is derived from the retail disassembly rather than asserted in prose.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
SPILL = re.compile(r"\*/\s*(sq|sd)\s+\$s[0-7],")
LABEL = re.compile(r"^glabel\s+(\S+)")
END = re.compile(r"^endlabel\b")


def spills() -> dict[str, set[str]]:
    """Scan the zero-C baseline, which always covers the complete image."""
    tree = ROOT / "asm-baseline"
    if not tree.is_dir():
        tree = ROOT / "asm"
    result: dict[str, set[str]] = {}
    current: str | None = None
    for path in sorted(tree.rglob("*.s")):
        for line in path.read_text(errors="replace").splitlines():
            label = LABEL.match(line)
            if label:
                current = label.group(1)
                result.setdefault(current, set())
                continue
            if END.match(line):
                current = None
                continue
            if current is None:
                continue
            found = SPILL.search(line)
            if found:
                result[current].add(found.group(1))
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--json", type=Path, help="optional report path")
    args = parser.parse_args()

    catalog = json.loads(CATALOG.read_text())["functions"]
    widths = spills()
    rows = []
    for entry in catalog:
        kinds = widths.get(str(entry["name"]), set())
        if not kinds:
            continue
        rows.append(
            {
                "function": entry["name"],
                "address": entry["address"],
                "regime": "mixed" if len(kinds) > 1 else next(iter(kinds)),
            }
        )
    rows.sort(key=lambda row: int(str(row["address"]), 16))

    sq = [row for row in rows if row["regime"] == "sq"]
    sd = [row for row in rows if row["regime"] == "sd"]
    mixed = [row for row in rows if row["regime"] == "mixed"]
    if not sq or not sd:
        print("no spill regime boundary is observable")
        return 0
    boundary = int(str(sd[0]["address"]), 16)
    strays = [row for row in sq if int(str(row["address"]), 16) > boundary]

    print(f"functions spilling callee-saved registers: {len(rows)}")
    print(f"  128-bit sq regime: {len(sq)}")
    print(f"  64-bit  sd regime: {len(sd)}")
    print(f"  mixed within one function: {len(mixed)}")
    print(f"first sd-regime function: {sd[0]['address']} {sd[0]['function']}")
    below = [row for row in sq if int(str(row["address"]), 16) < boundary]
    print(f"last sq-regime function below it: {below[-1]['address']} {below[-1]['function']}")
    print(f"sq-regime functions above the boundary: {len(strays)}")
    for row in strays:
        print(f"  {row['address']} {row['function']}")
    if args.json:
        out = args.json if args.json.is_absolute() else ROOT / args.json
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(
            json.dumps(
                {
                    "boundary": f"0x{boundary:08X}",
                    "counts": {"sq": len(sq), "sd": len(sd), "mixed": len(mixed)},
                    "strays_above_boundary": strays,
                    "functions": rows,
                },
                indent=2,
            )
            + "\n"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
