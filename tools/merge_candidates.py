#!/usr/bin/env python3
"""Validate candidate JSONL and transactionally import exact C reconstructions.

The default is a read-only dry run. ``--write`` updates the reconstruction and
exact-match ledgers, regenerates Splat text boundaries, and retains the changes
only if the complete build, baseline build, generated README, STATUS, and scope
progress, and public repository checks pass.
Candidate source must already exist below ``src/``; this tool never copies it.
Every record requires match evidence; unresolved provenance may be recorded as
an optional note without creating a second public progress tier.
"""

from __future__ import annotations

import argparse
import fcntl
import json
import os
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path, PurePosixPath
from typing import NoReturn

from build_controls import object_flag_errors
from compiler_diagnostics import dangerous_diagnostics, unexpected_diagnostics
from source_audit import audit_c_source

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
TOOLCHAINS = ROOT / "config/toolchains.json"
RECONSTRUCTED = ROOT / "config/reconstructed.json"
MATCHED = ROOT / "config/matched.json"
SPLAT = ROOT / "config/splat.us.yaml"
README = ROOT / "README.md"
STATUS = ROOT / "docs/STATUS.md"
SCOPE = ROOT / "docs/scope.md"
PROMOTION_LOCK = ROOT / "work/promotion.lock"

ALLOWED_FIELDS = {
    "function",
    "source",
    "build_profile",
    "verified_profiles",
    "object_flags",
    "unit_start",
    "unit_end",
    "rodata_start",
    "profile_evidence",
    "evidence",
    "provenance_note",
}
class CandidateError(Exception):
    """A deterministic validation failure in candidate or repository data."""


@dataclass(frozen=True)
class Candidate:
    function: str
    source: str
    build_profile: str
    verified_profiles: tuple[str, ...]
    object_flags: tuple[str, ...]
    unit_start: str | None
    unit_end: str | None
    rodata_start: str | None
    profile_evidence: str | None
    evidence: str
    provenance_note: str | None
    line: int


@dataclass(frozen=True)
class Backup:
    data: bytes
    mode: int


def fail(message: str) -> NoReturn:
    raise CandidateError(message)


def load_json(path: Path, expected: type) -> object:
    try:
        value = json.loads(path.read_text())
    except (OSError, json.JSONDecodeError) as error:
        fail(f"cannot read {path.relative_to(ROOT)}: {error}")
    if not isinstance(value, expected):
        fail(f"{path.relative_to(ROOT)} must contain a JSON {expected.__name__}")
    return value


def address(value: object, where: str) -> int:
    if isinstance(value, bool):
        fail(f"{where} must be an integer or hexadecimal string")
    try:
        parsed = value if isinstance(value, int) else int(str(value), 0)
    except (TypeError, ValueError):
        fail(f"{where} is not an address: {value!r}")
    if not 0 <= parsed <= 0xFFFFFFFF:
        fail(f"{where} is outside the 32-bit address space: {value!r}")
    return parsed


def hex_address(value: int) -> str:
    return f"0x{value:08X}"


def required_string(record: dict[str, object], key: str, where: str) -> str:
    value = record.get(key)
    if not isinstance(value, str) or not value.strip():
        fail(f"{where}: {key} must be a non-empty string")
    return value.strip()


def optional_string(record: dict[str, object], key: str, where: str) -> str | None:
    if key not in record:
        return None
    value = record[key]
    if not isinstance(value, str) or not value.strip():
        fail(f"{where}: {key} must be a non-empty string when present")
    return value.strip()


def string_list(
    record: dict[str, object], key: str, where: str, *, required: bool
) -> tuple[str, ...]:
    if key not in record:
        if required:
            fail(f"{where}: missing required field {key}")
        return ()
    value = record[key]
    if not isinstance(value, list) or (required and not value):
        qualifier = "a non-empty" if required else "a"
        fail(f"{where}: {key} must be {qualifier} list")
    result: list[str] = []
    for index, item in enumerate(value):
        if not isinstance(item, str) or not item:
            fail(f"{where}: {key}[{index}] must be a non-empty string")
        if item in result:
            fail(f"{where}: {key} contains duplicate value {item!r}")
        result.append(item)
    return tuple(result)


