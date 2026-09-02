#!/usr/bin/env python3
"""Compile one C file to an object exactly as the match verifier does.

A search tool is only useful if it optimises against the compile that decides
the answer. Reimplementing the driver invocation in a shell script would drift
from tools/match.py the first time a profile changes, and a permuter run
against a drifted compiler is worse than none: it reports progress on bytes
nothing will ever verify.

So this is the single entry point. It takes a profile name and object flags,
routes through match.compile_historical_object, and writes the object the
verifier would have produced. compile.sh in a permuter working directory calls
this and nothing else.
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import match
from normalize_asm import normalize

ROOT = Path(__file__).resolve().parents[1]
TOOLCHAINS = ROOT / "config/toolchains.json"


def profiles() -> dict[str, dict[str, object]]:
    return json.loads(TOOLCHAINS.read_text())["profiles"]


def compile_object(
    profile_name: str, source: Path, output: Path, object_flags: list[str]
) -> None:
    """Write the object tools/match.py would compile for this profile."""
    available = profiles()
    if profile_name not in available:
        raise SystemExit(f"unknown profile: {profile_name}")
    profile = available[profile_name]
    output.parent.mkdir(parents=True, exist_ok=True)
    if match.compile_historical_object(profile, source, output, object_flags):
        return
    # Every profile currently pins an assembler, so this is the documented
    # fallback rather than a path in regular use; keep it identical to the one
    # match.py takes so the two cannot diverge silently.
    assembly = output.with_suffix(".s")
    normalized = output.with_suffix(".normalized.s")
    match.run_compiler(match.profile_command(profile, source, assembly))
    normalized.write_text(normalize(assembly.read_text()))
    match.run(
        [
            "mipsel-linux-gnu-as",
            "-EL",
            "-march=r5900",
            "-mabi=eabi",
            "-no-pad-sections",
            "-Iinclude",
            "-o",
            str(output),
            str(normalized),
        ]
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("-o", "--output", type=Path, required=True)
    parser.add_argument("--profile", required=True)
    parser.add_argument("--object-flag", action="append", default=[])
    arguments = parser.parse_args()

    source = arguments.source
    if not source.is_absolute():
        source = Path.cwd() / source
    output = arguments.output
    if not output.is_absolute():
        output = Path.cwd() / output
    compile_object(arguments.profile, source, output, list(arguments.object_flag))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
