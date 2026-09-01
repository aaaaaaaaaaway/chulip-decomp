#!/usr/bin/env python3
"""Report exact source matches and keep the README progress block reproducible."""

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
    if set(exact_names) != set(names):
        raise SystemExit(
            "exact reconstructed functions differ from config/matched.json"
        )
    sources: dict[str, int] = {}
    for entry in ledger:
        sources[str(entry["source"])] = sources.get(str(entry["source"]), 0) + 1
    in_units = sum(count for count in sources.values() if count > 1)
    profiles = {
        (
            str(entry.get("build_profile", "")),
            tuple(str(flag) for flag in entry.get("object_flags", [])),
        )
        for entry in reconstructed
    }
    return {
        "unit_functions": in_units,
        "isolated_functions": len(names) - in_units,
        "unit_percent": 100 * in_units / len(names) if names else 0.0,
        "build_configurations": len(profiles),
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
    return "\n".join(
        [
            START,
            "## Decompilation progress",
            "",
            f"![Matched functions]({function_badge}) ![Matched text bytes]({byte_badge})",
            "",
            f"`{bar}` **{byte_percent:.4f}%** of provisional text bytes matched",
            "",
            "| Metric | Matched | Total | Progress |",
            "| --- | ---: | ---: | ---: |",
            f"| Text bytes | {data['matched_bytes']:,} | {data['total_bytes']:,} | {byte_percent:.4f}% |",
            f"| Functions | {data['matched_functions']:,} | {data['total_functions']:,} | {function_percent:.4f}% |",
            "",
            "Text bytes is the honest measure. The function count runs well ahead of it "
            "because small functions are matched first, so it overstates how much of the "
            "executable is reconstructed.",
            "",
            "### Provenance",
            "",
            "| Provenance | Count |",
            "| --- | ---: |",
            f"| Recovered inside a multi-function source unit | {data['unit_functions']:,} of {data['matched_functions']:,} ({data['unit_percent']:.1f}%) |",
            f"| Compiled alone in a single-function object | {data['isolated_functions']:,} |",
            f"| Distinct compiler and assembler configurations in use | {data['build_configurations']} |",
            "",
            "A retail translation unit was compiled once, with one set of flags. A function "
            "matched alone in its own object, free to choose its own flags, has the right "
            "bytes but not yet a proven reason for them. Raising the first row and lowering "
            "the last is what turns a byte match into a reconstruction. See "
            "[scope and denominator](docs/scope.md).",
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
        f"matched bytes:     {data['matched_bytes']} / {data['total_bytes']} "
        f"({data['byte_percent']:.4f}%)"
    )
    print(
        f"matched functions: {data['matched_functions']} / {data['total_functions']} "
        f"({data['function_percent']:.4f}%)"
    )
    print(
        f"in proven units:   {data['unit_functions']} / {data['matched_functions']} "
        f"({data['unit_percent']:.1f}%); "
        f"{data['isolated_functions']} compiled alone"
    )
    print(f"build configurations in use: {data['build_configurations']}")
    print("ownership:        SDK frontier at 0x00185400; see docs/scope.md")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