def normalized_source(value: str, where: str) -> str:
    if "\\" in value:
        fail(f"{where}: source must use repository-relative POSIX separators")
    pure = PurePosixPath(value)
    if pure.is_absolute() or ".." in pure.parts or not pure.parts:
        fail(f"{where}: source must be a normalized path below src/: {value!r}")
    if pure.parts[0] != "src" or pure.suffix != ".c" or str(pure) != value:
        fail(f"{where}: source must be a normalized C path below src/: {value!r}")
    path = ROOT / pure
    if not path.is_file():
        fail(f"{where}: source does not exist: {value}")
    try:
        path.resolve().relative_to((ROOT / "src").resolve())
    except ValueError:
        fail(f"{where}: source resolves outside src/: {value}")
    return value


def validate_object_flags(flags: tuple[str, ...], where: str) -> None:
    errors = object_flag_errors(list(flags))
    if errors:
        fail(f"{where}: " + "; ".join(errors))


def _code_without_comments_or_literals(text: str) -> str:
    """Mask comments and quoted literals while preserving line structure."""
    result = list(text)
    state = "code"
    index = 0
    while index < len(text):
        char = text[index]
        following = text[index + 1] if index + 1 < len(text) else ""
        if state == "code":
            if char == "/" and following == "/":
                result[index] = result[index + 1] = " "
                index += 1
                state = "line-comment"
            elif char == "/" and following == "*":
                result[index] = result[index + 1] = " "
                index += 1
                state = "block-comment"
            elif char == '"':
                result[index] = " "
                state = "string"
            elif char == "'":
                result[index] = " "
                state = "character"
        elif state in ("string", "character"):
            if char != "\n":
                result[index] = " "
            if char == "\\" and following:
                index += 1
                if text[index] != "\n":
                    result[index] = " "
            elif (state == "string" and char == '"') or (
                state == "character" and char == "'"
            ):
                state = "code"
        elif state == "line-comment":
            if char == "\n":
                state = "code"
            else:
                result[index] = " "
        elif state == "block-comment":
            if char == "*" and following == "/":
                result[index] = result[index + 1] = " "
                index += 1
                state = "code"
            elif char != "\n":
                result[index] = " "
        index += 1
    return "".join(result)


