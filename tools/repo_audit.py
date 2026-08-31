#!/usr/bin/env python3
"""Audit the committable repository using no copyrighted local inputs."""

from __future__ import annotations

import json
import re
import subprocess
from pathlib import Path

from progress import markdown, progress_data, replace_readme

ROOT = Path(__file__).resolve().parents[1]
FORBIDDEN_PREFIXES = (
    ".venv/",
    "asm/",
    "asm-baseline/",
    "assets/",
    "build/",
    "disc/",
    "expected/",
    "original/",
    "tools/compilers/",
    "work/",
)
FORBIDDEN_SUFFIXES = (
    ".7z",
    ".bin",
    ".cue",
    ".elf",
    ".exe",
    ".iso",
    ".map",
    ".o",
    ".rar",
    ".zip",
)
SECRET_PATTERNS = (
    re.compile(r"ghp_[A-Za-z0-9]{30,}"),
    re.compile(r"github_pat_[A-Za-z0-9_]{30,}"),
    re.compile(r"AKIA[0-9A-Z]{16}"),
)
LOCAL_PATH_PATTERNS = (
    re.compile(r"/(?:home|Users)/[A-Za-z0-9._-]+/"),
    re.compile(r"[A-Za-z]:\\\\Users\\\\[A-Za-z0-9._-]+\\\\"),
)
REQUIRED = (
    ".github/workflows/verify.yml",
    ".gitignore",
    "README.md",
    "config/disc.json",
    "config/elf.json",
    "config/functions.json",
    "config/matched.json",
    "config/reconstructed.json",
    "config/toolchains.json",
    "docs/DECOMP_POLICY.md",
    "docs/SETUP.md",
)


def committable_files() -> list[str]:
    result = subprocess.run(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z"],
        cwd=ROOT,
        check=True,
        capture_output=True,
    )
    files = (path.decode() for path in result.stdout.split(b"\0") if path)
    return sorted(path for path in files if (ROOT / path).is_file())


def load_json(path: str):
    return json.loads((ROOT / path).read_text())


def main() -> int:
    errors: list[str] = []
    files = committable_files()
    file_set = set(files)
    for required in REQUIRED:
        if required not in file_set:
            errors.append(f"required committable file is missing: {required}")

    for name in files:
        lowered = name.lower()
        if name.startswith(FORBIDDEN_PREFIXES) or lowered.endswith(FORBIDDEN_SUFFIXES):
            errors.append(f"forbidden tracked path: {name}")
            continue
        data = (ROOT / name).read_bytes()
        if b"\0" in data:
            errors.append(f"binary/NUL-containing tracked file: {name}")
            continue
        text = data.decode("utf-8", errors="replace")
        for pattern in SECRET_PATTERNS:
            if pattern.search(text):
                errors.append(f"possible credential in {name}: {pattern.pattern}")
        for pattern in LOCAL_PATH_PATTERNS:
            if pattern.search(text):
                errors.append(f"machine-local path in {name}: {pattern.pattern}")

    for path in sorted((ROOT / "config").glob("*.json")):
        try:
            json.loads(path.read_text())
        except json.JSONDecodeError as error:
            errors.append(f"invalid JSON {path.relative_to(ROOT)}: {error}")
    ledger_path = ROOT / "docs/matching-knowledge.jsonl"
    for line_number, line in enumerate(ledger_path.read_text().splitlines(), 1):
        try:
            json.loads(line)
        except json.JSONDecodeError as error:
            errors.append(f"invalid JSONL {ledger_path.relative_to(ROOT)}:{line_number}: {error}")

    catalog = load_json("config/functions.json")["functions"]
    by_name = {entry["name"]: entry for entry in catalog}
    reconstructed = load_json("config/reconstructed.json")
    matched = load_json("config/matched.json")
    profiles = load_json("config/toolchains.json")["profiles"]
    reconstructed_by_name = {entry["function"]: entry for entry in reconstructed}
    if len(reconstructed_by_name) != len(reconstructed):
        errors.append("duplicate function in config/reconstructed.json")
    matched_names = [entry["function"] for entry in matched]
    if len(matched_names) != len(set(matched_names)):
        errors.append("duplicate function in config/matched.json")

    for entry in reconstructed:
        name = entry["function"]
        known = by_name.get(name)
        if not known:
            errors.append(f"reconstructed function absent from catalog: {name}")
            continue
        if entry.get("address") != known["address"] or entry.get("size") != known["size"]:
            errors.append(f"reconstructed range disagrees with catalog: {name}")
        source = ROOT / entry["source"]
        if not source.is_file() or name not in source.read_text():
            errors.append(f"reconstructed source missing function definition: {name}")
        if entry.get("build_profile") not in profiles:
            errors.append(f"unknown build profile for {name}: {entry.get('build_profile')}")
        if not entry.get("isolated_match") or not entry.get("whole_program_match"):
            errors.append(f"reconstructed entry lacks exact verification: {name}")

    promoted = {entry["function"] for entry in reconstructed if entry.get("promoted")}
    if promoted != set(matched_names):
        errors.append("promoted reconstructed functions differ from config/matched.json")
    for entry in matched:
        name = entry["function"]
        if entry.get("profile") not in profiles:
            errors.append(f"unknown matched profile for {name}: {entry.get('profile')}")

    try:
        data = progress_data()
        replace_readme(markdown(data), write=False)
    except SystemExit as error:
        errors.append(str(error))

    if errors:
        raise SystemExit("REPOSITORY AUDIT FAILED\n  " + "\n  ".join(errors))
    print(f"REPOSITORY AUDIT OK: {len(files)} committable files")
    print(f"promoted matches: {len(matched)} / {len(catalog)} functions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
