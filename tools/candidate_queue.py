#!/usr/bin/env python3
"""Rank unmatched functions by static tractability signals from generated assembly."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
RECONSTRUCTED = ROOT / "config/reconstructed.json"

CALL = re.compile(r"\bjal(?:r)?\b")
BRANCH = re.compile(
    r"\b(?:b|bal|beq|beql|bne|bnel|bgez|bgezal|bgezall|bgezl|bgtz|bgtzl|"
    r"blez|blezl|bltz|bltzal|bltzall|bltzl|bc1f|bc1fl|bc1t|bc1tl)\b"
)
JUMP_TABLE = re.compile(r"\bjr\s+\$(?!ra\b)")
FLOAT = re.compile(r"\$(?:f\d+)|\b(?:add|sub|mul|div|c\.[a-z]+|cvt\.[a-z]+)\.s\b")
EE = re.compile(r"\b(?:lq|sq|por|pcpy|pext|padd|psub|pmul|qfsrv|mtsab|mtsah)\w*\b")
GLOBAL = re.compile(r"\b(?:D|jtbl)_[0-9A-Fa-f]{8}\b")
GP_REL = re.compile(r"%gp_rel\(")
WORD = re.compile(r"\s\.word\s")
CALLEE = re.compile(r"\bjal\s+([A-Za-z_][\w.]*)")


def assembly_functions() -> dict[str, str]:
    result: dict[str, str] = {}
    current: str | None = None
    body: list[str] = []
    for path in sorted((ROOT / "asm").rglob("*.s")):
        for line in path.read_text(errors="replace").splitlines():
            if line.startswith("glabel "):
                if current:
                    result[current] = "\n".join(body)
                current = line.split()[1]
                body = []
            elif current and line.startswith("endlabel "):
                result[current] = "\n".join(body)
                current = None
                body = []
            elif current:
                body.append(line)
        if current:
            result[current] = "\n".join(body)
            current = None
            body = []
    return result


def features(
    entry: dict[str, object],
    assembly: str,
    reconstructed: frozenset[str] | set[str] | None = None,
) -> dict[str, object]:
    size = int(entry["size"])
    calls = len(CALL.findall(assembly))
    branches = len(BRANCH.findall(assembly))
    globals_count = len(set(GLOBAL.findall(assembly)))
    jump_table = bool(JUMP_TABLE.search(assembly))
    float_ops = len(FLOAT.findall(assembly))
    ee_ops = len(EE.findall(assembly))
    unknown_words = len(WORD.findall(assembly))
    gp_refs = len(GP_REL.findall(assembly))
    handwritten = bool(entry.get("handwritten"))
    callees = set(CALLEE.findall(assembly))
    pending_callees = (
        len(callees - set(reconstructed)) if reconstructed is not None else 0
    )
    # Cost of one attempt, then divided by the bytes it recovers. Ranking the
    # quotient ascending asks for the cheapest byte rather than the smallest
    # function: the old sum grew with size, so it always handed out the tail of
    # tiny leaves first, and 224 unmatched functions of 64 bytes or less are
    # worth 5 KB between them.
    cost = (
        60.0
        + calls * 6
        + branches * 4
        + globals_count * 3
        + float_ops * 2
        + ee_ops * 16
        + unknown_words * 25
        # Switch tables are routine now that build.py pins 36 of them; the old
        # 300 treated them as near-impossible and buried the largest functions.
        + jump_table * 120
        + handwritten * 5000
        # A caller whose callees are still assembly needs their prototypes
        # guessed, and a wrong return type moves registers at every call site.
        + pending_callees * 45
    )
    score = cost / max(size, 1)
    return {
        "function": entry["name"],
        "address": entry["address"],
        "size": size,
        "calls": calls,
        "branches": branches,
        "globals": globals_count,
        "gp_refs": gp_refs,
        "float_ops": float_ops,
        "ee_ops": ee_ops,
        "unknown_words": unknown_words,
        "jump_table": jump_table,
        "handwritten": handwritten,
        "pending_callees": pending_callees,
        "assembly_available": bool(assembly),
        "score": round(score, 2),
    }


def manifest_functions(paths: list[Path]) -> set[str]:
    excluded: set[str] = set()
    for path in paths:
        path = path if path.is_absolute() else ROOT / path
        for line_number, line in enumerate(path.read_text().splitlines(), 1):
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            try:
                entry = json.loads(line)
            except json.JSONDecodeError as error:
                raise SystemExit(f"invalid JSONL {path}:{line_number}: {error}") from error
            function = entry.get("function") if isinstance(entry, dict) else None
            if not isinstance(function, str) or not function:
                raise SystemExit(f"manifest entry lacks function: {path}:{line_number}")
            excluded.add(function)
    return excluded


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--limit", type=int, default=50)
    parser.add_argument("--min-size", type=int, default=8)
    parser.add_argument("--json", type=Path, help="optional queue output")
    parser.add_argument(
        "--exclude-manifest",
        action="append",
        default=[],
        type=Path,
        help="exclude functions named by this JSONL manifest; repeatable",
    )
    args = parser.parse_args()

    catalog = json.loads(CATALOG.read_text())["functions"]
    reconstructed = {
        entry["function"] for entry in json.loads(RECONSTRUCTED.read_text())
    }
    excluded = reconstructed | manifest_functions(args.exclude_manifest)
    assembly = assembly_functions()
    queue = [
        features(entry, assembly.get(str(entry["name"]), ""), reconstructed)
        for entry in catalog
        if entry["name"] not in excluded and int(entry["size"]) >= args.min_size
    ]
    queue.sort(key=lambda row: (row["score"], row["size"], row["address"]))

    print("rank  cost/B bytes call br glob gp fp ee raw dep function")
    for rank, row in enumerate(queue[: args.limit], 1):
        print(
            f"{rank:4} {row['score']:7.2f} {row['size']:5} {row['calls']:4} "
            f"{row['branches']:2} {row['globals']:4} {row['gp_refs']:2} "
            f"{row['float_ops']:2} {row['ee_ops']:2} {row['unknown_words']:3} "
            f"{row['pending_callees']:3} {row['function']}"
        )
    print(f"ranked {len(queue)} unmatched functions")
    if args.json:
        output = args.json if args.json.is_absolute() else ROOT / args.json
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(queue, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