def parse_candidates(path: Path, profiles: set[str]) -> list[Candidate]:
    try:
        lines = path.read_text().splitlines()
    except OSError as error:
        fail(f"cannot read candidate JSONL {path}: {error}")
    candidates: list[Candidate] = []
    seen: dict[str, int] = {}
    for line_number, line in enumerate(lines, 1):
        if not line.strip():
            continue
        where = f"{path}:{line_number}"
        try:
            record = json.loads(line)
        except json.JSONDecodeError as error:
            fail(f"{where}: invalid JSON: {error}")
        if not isinstance(record, dict):
            fail(f"{where}: each JSONL record must be an object")
        unknown = sorted(set(record) - ALLOWED_FIELDS)
        if unknown:
            fail(f"{where}: unknown fields: {', '.join(unknown)}")

        function = required_string(record, "function", where)
        if function in seen:
            fail(
                f"{where}: duplicate input function {function}; "
                f"first seen on line {seen[function]}"
            )
        seen[function] = line_number
        source = normalized_source(required_string(record, "source", where), where)
        build_profile = required_string(record, "build_profile", where)
        verified_profiles = string_list(
            record, "verified_profiles", where, required=True
        )
        object_flags = string_list(record, "object_flags", where, required=False)
        validate_object_flags(object_flags, where)
        unknown_profiles = sorted(
            set((build_profile, *verified_profiles)) - profiles
        )
        if unknown_profiles:
            fail(f"{where}: unknown profiles: {', '.join(unknown_profiles)}")
        if build_profile not in verified_profiles:
            fail(f"{where}: build_profile must appear in verified_profiles")

        has_start = "unit_start" in record
        has_end = "unit_end" in record
        if has_start != has_end:
            fail(f"{where}: unit_start and unit_end must be supplied together")
        unit_start = None
        unit_end = None
        if has_start:
            unit_start = hex_address(address(record["unit_start"], f"{where}: unit_start"))
            unit_end = hex_address(address(record["unit_end"], f"{where}: unit_end"))
        rodata_start = None
        if "rodata_start" in record:
            rodata_start = hex_address(
                address(record["rodata_start"], f"{where}: rodata_start")
            )

        profile_evidence = optional_string(record, "profile_evidence", where)
        evidence = optional_string(record, "evidence", where)
        provenance_note = optional_string(record, "provenance_note", where)
        if evidence is None:
            fail(f"{where}: exact candidates require evidence")

        candidates.append(
            Candidate(
                function=function,
                source=source,
                build_profile=build_profile,
                verified_profiles=verified_profiles,
                object_flags=object_flags,
                unit_start=unit_start,
                unit_end=unit_end,
                rodata_start=rodata_start,
                profile_evidence=profile_evidence,
                evidence=evidence,
                provenance_note=provenance_note,
                line=line_number,
            )
        )
    if not candidates:
        fail(f"candidate JSONL contains no records: {path}")
    return candidates


def source_has_definition(
    text: str, function: str, source: Path | None = None
) -> bool:
    def conditional_definition(name: str) -> bool:
        return re.search(
            rf"^[^\n;]*\b{re.escape(name)}\s*\([^;\n]*\)\s*\n"
            rf"[ \t]*#[ \t]*else\s*\n"
            rf"[^\n]*\b{re.escape(name)}\s*\([^;\n]*\)[^\n]*\n"
            rf"[ \t]*#[ \t]*endif\s*\n[ \t]*\{{",
            clean,
            re.M,
        ) is not None

    def knr_definition(name: str) -> bool:
        return re.search(
            rf"^[ \t]*{re.escape(name)}\s*\([^;\n]*\)\s*\n"
            rf"(?:[ \t]+[^;\n]+;\s*\n)+[ \t]*\{{",
            clean,
            re.M,
        ) is not None

    pattern = re.compile(
        rf"\b{re.escape(function)}\s*\([^;{{}}]*\)\s*"
        rf"(?:__attribute__\s*\(\([^;{{}}]*\)\)\s*)?\{{",
        re.S,
    )
    clean = _code_without_comments_or_literals(text)
    if pattern.search(clean) is not None:
        return True
    if re.search(rf"\b_DEFUN\s*\(\s*{re.escape(function)}\s*,", clean):
        return True
    if conditional_definition(function):
        return True
    if knr_definition(function):
        return True
    aliases = re.findall(
        rf"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)[ \t]+{re.escape(function)}[ \t]*$",
        text,
        re.M,
    )
    for alias in aliases:
        alias_pattern = re.compile(
            rf"\b{re.escape(alias)}\s*\([^;{{}}]*\)\s*"
            rf"(?:__attribute__\s*\(\([^;{{}}]*\)\)\s*)?\{{",
            re.S,
        )
        if alias_pattern.search(clean) is not None:
            return True
        if re.search(rf"\b_DEFUN\s*\(\s*{re.escape(alias)}\s*,", clean):
            return True
        if conditional_definition(alias):
            return True
        if knr_definition(alias):
            return True
    if source is None:
        return False

    # An authentic vendored translation unit may be wrapped only to rename its
    # original symbols to the address-based public names used by this project.
    # Accept that narrow form when the quoted C include really defines the
    # macro's source-side function; the compiled-object proof still checks the
    # requested public symbol and all retail bytes.
    includes = re.findall(
        r'^[ \t]*#[ \t]*include[ \t]+"([^"\n]+\.c)"', text, re.M
    )
    for include in includes:
        for candidate in (source.parent / include, ROOT / include):
            candidate = candidate.resolve()
            try:
                candidate.relative_to(ROOT.resolve())
            except ValueError:
                continue
            if not candidate.is_file():
                continue
            included_text = candidate.read_text(errors="replace")
            if any(source_has_definition(included_text, alias) for alias in aliases):
                return True
    return False


