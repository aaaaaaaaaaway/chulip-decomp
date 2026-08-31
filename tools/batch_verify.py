#!/usr/bin/env python3
"""Re-verify a JSONL batch of staged source candidates with compact output."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TOOLCHAINS = ROOT / "config/toolchains.json"
FUNCTIONS = ROOT / "config/functions.json"
FORBIDDEN_BRIDGES = ("include_asm", "glabel ", "endlabel ", ".globl ", ".word")


def entries(path: Path) -> list[dict[str, object]]:
    result = []
    for number, line in enumerate(path.read_text().splitlines(), 1):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        try:
            entry = json.loads(line)
        except json.JSONDecodeError as error:
            raise SystemExit(f"invalid JSONL {path}:{number}: {error}") from error
        if not entry.get("function") or not entry.get("source"):
            raise SystemExit(f"candidate lacks function/source at {path}:{number}")
        result.append(entry)
    return result


def candidate_source(entry: dict[str, object]) -> Path:
    path = Path(str(entry["source"]))
    path = path if path.is_absolute() else ROOT / path
    if not path.is_file():
        raise SystemExit(f"missing candidate source: {path}")
    text = path.read_text(errors="replace")
    if any(marker in text for marker in FORBIDDEN_BRIDGES):
        raise SystemExit(f"raw/full-function assembly bridge rejected: {path}")
    if str(entry["function"]) not in text:
        raise SystemExit(f"candidate source does not define {entry['function']}: {path}")
    return path


def validate_range(entry: dict[str, object], catalog: dict[str, dict[str, object]]) -> None:
    name = str(entry["function"])
    if name not in catalog:
        raise SystemExit(f"candidate is absent from function catalog: {name}")
    has_start = entry.get("range_start") is not None
    has_end = entry.get("range_end") is not None
    if has_start != has_end:
        raise SystemExit(f"candidate must provide both range_start and range_end: {name}")
    if not has_start:
        return
    start = int(str(entry["range_start"]), 0)
    end = int(str(entry["range_end"]), 0)
    function_start = int(str(catalog[name]["address"]), 0)
    function_end = function_start + int(catalog[name]["size"])
    if not start <= function_start < function_end <= end:
        raise SystemExit(
            f"candidate range does not contain complete catalog function: {name}"
        )


def relative(path: Path) -> Path:
    try:
        return path.resolve().relative_to(ROOT.resolve())
    except ValueError as error:
        raise SystemExit(f"candidate source must be inside the repository: {path}") from error


def command(entry: dict[str, object], source: Path, profile: str) -> list[str]:
    result = [
        sys.executable,
        "tools/match.py",
        str(entry["function"]),
        "--source",
        str(relative(source)),
        "--profile",
        profile,
        "--quiet",
    ]
    for flag in entry.get("object_flags", []):
        result.append(f"--object-flag={flag}")
    if entry.get("range_start") is not None:
        result.extend(["--range-start", str(entry["range_start"])])
    if entry.get("range_end") is not None:
        result.extend(["--range-end", str(entry["range_end"])])
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path, help="JSONL candidate manifest")
    parser.add_argument("--report", type=Path, help="optional JSON result path")
    parser.add_argument(
        "--require-profile",
        action="append",
        default=[],
        help="require this profile to match every candidate; repeatable",
    )
    args = parser.parse_args()

    known_profiles = json.loads(TOOLCHAINS.read_text())["profiles"]
    catalog = {
        entry["name"]: entry
        for entry in json.loads(FUNCTIONS.read_text())["functions"]
    }
    results: list[dict[str, object]] = []
    failures = 0
    for entry in entries(args.manifest):
        validate_range(entry, catalog)
        source = candidate_source(entry)
        requested = entry.get("profiles") or args.require_profile or list(known_profiles)
        unknown = sorted(set(requested) - set(known_profiles))
        if unknown:
            raise SystemExit("unknown profiles: " + ", ".join(unknown))
        matched: list[str] = []
        attempts: dict[str, str] = {}
        for profile in requested:
            proof = subprocess.run(
                command(entry, source, str(profile)),
                cwd=ROOT,
                capture_output=True,
                text=True,
            )
            lines = [line for line in proof.stdout.splitlines() if ": " in line]
            attempts[str(profile)] = lines[0] if lines else proof.stderr.strip()[-240:]
            if proof.returncode == 0:
                matched.append(str(profile))
        required = args.require_profile or entry.get("required_profiles", [])
        ok = bool(matched) and all(str(profile) in matched for profile in required)
        if not ok:
            failures += 1
        state = "MATCH" if ok else "FAIL"
        print(
            f"{state:5} {entry['function']} profiles={','.join(matched) or '-'} "
            f"source={relative(source)}"
        )
        results.append(
            {
                "function": entry["function"],
                "source": str(relative(source)),
                "matched_profiles": matched,
                "attempts": attempts,
                "ok": ok,
            }
        )

    summary = {"candidates": len(results), "passed": len(results) - failures, "failed": failures}
    print(f"verified {summary['passed']} / {summary['candidates']} candidates")
    if args.report:
        report = args.report if args.report.is_absolute() else ROOT / args.report
        report.parent.mkdir(parents=True, exist_ok=True)
        report.write_text(json.dumps({"summary": summary, "results": results}, indent=2) + "\n")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
