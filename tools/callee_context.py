#!/usr/bin/env python3
"""Flag candidate parameter declarations that conflict with matched callees.

This is a read-only triage aid, not a C parser or a match authority. It compares
explicit parameter counts and floating-point argument positions. Historical
declarations can differ; inspect caller and callee assembly before changing C.
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SIGNATURE = re.compile(r"\b(func_[0-9A-Fa-f]+)\s*\(([^;{}]*?)\)\s*([;{])")


def parameter_shape(parameters: str) -> tuple[str, ...] | None:
    parameters = parameters.strip()
    if not parameters or "..." in parameters:
        return None  # Unspecified and variadic lists cannot establish arity.
    if parameters == "void":
        return ()
    parts = []
    start = depth = 0
    for index, character in enumerate(parameters):
        if character in "([":
            depth += 1
        elif character in ")]":
            depth -= 1
        elif character == "," and depth == 0:
            parts.append(parameters[start:index])
            start = index + 1
    parts.append(parameters[start:])
    return tuple(
        "pointer" if any(c in part for c in "*[") else
        "double" if re.search(r"\bdouble\b", part) else
        "float" if re.search(r"\bfloat\b", part) else "other"
        for part in parts
    )


def signatures(source: str, terminator: str) -> dict[str, tuple[str, ...]]:
    # Remove comments and literals so examples and messages are not declarations.
    source = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                    " ", source, flags=re.S)
    result = {}
    depth = previous = 0
    for found in SIGNATURE.finditer(source):
        between = source[previous:found.start()]
        depth += between.count("{") - between.count("}")
        previous = found.start()
        if depth != 0:
            continue  # A call in a function body is not a top-level signature.
        if found[3] != terminator:
            continue
        # A call also ends in ';'. Only declarations have a type before the name.
        if terminator == ";":
            prefix = re.split(r"[;{}\n]", source[:found.start()])[-1].strip()
            if not prefix or not re.fullmatch(r"[A-Za-z_][\w\s*]*", prefix):
                continue
            if prefix in {"return", "goto"}:
                continue
        shape = parameter_shape(found[2])
        if shape is not None:
            result[found[1]] = shape
    return result


def conflicts(candidate: dict[str, tuple[str, ...]],
              known: dict[str, tuple[str, ...]]) -> list[dict[str, object]]:
    rows = []
    for name, actual in sorted(candidate.items()):
        expected = known.get(name)
        if expected is None:
            continue
        if len(actual) != len(expected):
            reason = "parameter count"
        elif tuple((i, t) for i, t in enumerate(actual) if t in {"float", "double"}) != \
                tuple((i, t) for i, t in enumerate(expected) if t in {"float", "double"}):
            reason = "floating-point argument positions"
        else:
            continue
        rows.append({"callee": name, "reason": reason,
                     "candidate_shape": actual, "matched_shape": expected})
    return rows


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("sources", type=Path, nargs="+")
    parser.add_argument("--json", type=Path)
    args = parser.parse_args()
    ledger = json.loads((ROOT / "config/reconstructed.json").read_text())
    known = {}
    evidence = {}
    cache = {}
    for row in ledger:
        source = row["source"]
        if source not in cache:
            cache[source] = signatures((ROOT / source).read_text(), "{")
        name = row["function"]
        if name in cache[source]:
            known[name] = cache[source][name]
            evidence[name] = source
    rows = []
    for source in args.sources:
        for row in conflicts(signatures(source.read_text(), ";"), known):
            row.update(source=str(source), matched_source=evidence[row["callee"]])
            rows.append(row)
            print(f"{source}: {row['callee']}: {row['reason']}: "
                  f"{row['candidate_shape']} -> {row['matched_shape']}; "
                  f"evidence {row['matched_source']}")
    report = {"note": "Triage only. Confirm types and actual call arguments against retail before editing.",
              "matched_definitions_scanned": len(known), "conflicts": rows}
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(report, indent=2) + "\n")
    print(f"{len(rows)} declaration conflicts; {len(known)} matched definitions scanned")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