def validate_source(source: str, functions: list[str]) -> None:
    path = ROOT / source
    text = path.read_text(errors="replace")
    issues = audit_c_source(path, repo_root=ROOT)
    if issues:
        fail(issues[0].format(ROOT))
    for function in functions:
        if not source_has_definition(text, function, path):
            fail(f"{source}: missing C definition for {function}")


def proof_command(candidate: Candidate, profile: str) -> list[str]:
    """Build the exact, independently replayable proof for one claimed profile."""
    command = [
        sys.executable,
        "tools/match.py",
        candidate.function,
        "--source",
        candidate.source,
        "--profile",
        profile,
        "--quiet",
    ]
    if candidate.unit_start is not None and candidate.unit_end is not None:
        command.extend(
            [
                "--range-start",
                candidate.unit_start,
                "--range-end",
                candidate.unit_end,
            ]
        )
    if candidate.rodata_start is not None:
        command.extend(["--rodata-start", candidate.rodata_start])
    for flag in candidate.object_flags:
        command.append(f"--object-flag={flag}")
    return command


def verify_candidate_proofs(candidates: list[Candidate]) -> tuple[int, int]:
    """Re-run every profile claim and reject unsafe compiler diagnostics."""
    claims = 0
    replays = 0
    replayed: set[tuple[object, ...]] = set()
    for candidate in candidates:
        for profile in candidate.verified_profiles:
            claims += 1
            key = (
                candidate.function,
                candidate.source,
                profile,
                candidate.object_flags,
                candidate.unit_start,
                candidate.unit_end,
                candidate.rodata_start,
            )
            if key in replayed:
                continue
            command = proof_command(candidate, profile)
            print("+ " + " ".join(command), flush=True)
            result = subprocess.run(
                command,
                cwd=ROOT,
                capture_output=True,
                text=True,
            )
            output = result.stdout + result.stderr
            if result.returncode != 0:
                detail = output.strip()
                suffix = f"\n{detail}" if detail else ""
                fail(
                    f"candidate line {candidate.line}: independent proof failed for "
                    f"{candidate.function} with {profile} (exit {result.returncode})"
                    f"{suffix}"
                )
            dangerous = dangerous_diagnostics(output)
            if dangerous:
                fail(
                    f"candidate line {candidate.line}: unsafe compiler diagnostics for "
                    f"{candidate.function} with {profile}: {', '.join(dangerous)}"
                )
            unclassified = unexpected_diagnostics(output)
            if unclassified:
                fail(
                    f"candidate line {candidate.line}: unclassified compiler "
                    f"diagnostics for {candidate.function} with {profile}: "
                    + "; ".join(unclassified)
                    + ". Classify each in tools/compiler_diagnostics.py as benign "
                    "or ABI-dangerous before importing this match."
                )
            replayed.add(key)
            replays += 1
    return claims, replays


def record_range(
    entry: dict[str, object], catalog: dict[str, dict[str, object]]
) -> tuple[int, int, bool]:
    known = catalog[str(entry["function"])]
    function_start = address(known["address"], f"catalog {entry['function']} address")
    function_end = function_start + int(known["size"])
    explicit = "unit_start" in entry or "unit_end" in entry
    start = address(entry.get("unit_start", function_start), f"{entry['function']} unit_start")
    end = address(entry.get("unit_end", function_end), f"{entry['function']} unit_end")
    return start, end, explicit


