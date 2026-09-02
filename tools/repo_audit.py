#!/usr/bin/env python3
"""Audit the committable repository for public-safe inputs."""

from __future__ import annotations

import argparse
import json
import hashlib
import re
import subprocess
from pathlib import Path

from build_controls import object_flag_errors
from progress import markdown, progress_data, replace_readme
from gen_splat_config import rendered_config
from source_audit import audit_c_source

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
    "docs/knowledge-book.md",
    "docs/SETUP.md",
    "docs/chulip-gameplay.webp",
)
ALLOWED_BINARY_SHA256 = {
    "docs/chulip-gameplay.webp": "181d41ebc6fdb23a58ce52aaabc93cde6a042912d0aca4267ed472295b42c676",
}


def committable_files(index_only: bool = False) -> list[str]:
    """List the files a commit would publish.

    The standing public audit also considers untracked files, because an
    unledgered source sitting in ``src`` is a real inconsistency. A
    pre-commit gate wants the narrower question -- is *this commit*
    consistent -- so that one worker's in-flight promotion cannot refuse
    another's unrelated commit.
    """
    selection = ["--cached"] if index_only else ["--cached", "--others"]
    result = subprocess.run(
        ["git", "ls-files", *selection, "--exclude-standard", "-z"],
        cwd=ROOT,
        check=True,
        capture_output=True,
    )
    files = (path.decode() for path in result.stdout.split(b"\0") if path)
    return sorted(path for path in files if (ROOT / path).is_file())


# Set for --index so every question is asked of one snapshot. Reading the
# file list from the index while reading the ledger from the working tree
# compares two different states, and under concurrent promotion they
# disagree constantly in both directions.
INDEX_ONLY = False


def repository_text(path: str) -> str:
    """Read a tracked file as this commit would publish it."""
    if not INDEX_ONLY:
        return (ROOT / path).read_text()
    result = subprocess.run(
        ["git", "show", f":{path}"],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if result.returncode:
        # Not in the index: the commit publishes HEAD's copy, or nothing.
        return (ROOT / path).read_text()
    return result.stdout


def load_json(path: str):
    return json.loads(repository_text(path))


def matched_sources_are_decompiled(errors: list[str]) -> None:
    """Every ledgered source must still satisfy the shared strict C audit."""
    ledger = load_json("config/reconstructed.json")
    audited: set[str] = set()
    reported: set[tuple[Path, int, str, str]] = set()
    for entry in ledger:
        source = str(entry.get("source", ""))
        path = ROOT / source
        if not path.is_file():
            errors.append(f"matched source is missing: {source}")
            continue
        if source in audited:
            continue
        audited.add(source)
        for issue in audit_c_source(path, repo_root=ROOT):
            key = (issue.path, issue.line, issue.kind, issue.detail)
            if key in reported:
                continue
            reported.add(key)
            errors.append(
                "matched source violates the strict reconstructed-C policy: "
                + issue.format(ROOT)
            )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--index",
        action="store_true",
        help="audit only what is staged, ignoring untracked working-tree files",
    )
    arguments = parser.parse_args()

    global INDEX_ONLY
    INDEX_ONLY = arguments.index

    errors: list[str] = []
    matched_sources_are_decompiled(errors)
    files = committable_files(index_only=arguments.index)
    file_set = set(files)
    for required in REQUIRED:
        if required not in file_set:
            errors.append(f"required committable file is missing: {required}")

    for name in files:
        lowered = name.lower()
        if (ROOT / name).is_symlink():
            errors.append(f"committable symbolic link is prohibited: {name}")
            continue
        if name.startswith(FORBIDDEN_PREFIXES) or lowered.endswith(FORBIDDEN_SUFFIXES):
            errors.append(f"forbidden tracked path: {name}")
            continue
        data = (ROOT / name).read_bytes()
        if b"\0" in data:
            expected_hash = ALLOWED_BINARY_SHA256.get(name)
            actual_hash = hashlib.sha256(data).hexdigest()
            if expected_hash is None:
                errors.append(f"binary/NUL-containing tracked file: {name}")
            elif actual_hash != expected_hash:
                errors.append(f"allowlisted binary hash changed: {name}")
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
    for line_number, line in enumerate(
        repository_text("docs/matching-knowledge.jsonl").splitlines(), 1
    ):
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

    reconstructed_sources = {entry["source"] for entry in reconstructed}
    public_sources = {
        name for name in files if name.startswith("src/") and name.endswith(".c")
    }
    for source in sorted(public_sources - reconstructed_sources):
        errors.append(f"public source is absent from reconstruction ledger: {source}")
    for source in sorted(reconstructed_sources - public_sources):
        errors.append(f"reconstruction ledger source is not committable: {source}")

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
        verified_profiles = entry.get("verified_profiles")
        if (
            not isinstance(verified_profiles, list)
            or not verified_profiles
            or entry.get("build_profile") not in verified_profiles
            or any(profile not in profiles for profile in verified_profiles)
        ):
            errors.append(f"invalid verified profile evidence for {name}")
        if not entry.get("isolated_match") or not entry.get("whole_program_match"):
            errors.append(f"reconstructed entry lacks exact verification: {name}")
        for error in object_flag_errors(entry.get("object_flags", [])):
            errors.append(f"invalid object flags for {name}: {error}")

    entries_by_source: dict[str, list[dict[str, object]]] = {}
    for entry in reconstructed:
        entries_by_source.setdefault(entry["source"], []).append(entry)
    for source, entries in entries_by_source.items():
        profiles_for_source = {entry.get("build_profile") for entry in entries}
        object_flags_for_source = {
            tuple(entry.get("object_flags", [])) for entry in entries
        }
        unit_ranges = {
            (entry.get("unit_start"), entry.get("unit_end")) for entry in entries
        }
        rodata_origins = {entry.get("rodata_start") for entry in entries}
        if len(profiles_for_source) != 1 or len(object_flags_for_source) != 1:
            errors.append(f"inconsistent shared translation-unit settings: {source}")
        if len(entries) > 1 and (len(unit_ranges) != 1 or None in next(iter(unit_ranges))):
            errors.append(f"shared source lacks one exact translation-unit range: {source}")
        if len(rodata_origins) != 1:
            errors.append(f"inconsistent shared translation-unit rodata_start: {source}")

    if set(reconstructed_by_name) != set(matched_names):
        errors.append("exact reconstructed functions differ from config/matched.json")
    for entry in matched:
        name = entry["function"]
        if entry.get("profile") not in profiles:
            errors.append(f"unknown matched profile for {name}: {entry.get('profile')}")

    try:
        data = progress_data()
        replace_readme(markdown(data), write=False)
    except SystemExit as error:
        errors.append(str(error))
    if (ROOT / "config/splat.us.yaml").read_text() != rendered_config():
        errors.append("generated splat text subsegments are stale")

    if errors:
        raise SystemExit("REPOSITORY AUDIT FAILED\n  " + "\n  ".join(errors))
    print(f"REPOSITORY AUDIT OK: {len(files)} committable files")
    print(f"exact source matches: {len(matched)} / {len(catalog)} functions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
