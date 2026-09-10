#!/usr/bin/env python3
"""Find shared-global function clusters with already reconstructed examples.

Clusters overlap. Their byte counts describe work to investigate, not a sum of
recoverable bytes or evidence that their source shapes will all match.
"""
from __future__ import annotations

import argparse
import json
from collections import defaultdict
from pathlib import Path

import candidate_queue

ROOT = Path(__file__).resolve().parents[1]


def inventory() -> dict[str, object]:
    catalog = {
        row["name"]: row
        for row in json.loads((ROOT / "config/functions.json").read_text())["functions"]
    }
    reconstructed = {
        row["function"]: row
        for row in json.loads((ROOT / "config/reconstructed.json").read_text())
    }
    listings = candidate_queue.assembly_functions()
    groups: dict[str, set[str]] = defaultdict(set)
    for function, assembly in listings.items():
        if function in catalog:
            for symbol in set(candidate_queue.GLOBAL.findall(assembly)):
                groups[symbol].add(function)
    rows = []
    for symbol, members in groups.items():
        pending = sorted(members - reconstructed.keys(), key=lambda f: (-catalog[f]["size"], f))
        known = sorted(members & reconstructed.keys())
        if not pending:
            continue
        rows.append({
            "anchor": symbol,
            "pending_functions": len(pending),
            "pending_bytes": sum(catalog[f]["size"] for f in pending),
            "known_functions": len(known),
            "pending": [{"function": f, "size": catalog[f]["size"]} for f in pending],
            "references": [{"function": f, "source": reconstructed[f]["source"]} for f in known],
        })
    rows.sort(key=lambda row: (-row["pending_bytes"], -row["known_functions"], row["anchor"]))
    return {
        "note": "Shared-global clusters overlap; source transfer remains a hypothesis until verified.",
        "catalog_functions": len(catalog),
        "functions_with_listings": len(catalog.keys() & listings.keys()),
        "clusters": rows,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--anchor", help="show members and source examples for one global")
    parser.add_argument("--min-pending", type=int, default=3)
    parser.add_argument("--min-known", type=int, default=2)
    parser.add_argument("--limit", type=int, default=20)
    parser.add_argument("--json", type=Path, help="write the full inventory, including source references")
    args = parser.parse_args()
    report = inventory()
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(report, indent=2) + "\n")
    rows = report["clusters"]
    if args.anchor:
        found = [row for row in rows if row["anchor"] == args.anchor]
        if not found:
            parser.error(f"no pending cluster for {args.anchor}")
        print(json.dumps(found[0], indent=2))
    else:
        print("global          pending   bytes  known examples")
        selected = [row for row in rows if row["pending_functions"] >= args.min_pending
                    and row["known_functions"] >= args.min_known]
        for row in selected[:args.limit]:
            print(f"{row['anchor']} {row['pending_functions']:7} {row['pending_bytes']:7} "
                  f"{row['known_functions']:6} "
                  + ", ".join(member["function"] for member in row["pending"][:3]))
        print(report["note"])
        print(f"assembly coverage: {report['functions_with_listings']}/{report['catalog_functions']} functions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