def validate_combined(
    reconstructed: list[dict[str, object]],
    matched: list[dict[str, object]],
    catalog_document: dict[str, object],
    profiles: set[str],
) -> None:
    functions_value = catalog_document.get("functions")
    if not isinstance(functions_value, list):
        fail("config/functions.json lacks a functions list")
    catalog = {
        str(entry["name"]): entry
        for entry in functions_value
        if isinstance(entry, dict) and "name" in entry
    }
    if len(catalog) != len(functions_value):
        fail("config/functions.json contains malformed or duplicate functions")

    reconstructed_by_name: dict[str, dict[str, object]] = {}
    by_source: dict[str, list[dict[str, object]]] = {}
    for index, entry in enumerate(reconstructed):
        where = f"reconstructed entry {index}"
        if not isinstance(entry, dict):
            fail(f"{where} must be an object")
        function = entry.get("function")
        source = entry.get("source")
        if not isinstance(function, str) or function not in catalog:
            fail(f"{where} has unknown function: {function!r}")
        if function in reconstructed_by_name:
            fail(f"duplicate reconstructed function: {function}")
        reconstructed_by_name[function] = entry
        if not isinstance(source, str):
            fail(f"{where} has invalid source")
        normalized_source(source, where)
        known = catalog[function]
        if entry.get("address") != known.get("address") or entry.get("size") != known.get("size"):
            fail(f"{where} range disagrees with catalog: {function}")
        profile = entry.get("build_profile")
        if profile not in profiles:
            fail(f"{where} has unknown build_profile: {profile!r}")
        flags = entry.get("object_flags", [])
        if not isinstance(flags, list) or not all(isinstance(flag, str) for flag in flags):
            fail(f"{where} has invalid object_flags")
        validate_object_flags(tuple(flags), where)
        verified = entry.get("verified_profiles")
        if (
            not isinstance(verified, list)
            or not verified
            or not all(isinstance(item, str) and item in profiles for item in verified)
            or profile not in verified
        ):
            fail(f"{where} has invalid verified_profiles")
        start, end, _explicit = record_range(entry, catalog)
        function_start = address(known["address"], f"catalog {function} address")
        function_end = function_start + int(known["size"])
        if not start <= function_start < function_end <= end:
            fail(f"{where} unit range does not contain {function}")
        by_source.setdefault(source, []).append(entry)

    text_start = address(catalog_document.get("text_start"), "catalog text_start")
    text_end = address(catalog_document.get("text_end"), "catalog text_end")
    units: list[tuple[int, int, str]] = []
    for source, entries in by_source.items():
        validate_source(source, [str(entry["function"]) for entry in entries])
        profile_values = {str(entry["build_profile"]) for entry in entries}
        flag_values = {
            tuple(str(flag) for flag in entry.get("object_flags", []))
            for entry in entries
        }
        ranges = {record_range(entry, catalog)[:2] for entry in entries}
        explicit = {record_range(entry, catalog)[2] for entry in entries}
        rodata_origins = {entry.get("rodata_start") for entry in entries}
        if len(profile_values) != 1:
            fail(f"shared source has inconsistent build_profile: {source}")
        if len(flag_values) != 1:
            fail(f"shared source has inconsistent object_flags: {source}")
        if len(ranges) != 1 or (len(entries) > 1 and explicit != {True}):
            fail(f"shared source lacks one explicit, consistent unit range: {source}")
        if len(rodata_origins) != 1:
            fail(f"shared source has inconsistent rodata_start: {source}")
        rodata_origin = next(iter(rodata_origins))
        if rodata_origin is not None:
            address(rodata_origin, f"shared source {source} rodata_start")
        start, end = next(iter(ranges))
        if not text_start <= start < end <= text_end:
            fail(f"source unit is outside catalog text: {source}: {start:#x}-{end:#x}")
        units.append((start, end, source))

    previous_end = text_start
    previous_source = "<text start>"
    for start, end, source in sorted(units):
        if start < previous_end:
            fail(
                f"source units overlap: {previous_source} ends at {previous_end:#x}, "
                f"{source} starts at {start:#x}"
            )
        previous_end = (end + 7) & -8
        previous_source = source

    matched_by_name: dict[str, dict[str, object]] = {}
    for index, entry in enumerate(matched):
        where = f"matched entry {index}"
        if not isinstance(entry, dict) or not isinstance(entry.get("function"), str):
            fail(f"{where} must name a function")
        function = str(entry["function"])
        if function in matched_by_name:
            fail(f"duplicate matched function: {function}")
        matched_by_name[function] = entry
        reconstruction = reconstructed_by_name.get(function)
        if reconstruction is None:
            fail(f"matched function lacks reconstruction: {function}")
        if entry.get("source") != reconstruction.get("source"):
            fail(f"matched source disagrees with reconstruction: {function}")
        known = catalog[function]
        if entry.get("address") != known.get("address") or entry.get("size") != known.get("size"):
            fail(f"matched range disagrees with catalog: {function}")
        if entry.get("profile") != reconstruction.get("build_profile"):
            fail(f"matched profile disagrees with reconstruction: {function}")
        if not isinstance(entry.get("evidence"), str) or not str(entry["evidence"]).strip():
            fail(f"matched function lacks evidence: {function}")

    if set(reconstructed_by_name) != set(matched_by_name):
        fail("exact reconstructed functions differ from config/matched.json")


