#!/usr/bin/env python3
"""Report promoted matches and keep the README progress block reproducible."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
START = "<!-- decomp-progress-start -->"
END = "<!-- decomp-progress-end -->"


def progress_data() -> dict[str, int | float]:
    catalog = json.loads((ROOT / "config/functions.json").read_text())["functions"]
    ledger = json.loads((ROOT / "config/matched.json").read_text())
    reconstructed = json.loads((ROOT / "config/reconstructed.json").read_text())
    by_name = {entry["name"]: entry for entry in catalog}
    names = [entry["function"] for entry in ledger]
    if len(names) != len(set(names)):
        raise SystemExit("duplicate function in config/matched.json")
    unknown = sorted(set(names) - set(by_name))
    if unknown:
        raise SystemExit("matched ledger has unknown functions: " + ", ".join(unknown))
    for entry in ledger:
        catalog_entry = by_name[entry["function"]]
        if entry.get("address") != catalog_entry["address"] or entry.get("size") != catalog_entry["size"]:
            raise SystemExit(f"ledger range disagrees with catalog: {entry['function']}")
        if not (ROOT / entry["source"]).is_file():
            raise SystemExit(f"matched source is missing: {entry['source']}")

    total_bytes = sum(entry["size"] for entry in catalog)
    matched_bytes = sum(by_name[name]["size"] for name in names)
    exact_names = [
        entry["function"]
        for entry in reconstructed
        if entry.get("isolated_match") and entry.get("whole_program_match")
    ]
    if len(exact_names) != len(set(exact_names)):
        raise SystemExit("duplicate exact function in config/reconstructed.json")
    exact_unknown = sorted(set(exact_names) - set(by_name))
    if exact_unknown:
        raise SystemExit(
            "reconstruction ledger has unknown exact functions: "
            + ", ".join(exact_unknown)
        )
    exact_bytes = sum(by_name[name]["size"] for name in exact_names)
    return {
        "exact_functions": len(exact_names),
        "exact_bytes": exact_bytes,
        "matched_functions": len(names),
        "total_functions": len(catalog),
        "function_percent": 100 * len(names) / len(catalog),
        "matched_bytes": matched_bytes,
        "total_bytes": total_bytes,
        "byte_percent": 100 * matched_bytes / total_bytes,
    }


def markdown(data: dict[str, int | float]) -> str:
    function_percent = float(data["function_percent"])
    byte_percent = float(data["byte_percent"])
    cells = 40
    filled = int(byte_percent * cells / 100)
    if data["matched_bytes"] and filled == 0:
        bar = "▏" + "░" * (cells - 1)
    else:
        bar = "█" * filled + "░" * (cells - filled)
    function_badge = (
        "https://img.shields.io/badge/functions-"
        f"{data['matched_functions']}%20%2F%20{data['total_functions']}-2f81f7"
    )
    byte_badge = (
        "https://img.shields.io/badge/text%20bytes-"
        f"{data['matched_bytes']}%20%2F%20{data['total_bytes']}-2f81f7"
    )
    exact_badge = (
        "https://img.shields.io/badge/exact%20source-"
        f"{data['exact_functions']}%20functions%20%2F%20{data['exact_bytes']}%20bytes-5b8c5a"
    )
    return "\n".join(
        [
            START,
            "## Decompilation progress",
            "",
            f"![Matched functions]({function_badge}) ![Matched text bytes]({byte_badge}) ![Exact source built]({exact_badge})",
            "",
            f"`{bar}` **{byte_percent:.4f}%** of provisional text bytes promoted",
            "",
            "| Metric | Current | Total | Progress |",
            "| --- | ---: | ---: | ---: |",
            f"| Exact source-built functions | {data['exact_functions']:,} | {data['total_functions']:,} | {100 * int(data['exact_functions']) / int(data['total_functions']):.4f}% |",
            f"| Exact source-built bytes | {data['exact_bytes']:,} | {data['total_bytes']:,} | {100 * int(data['exact_bytes']) / int(data['total_bytes']):.4f}% |",
            f"| Promoted functions | {data['matched_functions']:,} | {data['total_functions']:,} | {function_percent:.4f}% |",
            f"| Promoted text bytes | {data['matched_bytes']:,} | {data['total_bytes']:,} | {byte_percent:.4f}% |",
            "",
            "Only readable source that passes isolated byte comparison, compiler-provenance review, and the complete-image rebuild is counted. Generated retail assembly contributes zero progress.",
            END,
        ]
    )


def replace_readme(block: str, *, write: bool) -> None:
    path = ROOT / "README.md"
    current = path.read_text()
    if current.count(START) != 1 or current.count(END) != 1:
        raise SystemExit("README progress markers are missing or duplicated")
    prefix, remainder = current.split(START, 1)
    _old, suffix = remainder.split(END, 1)
    expected = prefix + block + suffix
    if write:
        path.write_text(expected)
    elif current != expected:
        raise SystemExit("README progress block is stale; run tools/progress.py --write-readme")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--markdown", action="store_true")
    parser.add_argument("--write-readme", action="store_true")
    parser.add_argument("--check-readme", action="store_true")
    args = parser.parse_args()
    if sum((args.markdown, args.write_readme, args.check_readme)) > 1:
        raise SystemExit("select at most one output mode")

    data = progress_data()
    block = markdown(data)
    if args.markdown:
        print(block)
        return 0
    if args.write_readme or args.check_readme:
        replace_readme(block, write=args.write_readme)
        print("README progress block updated" if args.write_readme else "README progress block OK")
        return 0

    print(
        f"exact source:      {data['exact_functions']} functions / "
        f"{data['exact_bytes']} bytes"
    )
    print(
        f"matched functions: {data['matched_functions']} / {data['total_functions']} "
        f"({data['function_percent']:.4f}%)"
    )
    print(
        f"matched bytes:     {data['matched_bytes']} / {data['total_bytes']} "
        f"({data['byte_percent']:.4f}%)"
    )
    print("ownership:        provisional; game-vs-SDK boundaries are not yet proven")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
