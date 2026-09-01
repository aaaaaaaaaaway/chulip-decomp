#!/usr/bin/env python3
"""Retrieve solved Chulip functions with similar retail opcode sequences."""

from __future__ import annotations

import argparse
import hashlib
import json
import subprocess
from pathlib import Path

import asm_diff
import match

CACHE = match.ROOT / "work/cache/opcode_index.json"


def read_json(path: Path, default):
    return json.loads(path.read_text()) if path.is_file() else default


def cache_key() -> str:
    digest = hashlib.sha256()
    digest.update(match.CATALOG.read_bytes())
    digest.update(match.TARGET.read_bytes())
    version = subprocess.run(
        [asm_diff.OBJDUMP, "--version"], check=True, capture_output=True, text=True
    ).stdout.splitlines()[0]
    digest.update(version.encode())
    return digest.hexdigest()


def build_opcode_index(cache: Path = CACHE) -> dict[str, list[str]]:
    """Build ``function -> mnemonics`` from one disassembly of the retail text."""
    key = cache_key()
    cached = read_json(cache, {})
    if cached.get("schema") == 1 and cached.get("key") == key:
        return cached.get("index", {})

    functions = read_json(match.CATALOG, {"functions": []})["functions"]
    target = match.TARGET.read_bytes()
    valid = []
    for entry in functions:
        address = match.parse_address(entry["address"])
        size = int(entry["size"])
        offset = address - match.TEXT_VRAM
        if size and offset >= 0 and offset + size <= len(target):
            valid.append((str(entry["name"]), address, size))
    if not valid:
        return {}
    low = min(address for _, address, _ in valid)
    high = max(address + size for _, address, size in valid)
    blob = target[low - match.TEXT_VRAM : high - match.TEXT_VRAM]
    instructions = asm_diff.disassemble(blob, low)
    mnemonic_by_address = {
        low + offset: (text.split(None, 1)[0] if text else "?")
        for offset, _word, text in instructions
    }
    index = {
        name: [
            mnemonic_by_address[address]
            for address in range(start, start + size, 4)
            if address in mnemonic_by_address
        ]
        for name, start, size in valid
    }
    index = {name: opcodes for name, opcodes in index.items() if opcodes}
    cache.parent.mkdir(parents=True, exist_ok=True)
    cache.write_text(json.dumps({"schema": 1, "key": key, "index": index}, separators=(",", ":")))
    return index


def levenshtein(left: list[str], right: list[str]) -> int:
    if len(left) > len(right):
        left, right = right, left
    previous = list(range(len(left) + 1))
    for row, right_item in enumerate(right, 1):
        current = [row]
        for column, left_item in enumerate(left, 1):
            current.append(
                min(
                    current[-1] + 1,
                    previous[column] + 1,
                    previous[column - 1] + (left_item != right_item),
                )
            )
        previous = current
    return previous[-1]


def ngram_jaccard(left: list[str], right: list[str], n: int = 3) -> float:
    def grams(sequence: list[str]) -> set[tuple[str, ...]]:
        if len(sequence) < n:
            return {tuple(sequence)} if sequence else set()
        return {tuple(sequence[index : index + n]) for index in range(len(sequence) - n + 1)}

    left_grams, right_grams = grams(left), grams(right)
    union = left_grams | right_grams
    return len(left_grams & right_grams) / len(union) if union else 1.0


def similarity(left: list[str], right: list[str]) -> float:
    short, long = sorted((len(left), len(right)))
    if not long or short / long < 0.4:
        return 0.0
    edit = 1.0 - levenshtein(left, right) / long
    return 0.65 * edit + 0.35 * ngram_jaccard(left, right)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("--k", type=int, default=5)
    parser.add_argument("--pool", choices=("matched", "all"), default="matched")
    parser.add_argument("--min", type=float, default=0.30, dest="minimum")
    parser.add_argument("--with-c", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        index = build_opcode_index()
    except (OSError, subprocess.CalledProcessError) as error:
        print(f"FAILED: {error}")
        return 2
    if args.function not in index:
        print(f"no opcode sequence for {args.function}")
        return 2

    matched_entries = read_json(match.ROOT / "config/matched.json", [])
    matched = {entry["function"]: entry for entry in matched_entries}
    pool = matched if args.pool == "matched" else index
    scored = [
        (similarity(index[args.function], sequence), name)
        for name, sequence in index.items()
        if name != args.function and name in pool
    ]
    scored = sorted((score, name) for score, name in scored if score >= args.minimum)
    scored = list(reversed(scored))[: args.k]
    results = []
    for score, name in scored:
        entry = matched.get(name, {})
        results.append(
            {
                "function": name,
                "similarity": round(score, 3),
                "instructions": len(index[name]),
                "source": entry.get("source"),
                "profile": entry.get("profile") or entry.get("build_profile"),
            }
        )
    if args.json:
        print(
            json.dumps(
                {
                    "target": args.function,
                    "target_instructions": len(index[args.function]),
                    "neighbours": results,
                },
                indent=2,
            )
        )
        return 0
    print(f"# {args.function}: {len(index[args.function])} instructions")
    for result in results:
        print(
            f"  {result['similarity']:.3f}  {result['instructions']:>4}i  "
            f"{result['function']}  {result['profile'] or '?'}  {result['source'] or ''}"
        )
        if args.with_c and result["source"]:
            source = match.ROOT / result["source"]
            if source.is_file():
                print(source.read_text().rstrip())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