def planned_entries(
    candidates: list[Candidate],
    catalog_document: dict[str, object],
    existing_reconstructed: list[dict[str, object]],
    existing_matched: list[dict[str, object]],
    *,
    replace_existing: bool = False,
) -> tuple[list[dict[str, object]], list[dict[str, object]]]:
    catalog = {
        str(entry["name"]): entry
        for entry in catalog_document["functions"]  # type: ignore[index]
    }
    candidate_names = {candidate.function for candidate in candidates}
    reconstructed_names = {
        str(entry["function"]) for entry in existing_reconstructed
    }
    matched_names = {str(entry["function"]) for entry in existing_matched}
    replacements = candidate_names & (reconstructed_names | matched_names)
    if replacements and not replace_existing:
        first = next(
            candidate for candidate in candidates if candidate.function in replacements
        )
        fail(
            f"candidate line {first.line}: function already exists in a ledger: "
            f"{first.function}"
        )
    for function in sorted(replacements):
        if function not in reconstructed_names or function not in matched_names:
            fail(
                "cannot replace inconsistent ledger entry; function must exist in both "
                f"config/reconstructed.json and config/matched.json: {function}"
            )

    retained_reconstructed = [
        entry
        for entry in existing_reconstructed
        if not replace_existing or str(entry["function"]) not in candidate_names
    ]
    retained_matched = [
        entry
        for entry in existing_matched
        if not replace_existing or str(entry["function"]) not in candidate_names
    ]
    additions: list[dict[str, object]] = []
    matches: list[dict[str, object]] = []
    for candidate in candidates:
        where = f"candidate line {candidate.line}"
        known = catalog.get(candidate.function)
        if known is None:
            fail(f"{where}: function absent from catalog: {candidate.function}")
        function_start = address(known["address"], f"catalog {candidate.function} address")
        function_end = function_start + int(known["size"])
        if candidate.unit_start is not None and candidate.unit_end is not None:
            start = address(candidate.unit_start, f"{where}: unit_start")
            end = address(candidate.unit_end, f"{where}: unit_end")
            if not start <= function_start < function_end <= end:
                fail(f"{where}: unit range does not contain {candidate.function}")

        entry: dict[str, object] = {
            "function": candidate.function,
            "source": candidate.source,
            "address": known["address"],
            "size": known["size"],
            "verified_profiles": list(candidate.verified_profiles),
            "build_profile": candidate.build_profile,
        }
        if candidate.object_flags:
            entry["object_flags"] = list(candidate.object_flags)
        if candidate.unit_start is not None and candidate.unit_end is not None:
            entry["unit_start"] = candidate.unit_start
            entry["unit_end"] = candidate.unit_end
        if candidate.rodata_start is not None:
            entry["rodata_start"] = candidate.rodata_start
        entry.update(
            {
                "isolated_match": True,
                "whole_program_match": True,
            }
        )
        if candidate.profile_evidence is not None:
            entry["profile_evidence"] = candidate.profile_evidence
        if candidate.provenance_note is not None:
            entry["provenance_note"] = candidate.provenance_note
        additions.append(entry)

        matches.append(
            {
                "function": candidate.function,
                "source": candidate.source,
                "address": known["address"],
                "size": known["size"],
                "profile": candidate.build_profile,
                "evidence": candidate.evidence,
            }
        )

    combined_reconstructed = [*retained_reconstructed, *additions]
    combined_matched = [*retained_matched, *matches]
    combined_reconstructed.sort(
        key=lambda entry: address(entry["address"], f"{entry['function']} address")
    )
    combined_matched.sort(
        key=lambda entry: address(entry["address"], f"{entry['function']} address")
    )
    return combined_reconstructed, combined_matched


