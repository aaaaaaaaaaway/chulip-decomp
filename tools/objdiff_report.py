#!/usr/bin/env python3
"""Export the exact-C function ledger as an objdiff v2 text-only report.

Units are logical catalog functions, not claims about original translation units.
Fuzzy values are deliberately binary exact-match lower bounds. Data and alignment
outside catalog function ranges are outside this report's scope.
Schema: https://github.com/encounter/objdiff/blob/fba10a617154f19b3fc25c8817dc81f81d8489b5/objdiff-core/protos/report.proto
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys


def measures(functions: list[dict], matched: set[str]) -> dict:
    size = sum(f["size"] for f in functions)
    exact = [f for f in functions if f["name"] in matched]
    matched_size = sum(f["size"] for f in exact)
    byte_percent = 100.0 * matched_size / size if size else 0.0
    return {
        "fuzzy_match_percent": byte_percent,
        "total_code": str(size),
        "matched_code": str(matched_size),
        "matched_code_percent": byte_percent,
        "total_functions": len(functions),
        "matched_functions": len(exact),
        "matched_functions_percent": 100.0 * len(exact) / len(functions) if functions else 0.0,
        "complete_code": str(matched_size),
        "complete_code_percent": byte_percent,
        "total_units": len(functions),
        "complete_units": len(exact),
    }


def build_report(catalog: dict, ledger: list[dict], reconstructed: list[dict]) -> dict:
    functions = catalog["functions"]
    names = [f["name"] for f in functions]
    if len(names) != len(set(names)):
        raise ValueError("duplicate catalog function")
    by_name = {f["name"]: f for f in functions}
    matched = {f["function"] for f in ledger}
    if len(matched) != len(ledger):
        raise ValueError("duplicate matched function")
    exact_records = [f for f in reconstructed if f.get("isolated_match") and f.get("whole_program_match")]
    exact = {f["function"] for f in exact_records}
    if len(exact) != len(exact_records) or exact != matched:
        raise ValueError("exact reconstruction ledger disagrees with matched ledger")
    source_by_name = {}
    for entry in ledger:
        f = by_name.get(entry["function"])
        if f is None or any(entry.get(k) != f[k] for k in ("address", "size")):
            raise ValueError("matched function range disagrees with catalog")
        source_by_name[f["name"]] = entry["source"]
    previous_end = int(catalog["text_start"], 0)
    for f in sorted(functions, key=lambda f: int(f["address"], 0)):
        address = int(f["address"], 0)
        if not isinstance(f["size"], int) or isinstance(f["size"], bool) or f["size"] <= 0:
            raise ValueError("invalid function size")
        if address < previous_end or address + f["size"] > int(catalog["text_end"], 0):
            raise ValueError("overlapping or out-of-text function range")
        previous_end = address + f["size"]
    units = []
    for f in sorted(functions, key=lambda f: int(f["address"], 0)):
        name = f["name"]
        category = "handwritten" if f.get("handwritten") else "ordinary"
        metadata = {"complete": name in matched, "module_name": "SLUS_207.42", "progress_categories": [category]}
        if name in source_by_name:
            metadata["source_path"] = source_by_name[name]
        units.append({
            "name": "functions/" + name,
            "measures": measures([f], matched),
            "functions": [{"name": name, "size": str(f["size"]),
                           "fuzzy_match_percent": 100.0 if name in matched else 0.0,
                           "address": "0", "metadata": {"virtual_address": str(int(f["address"], 0))}}],
            "metadata": metadata,
        })
    categories = [
        {"id": "ordinary", "name": "Other catalog functions", "measures": measures([f for f in functions if not f.get("handwritten")], matched)},
        {"id": "handwritten", "name": "Catalog-marked handwritten functions (included)", "measures": measures([f for f in functions if f.get("handwritten")], matched)},
    ]
    return {"measures": measures(functions, matched), "units": units, "version": 2, "categories": categories}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    # Reuse the project's source-existence and dual-ledger consistency gate.
    sys.path.insert(0, str(args.root / "tools"))
    import progress
    progress.ROOT = args.root.resolve()
    data = progress.progress_data(lambda name: (args.root / name).read_text())
    load = lambda name: json.loads((args.root / "config" / name).read_text())
    report = build_report(load("functions.json"), load("matched.json"), load("reconstructed.json"))
    if int(report["measures"]["matched_code"]) != data["matched_bytes"]:
        raise ValueError("report differs from project progress")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2, allow_nan=False) + "\n")
    print(f"wrote {len(report['units'])} logical function units to {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
