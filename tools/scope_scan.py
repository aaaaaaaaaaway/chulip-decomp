#!/usr/bin/env python3
"""Classify every retail function by whether natural C can express it at all.

A completion percentage is only meaningful against an honest denominator. Some
of this executable is hand-written assembly that no C compiler emits: kernel
syscall stubs, VU0 macro-mode vector code, the second EE multiply pipe, and
compiler-generated jump tables whose data the reconstruction cannot yet place.
This scan derives those classes from the zero-C baseline disassembly so the
scope claim is checkable rather than asserted.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
MATCHED = ROOT / "config/matched.json"

LABEL = re.compile(r"^glabel\s+(\S+)")
END = re.compile(r"^endlabel\b")
INSTRUCTION = re.compile(r"\*/\s*(.*)$")

SYSCALL = re.compile(r"^syscall\b")
VU0 = re.compile(r"^(lqc2|sqc2|qmtc2|qmfc2|vcallms|v[a-z]+\.[a-z]+)\b")
MULT1 = re.compile(r"^(mult1|multu1|div1|divu1|madd1|maddu1|mfhi1|mflo1)\b")
JUMP_TABLE = re.compile(r"^jr\s+\$(?!ra\b)")


def bodies() -> dict[str, list[str]]:
    tree = ROOT / "asm-baseline"
    if not tree.is_dir():
        tree = ROOT / "asm"
    result: dict[str, list[str]] = {}
    current: str | None = None
    for path in sorted(tree.rglob("*.s")):
        for line in path.read_text(errors="replace").splitlines():
            label = LABEL.match(line)
            if label:
                current = label.group(1)
                result.setdefault(current, [])
                continue
            if END.match(line):
                current = None
                continue
            if current is None:
                continue
            found = INSTRUCTION.search(line)
            if found:
                result[current].append(" ".join(found.group(1).split()))
    return result


def classify(entry: dict[str, object], body: list[str], matched: set[str]) -> str:
    if str(entry["name"]) in matched:
        return "matched"
    if entry.get("handwritten"):
        return "hand-written assembly"
    if any(SYSCALL.match(text) for text in body):
        return "kernel syscall stub"
    if any(VU0.match(text) for text in body):
        return "VU0 macro mode"
    if any(MULT1.match(text) for text in body):
        return "second multiply pipe"
    if any(JUMP_TABLE.match(text) for text in body):
        return "jump-table switch"
    return "reachable, not yet written"


# Natural C cannot express these at all.
INEXPRESSIBLE = {
    "hand-written assembly",
    "kernel syscall stub",
    "VU0 macro mode",
    "second multiply pipe",
}
# These are ordinary C that the reconstruction cannot yet place. A switch
# compiles to a jump table in .rodata, and the build does not yet lay that
# table down at its retail address. This is a tooling gap, not a limit of C,
# and it is the largest single block of unmatched bytes.
BLOCKED_BY_TOOLING = {"jump-table switch"}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--json", type=Path, help="optional report path")
    args = parser.parse_args()

    catalog = json.loads(CATALOG.read_text())["functions"]
    matched = {str(entry["function"]) for entry in json.loads(MATCHED.read_text())}
    text = bodies()

    groups: dict[str, list[dict[str, object]]] = {}
    for entry in catalog:
        kind = classify(entry, text.get(str(entry["name"]), []), matched)
        groups.setdefault(kind, []).append(entry)

    total_bytes = sum(int(entry["size"]) for entry in catalog)
    order = [
        "matched",
        "reachable, not yet written",
        "jump-table switch",
        "kernel syscall stub",
        "VU0 macro mode",
        "hand-written assembly",
        "second multiply pipe",
    ]
    print(f"{'class':30} {'functions':>9} {'bytes':>9} {'share':>7}")
    for kind in order:
        rows = groups.get(kind, [])
        size = sum(int(entry["size"]) for entry in rows)
        print(f"{kind:30} {len(rows):9} {size:9} {100 * size / total_bytes:6.2f}%")

    def group_bytes(kinds):
        return sum(
            int(entry["size"])
            for kind, rows in groups.items()
            if kind in kinds
            for entry in rows
        )

    inexpressible = group_bytes(INEXPRESSIBLE)
    blocked = group_bytes(BLOCKED_BY_TOOLING)
    reachable_bytes = total_bytes - inexpressible
    matched_bytes = sum(int(entry["size"]) for entry in groups.get("matched", []))
    print()
    print(f"total text                      {total_bytes:9}")
    print(f"  not expressible in C          {inexpressible:9} "
          f"({100 * inexpressible / total_bytes:.2f}%)")
    print(f"  blocked by the build, not C   {blocked:9} "
          f"({100 * blocked / total_bytes:.2f}%)")
    print(f"reachable denominator           {reachable_bytes:9}")
    print(
        f"matched against it              {matched_bytes:9} "
        f"({100 * matched_bytes / reachable_bytes:.4f}%)"
    )
    if args.json:
        out = args.json if args.json.is_absolute() else ROOT / args.json
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(
            json.dumps(
                {
                    "total_bytes": total_bytes,
                    "reachable_bytes": reachable_bytes,
                    "inexpressible_bytes": inexpressible,
                    "blocked_by_tooling_bytes": blocked,
                    "matched_bytes": matched_bytes,
                    "classes": {
                        kind: {
                            "functions": len(rows),
                            "bytes": sum(int(e["size"]) for e in rows),
                        }
                        for kind, rows in sorted(groups.items())
                    },
                },
                indent=2,
            )
            + "\n"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