def json_bytes(value: object) -> bytes:
    return (json.dumps(value, indent=2) + "\n").encode()


def atomic_write(path: Path, data: bytes, mode: int) -> None:
    descriptor, temporary_name = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    temporary = Path(temporary_name)
    try:
        with os.fdopen(descriptor, "wb") as stream:
            stream.write(data)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(temporary, mode)
        os.replace(temporary, path)
        directory = os.open(path.parent, os.O_RDONLY)
        try:
            os.fsync(directory)
        finally:
            os.close(directory)
    finally:
        if temporary.exists():
            temporary.unlink()


def backups(paths: tuple[Path, ...]) -> dict[Path, Backup]:
    return {
        path: Backup(path.read_bytes(), path.stat().st_mode & 0o777)
        for path in paths
    }


def obsolete_replaced_sources(
    candidates: list[Candidate],
    existing_reconstructed: list[dict[str, object]],
    planned_reconstructed: list[dict[str, object]],
    *,
    replace_existing: bool,
) -> tuple[Path, ...]:
    """Return superseded source files that the transaction must remove safely."""
    if not replace_existing:
        return ()
    candidate_names = {candidate.function for candidate in candidates}
    retained_sources = {str(entry["source"]) for entry in planned_reconstructed}
    obsolete = {
        ROOT / str(entry["source"])
        for entry in existing_reconstructed
        if str(entry["function"]) in candidate_names
        and str(entry["source"]) not in retained_sources
    }
    return tuple(sorted(obsolete))


def restore(saved: dict[Path, Backup]) -> None:
    errors: list[str] = []
    for path, backup in saved.items():
        try:
            atomic_write(path, backup.data, backup.mode)
        except OSError as error:
            errors.append(f"{path}: {error}")
    if errors:
        raise RuntimeError("rollback failed: " + "; ".join(errors))


def run(command: list[str]) -> None:
    print("+ " + " ".join(command), flush=True)
    subprocess.run(command, cwd=ROOT, check=True)


