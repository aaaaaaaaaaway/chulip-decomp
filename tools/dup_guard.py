#!/usr/bin/env python3
"""Reject byte-for-byte repeated Chulip decompilation candidates."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import time
from pathlib import Path

import match_artifacts

LEDGER = match_artifacts.match.ROOT / "work/cache/dup_guard.jsonl"
TOKEN = re.compile(
    r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/|'
    r"[A-Za-z_]\w*|(?:0[xX][0-9A-Fa-f]+|\d+(?:\.\d*)?)(?:[Ee][+-]?\d+)?[uUlLfF]*|"
    r"<<=|>>=|\.\.\.|->|\+\+|--|&&|\|\||==|!=|<=|>=|<<|>>|\+=|-=|\*=|/=|%=|&=|\|=|\^=|\S",
    re.DOTALL,
)


def normalize(source: str) -> str:
    """Remove comments and formatting while preserving C literals and tokens."""
    tokens = []
    for found in TOKEN.finditer(source):
        token = found.group(0)
        if token.startswith("//") or token.startswith("/*"):
            continue
        tokens.append(token)
    return " ".join(tokens)


def fingerprint(source: str, context: dict[str, object]) -> str:
    digest = hashlib.sha256()
    digest.update(normalize(source).encode())
    digest.update(b"\0")
    digest.update(json.dumps(context, sort_keys=True, separators=(",", ":")).encode())
    return digest.hexdigest()[:20]


def load_entries(ledger: Path = LEDGER) -> list[dict[str, object]]:
    if not ledger.is_file():
        return []
    entries = []
    for line in ledger.read_text().splitlines():
        try:
            entries.append(json.loads(line))
        except json.JSONDecodeError:
            continue
    return entries


def find_duplicate(fp: str, function: str, ledger: Path = LEDGER) -> dict[str, object] | None:
    return next(
        (
            entry
            for entry in load_entries(ledger)
            if entry.get("fingerprint") == fp and entry.get("function") == function
        ),
        None,
    )


def record(
    fp: str,
    function: str,
    context: dict[str, object],
    result: str,
    differing_instructions: int | None,
    ledger: Path = LEDGER,
) -> None:
    ledger.parent.mkdir(parents=True, exist_ok=True)
    entry = {
        "schema": 1,
        "fingerprint": fp,
        "function": function,
        "context": context,
        "result": result,
        "differing_instructions": differing_instructions,
        "timestamp": int(time.time()),
    }
    with ledger.open("a") as output:
        output.write(json.dumps(entry, sort_keys=True) + "\n")


def context_from_spec(spec: match_artifacts.MatchSpec) -> dict[str, object]:
    return {
        "profile": spec.profile_name,
        "range_start": f"0x{spec.address:08X}",
        "range_end": f"0x{spec.end:08X}",
        "object_flags": list(spec.object_flags),
        "rodata_start": f"0x{spec.rodata:08X}" if spec.rodata is not None else None,
    }


def add_candidate_arguments(parser: argparse.ArgumentParser) -> None:
    match_artifacts.add_match_arguments(parser)
    parser.add_argument("--result", choices=("mismatch", "match", "compile-error"), default="mismatch")
    parser.add_argument("--diff", type=int, help="number of differing instructions")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    check_parser = commands.add_parser("check", help="exit 3 if this attempt was recorded")
    add_candidate_arguments(check_parser)
    check_parser.add_argument("--record", action="store_true", help="record the attempt when new")
    record_parser = commands.add_parser("record", help="append an attempt to the ledger")
    add_candidate_arguments(record_parser)
    list_parser = commands.add_parser("list", help="list attempts for a function")
    list_parser.add_argument("function")
    args = parser.parse_args()

    if args.command == "list":
        entries = [entry for entry in load_entries() if entry.get("function") == args.function]
        print(f"{args.function}: {len(entries)} recorded attempt(s)")
        for entry in entries:
            context = entry.get("context", {})
            print(
                f"  {entry.get('fingerprint')} {entry.get('result')} "
                f"diff={entry.get('differing_instructions')} profile={context.get('profile')}"
            )
        return 0

    try:
        spec = match_artifacts.spec_from_args(args)
    except (OSError, ValueError) as error:
        print(f"FAILED: {error}")
        return 2
    context = context_from_spec(spec)
    fp = fingerprint(spec.source.read_text(errors="replace"), context)
    prior = find_duplicate(fp, spec.function)
    if args.command == "check":
        if prior:
            print(
                f"DUP {fp} {spec.function}: already tried "
                f"({prior.get('result')}, diff={prior.get('differing_instructions')}, "
                f"profile={context['profile']})"
            )
            return 3
        print(f"NEW {fp} {spec.function}")
        if args.record:
            record(fp, spec.function, context, args.result, args.diff)
        return 0
    record(fp, spec.function, context, args.result, args.diff)
    print(f"recorded {fp} {spec.function} ({args.result})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
