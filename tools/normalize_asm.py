#!/usr/bin/env python3
"""Normalize Splat's O32 GPR aliases to numeric names for EE EABI64 GNU as.

Splat/Rabbitizer intentionally renders the retail register fields using O32
aliases. GNU as changes the meaning and availability of several aliases under
`-mabi=eabi` (notably t0-t7), even though the underlying registers are the
same. Numeric names remove that presentation-only ambiguity. This tool does
not rewrite instructions or operands other than GPR spelling.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

GPRS = {
    "zero": 0,
    "at": 1,
    "v0": 2,
    "v1": 3,
    "a0": 4,
    "a1": 5,
    "a2": 6,
    "a3": 7,
    "t0": 8,
    "t1": 9,
    "t2": 10,
    "t3": 11,
    "t4": 12,
    "t5": 13,
    "t6": 14,
    "t7": 15,
    "s0": 16,
    "s1": 17,
    "s2": 18,
    "s3": 19,
    "s4": 20,
    "s5": 21,
    "s6": 22,
    "s7": 23,
    "t8": 24,
    "t9": 25,
    "k0": 26,
    "k1": 27,
    "gp": 28,
    "sp": 29,
    "fp": 30,
    "s8": 30,
    "ra": 31,
}
PATTERN = re.compile(r"\$(" + "|".join(sorted(GPRS, key=len, reverse=True)) + r")\b")


def normalize(text: str) -> str:
    return PATTERN.sub(lambda match: f"${GPRS[match.group(1)]}", text)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    if args.source.resolve() == args.output.resolve():
        raise SystemExit("source and output must differ")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(normalize(args.source.read_text()))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