def write_transaction(
    reconstructed: list[dict[str, object]],
    matched: list[dict[str, object]],
    obsolete_sources: tuple[Path, ...] = (),
) -> None:
    paths = (
        RECONSTRUCTED,
        MATCHED,
        SPLAT,
        README,
        STATUS,
        SCOPE,
        *obsolete_sources,
    )
    saved = backups(paths)
    try:
        atomic_write(
            RECONSTRUCTED,
            json_bytes(reconstructed),
            saved[RECONSTRUCTED].mode,
        )
        atomic_write(MATCHED, json_bytes(matched), saved[MATCHED].mode)
        for source in obsolete_sources:
            source.unlink()
        run([sys.executable, "tools/gen_splat_config.py", "--write"])
        run(["make", "verify"])
        run(["make", "baseline"])
        run([sys.executable, "tools/progress.py", "--write-readme"])
        run([sys.executable, "tools/progress.py", "--write-status"])
        run([sys.executable, "tools/scope_scan.py", "--write-scope"])
        run(["make", "public-check"])
    except BaseException:
        restore(saved)
        print(
            "transaction failed; restored ledgers, Splat config, README, STATUS, and scope",
            file=sys.stderr,
        )
        raise


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("jsonl", type=Path, help="candidate JSONL input")
    parser.add_argument(
        "--write",
        action="store_true",
        help="apply the plan and retain it only after every repository gate passes",
    )
    parser.add_argument(
        "--replace-existing",
        action="store_true",
        help=(
            "transactionally re-verify and replace named exact ledger entries; "
            "used when authentic source-unit boundaries require a shared source"
        ),
    )
    args = parser.parse_args()

    # Keep the ledger snapshot, generated Splat config, and all verification
    # gates in one generation even when independent campaign workers promote
    # at the same time. The descriptor remains live until this process exits.
    PROMOTION_LOCK.parent.mkdir(parents=True, exist_ok=True)
    promotion_lock = PROMOTION_LOCK.open("a+")
    fcntl.flock(promotion_lock, fcntl.LOCK_EX)

    try:
        catalog_document = load_json(CATALOG, dict)
        toolchains = load_json(TOOLCHAINS, dict)
        profiles_value = toolchains.get("profiles")  # type: ignore[union-attr]
        if not isinstance(profiles_value, dict) or not profiles_value:
            fail("config/toolchains.json lacks a non-empty profiles object")
        profiles = set(str(name) for name in profiles_value)
        existing_reconstructed = load_json(RECONSTRUCTED, list)
        existing_matched = load_json(MATCHED, list)
        candidates = parse_candidates(args.jsonl, profiles)
        reconstructed, matched = planned_entries(
            candidates,
            catalog_document,  # type: ignore[arg-type]
            existing_reconstructed,  # type: ignore[arg-type]
            existing_matched,  # type: ignore[arg-type]
            replace_existing=args.replace_existing,
        )
        validate_combined(
            reconstructed,
            matched,
            catalog_document,  # type: ignore[arg-type]
            profiles,
        )
        proof_claims, proof_replays = verify_candidate_proofs(candidates)
        print(
            f"VALID PLAN: {len(candidates)} exact reconstruction(s); "
            f"{proof_claims} profile claim(s) covered by "
            f"{proof_replays} independent compiler replay(s)"
        )
        for candidate in candidates:
            print(
                f"  {candidate.function}: match; {candidate.source}; "
                f"{candidate.build_profile}"
            )
        if not args.write:
            print("DRY RUN: no files changed; pass --write to execute the gated transaction")
            return 0
        obsolete_sources = obsolete_replaced_sources(
            candidates,
            existing_reconstructed,  # type: ignore[arg-type]
            reconstructed,
            replace_existing=args.replace_existing,
        )
        write_transaction(reconstructed, matched, obsolete_sources)
        print("TRANSACTION COMPLETE: every gate passed")
        return 0
    except CandidateError as error:
        print(f"candidate import rejected: {error}", file=sys.stderr)
        return 2
    except subprocess.CalledProcessError as error:
        print(
            f"candidate import rejected: command exited {error.returncode}: "
            + " ".join(str(part) for part in error.cmd),
            file=sys.stderr,
        )
        return 1
    except KeyboardInterrupt:
        print("candidate import interrupted", file=sys.stderr)
        return 130


if __name__ == "__main__":
    raise SystemExit(main())
