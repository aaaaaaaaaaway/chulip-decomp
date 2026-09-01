#!/usr/bin/env python3
"""Record how close an unmatched candidate is, and keep only improvements.

A candidate that no longer matches is not worthless: the distance between it
and the retail function is the project's real measure of partial progress. A
lane that drives a function from thirty differing words to three has done most
of the work, and without a durable record the next lane starts from nothing.
One re-sweep of candidates parked as prose notes recovered 181 functions that
were already correct or nearly so, which is the cost of not recording this.

The ledger is append-only and monotone: a worse distance for a candidate is
kept for history but never replaces a better one.
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "docs/nearmiss.jsonl"
CATALOG = ROOT / "config/functions.json"
TARGET = ROOT / "original/SLUS_207.42.rom"
TEXT_VRAM = 0x00100000
WORDS = re.compile(r"^\s*(?:expected|actual)\s+words:\s*(.*)$", re.M)


def catalog() -> dict[str, dict[str, object]]:
    return {e["name"]: e for e in json.loads(CATALOG.read_text())["functions"]}


def distance(function: str, source: str, profile: str, flags: list[str],
             start: int | None, end: int | None) -> tuple[int, str]:
    """Differing 32-bit words between the candidate and retail, and a summary."""
    command = [sys.executable, "tools/match.py", function, "--source", source,
               "--profile", profile]
    for flag in flags:
        command.append(f"--object-flag={flag}")
    if start is not None:
        command += ["--range-start", hex(start), "--range-end", hex(end)]
    proof = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
    if proof.returncode == 0:
        return 0, "MATCH"
    dumps = WORDS.findall(proof.stdout)
    if len(dumps) != 2:
        return -1, (proof.stdout or proof.stderr).strip().splitlines()[-1][:120]
    expected, actual = (d.split() for d in dumps)
    if len(expected) != len(actual):
        return max(len(expected), len(actual)), (
            f"size differs: {len(expected)} vs {len(actual)} words")
    differing = [i for i, (a, b) in enumerate(zip(expected, actual)) if a != b]
    first = differing[0] if differing else 0
    return len(differing), f"{len(differing)} words differ, first at +0x{first * 4:X}"


def load() -> dict[str, dict[str, object]]:
    best: dict[str, dict[str, object]] = {}
    if not LEDGER.exists():
        return best
    for line in LEDGER.read_text().splitlines():
        if not line.strip():
            continue
        entry = json.loads(line)
        current = best.get(entry["function"])
        if current is None or entry["words"] < current["words"]:
            best[entry["function"]] = entry
    return best


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("function", nargs="?")
    parser.add_argument("--source")
    parser.add_argument("--profile", default="ee-gcc2.95.3-136-O2-G8")
    parser.add_argument("--object-flag", action="append", default=[])
    parser.add_argument("--range-start", type=lambda v: int(v, 0))
    parser.add_argument("--range-end", type=lambda v: int(v, 0))
    parser.add_argument("--note", default="")
    parser.add_argument("--report", action="store_true",
                        help="print the best recorded distance per candidate")
    args = parser.parse_args()

    if args.report or not args.function:
        best = load()
        rows = sorted(best.values(), key=lambda e: (e["words"], -int(e["size"])))
        print(f"{'words':>5} {'bytes':>6}  function")
        for row in rows:
            print(f"{row['words']:5} {row['size']:6}  {row['function']}  {row.get('note','')}")
        print(f"\n{len(rows)} candidates recorded; "
              f"{sum(1 for r in rows if r['words'] <= 4)} within four words")
        return 0

    if not args.source:
        raise SystemExit("--source is required when recording a candidate")
    entry = catalog()[args.function]
    words, summary = distance(args.function, args.source, args.profile,
                              args.object_flag, args.range_start, args.range_end)
    if words < 0:
        print(f"could not measure: {summary}")
        return 1
    best = load().get(args.function)
    record = {
        "function": args.function, "size": int(entry["size"]),
        "address": entry["address"], "source": args.source,
        "profile": args.profile, "object_flags": args.object_flag,
        "words": words, "summary": summary, "note": args.note,
        "recorded": time.strftime("%Y-%m-%d"),
    }
    if args.range_start is not None:
        record["range_start"] = hex(args.range_start)
        record["range_end"] = hex(args.range_end)
    if best is not None and best["words"] <= words:
        print(f"not an improvement: {words} words, best recorded is {best['words']}")
        return 0
    with LEDGER.open("a") as handle:
        handle.write(json.dumps(record) + "\n")
    previous = f" (was {best['words']})" if best else ""
    print(f"recorded {args.function}: {words} words{previous} -- {summary}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
