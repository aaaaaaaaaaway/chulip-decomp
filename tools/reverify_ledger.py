#!/usr/bin/env python3
"""Restartably replay every exact-match claim in the reconstruction ledger.

Each proof compiles the current source for one complete unit range and one
claimed compiler profile.  Functions which share that exact source, range,
object-flag set, and profile share one proof.  Resume records are content
addressed: changes to source, headers, target bytes, toolchain inputs, host
binutils, or verifier code produce a new proof id and force a fresh compile.
"""

from __future__ import annotations

import argparse
import datetime as dt
import fnmatch
import hashlib
import json
import os
import shutil
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

from compiler_diagnostics import dangerous_diagnostics

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "config/reconstructed.json"
CATALOG = ROOT / "config/functions.json"
TOOLCHAINS = ROOT / "config/toolchains.json"
TARGET = ROOT / "original/SLUS_207.42.rom"
WORK = ROOT / "work"
SCHEMA = 1


class LedgerError(Exception):
    """The ledger or requested verification configuration is invalid."""


@dataclass(frozen=True)
class Claim:
    function: str
    source: str
    profile: str
    start: int
    end: int
    object_flags: tuple[str, ...]
    address: int
    size: int
    rodata_start: int | None = None


@dataclass(frozen=True)
class Proof:
    source: str
    profile: str
    start: int
    end: int
    object_flags: tuple[str, ...]
    claims: tuple[Claim, ...]
    rodata_start: int | None = None

    @property
    def representative(self) -> Claim:
        return min(self.claims, key=lambda claim: (claim.address, claim.function))

    def unit_identity(self) -> dict[str, object]:
        return {
            "source": self.source,
            "profile": self.profile,
            "range_start": f"0x{self.start:08X}",
            "range_end": f"0x{self.end:08X}",
            "object_flags": list(self.object_flags),
            "rodata_start": (
                f"0x{self.rodata_start:08X}" if self.rodata_start is not None else None
            ),
        }


def parse_address(value: object, where: str) -> int:
    if isinstance(value, bool):
        raise LedgerError(f"{where} is not an address: {value!r}")
    try:
        result = value if isinstance(value, int) else int(str(value), 0)
    except (TypeError, ValueError) as error:
        raise LedgerError(f"{where} is not an address: {value!r}") from error
    if not 0 <= result <= 0xFFFFFFFF:
        raise LedgerError(f"{where} is outside the 32-bit address space")
    return result


def load_json(path: Path, expected: type) -> object:
    try:
        value = json.loads(path.read_text())
    except (OSError, json.JSONDecodeError) as error:
        raise LedgerError(f"cannot read {path.relative_to(ROOT)}: {error}") from error
    if not isinstance(value, expected):
        raise LedgerError(f"{path.relative_to(ROOT)} must contain a JSON {expected.__name__}")
    return value


def build_proofs(
    ledger: list[dict[str, object]],
    catalog_entries: list[dict[str, object]],
    profiles: dict[str, object],
) -> list[Proof]:
    """Validate the ledger and collapse only identical complete-unit proofs."""
    catalog = {str(entry["name"]): entry for entry in catalog_entries}
    if len(catalog) != len(catalog_entries):
        raise LedgerError("duplicate function in config/functions.json")

    source_units: dict[str, tuple[int, int, tuple[str, ...], int | None]] = {}
    grouped: dict[tuple[object, ...], list[Claim]] = {}
    seen_functions: set[str] = set()
    for index, entry in enumerate(ledger):
        where = f"reconstructed entry {index}"
        function = entry.get("function")
        source = entry.get("source")
        claimed_profiles = entry.get("verified_profiles")
        flags = entry.get("object_flags", [])
        if not isinstance(function, str) or not function:
            raise LedgerError(f"{where} has invalid function")
        if function in seen_functions:
            raise LedgerError(f"duplicate reconstructed function: {function}")
        seen_functions.add(function)
        if (
            not isinstance(source, str)
            or not source.startswith("src/")
            or not source.endswith(".c")
        ):
            raise LedgerError(f"{where} has invalid source")
        source_path = ROOT / source
        if not source_path.is_file():
            raise LedgerError(f"{where} source does not exist: {source}")
        try:
            source_path.resolve().relative_to((ROOT / "src").resolve())
        except ValueError as error:
            raise LedgerError(f"{where} source resolves outside src/: {source}") from error
        if function not in catalog:
            raise LedgerError(f"{where} is absent from config/functions.json: {function}")
        if (
            not isinstance(claimed_profiles, list)
            or not claimed_profiles
            or any(not isinstance(profile, str) for profile in claimed_profiles)
        ):
            raise LedgerError(f"{where} has no verified_profiles")
        if len(set(claimed_profiles)) != len(claimed_profiles) or any(
            profile not in profiles for profile in claimed_profiles
        ):
            raise LedgerError(f"{where} has invalid verified_profiles")
        if not isinstance(flags, list) or any(not isinstance(flag, str) for flag in flags):
            raise LedgerError(f"{where} has invalid object_flags")

        known = catalog[function]
        address = parse_address(known["address"], f"catalog {function} address")
        size = int(known["size"])
        if parse_address(entry.get("address"), f"{where} address") != address:
            raise LedgerError(f"{where} address disagrees with the function catalog")
        if int(entry.get("size", -1)) != size:
            raise LedgerError(f"{where} size disagrees with the function catalog")
        has_start = "unit_start" in entry
        has_end = "unit_end" in entry
        if has_start != has_end:
            raise LedgerError(f"{where} must provide both unit_start and unit_end")
        start = parse_address(entry["unit_start"], f"{where} unit_start") if has_start else address
        end = parse_address(entry["unit_end"], f"{where} unit_end") if has_end else address + size
        if not start <= address < address + size <= end or end <= start:
            raise LedgerError(f"{where} unit range does not contain the complete function")

        object_flags = tuple(flags)
        rodata_start = (
            parse_address(entry["rodata_start"], f"{where} rodata_start")
            if entry.get("rodata_start") is not None
            else None
        )
        unit = (start, end, object_flags, rodata_start)
        previous = source_units.setdefault(source, unit)
        if previous != unit:
            raise LedgerError(
                f"shared source has inconsistent complete range or object flags: {source}"
            )
        for profile in claimed_profiles:
            claim = Claim(
                function=function,
                source=source,
                profile=profile,
                start=start,
                end=end,
                object_flags=object_flags,
                rodata_start=rodata_start,
                address=address,
                size=size,
            )
            key = (source, profile, start, end, object_flags, rodata_start)
            grouped.setdefault(key, []).append(claim)

    proofs = [
        Proof(
            source=str(key[0]),
            profile=str(key[1]),
            start=int(key[2]),
            end=int(key[3]),
            object_flags=key[4],
            rodata_start=key[5],
            claims=tuple(sorted(claims, key=lambda claim: (claim.address, claim.function))),
        )
        for key, claims in grouped.items()
    ]
    return sorted(proofs, key=lambda proof: (proof.start, proof.end, proof.source, proof.profile))


def hash_file(path: Path, digest: "hashlib._Hash") -> None:
    digest.update(str(path.relative_to(ROOT) if path.is_relative_to(ROOT) else path).encode())
    digest.update(b"\0")
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    digest.update(b"\0")


def hash_tree(path: Path, digest: "hashlib._Hash") -> None:
    if not path.is_dir():
        raise LedgerError(f"required proof input directory is missing: {path}")
    for item in sorted(candidate for candidate in path.rglob("*") if candidate.is_file()):
        hash_file(item, digest)


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def dependency_fingerprint(toolchains: dict[str, object]) -> str:
    """Hash inputs outside an individual source which can affect match results."""
    digest = hashlib.sha256()
    digest.update(f"python:{sys.version}\0".encode())
    for relative in (
        "tools/reverify_ledger.py",
        "tools/match.py",
        "tools/match_artifacts.py",
        "tools/normalize_asm.py",
        "tools/compiler_diagnostics.py",
        "config/toolchains.json",
        "config/linker_aliases.ld",
        "asm-baseline/cod/text.s",
        "build/undefined_funcs_auto.txt",
        "build/undefined_syms_auto.txt",
        "original/SLUS_207.42.rom",
    ):
        path = ROOT / relative
        if not path.is_file():
            raise LedgerError(f"required proof input is missing: {relative}")
        hash_file(path, digest)
    hash_tree(ROOT / "include", digest)
    vendor = ROOT / "tools/vendor"
    if vendor.is_dir():
        hash_tree(vendor, digest)

    toolchain_trees: set[Path] = set()
    needs_wibo = False
    needs_linux32_runtime = False
    for profile in toolchains["profiles"].values():
        if not isinstance(profile, dict):
            raise LedgerError("config/toolchains.json contains a non-object profile")
        for field in ("compiler", "assembler"):
            if profile.get(field):
                relative = Path(str(profile[field]))
                if len(relative.parts) < 3 or relative.parts[:2] != (
                    "tools",
                    "compilers",
                ):
                    raise LedgerError(f"profile {field} is outside tools/compilers: {relative}")
                toolchain_trees.add(ROOT.joinpath(*relative.parts[:3]))
        if profile.get("runner") == "wibo-driver" or profile.get(
            "assembler_runner"
        ) in {"wibo", "ps2eeas"}:
            needs_wibo = True
        if profile.get("runner") == "linux32-cc1" or profile.get("assembler_runner") == "linux32":
            needs_linux32_runtime = True
    for path in sorted(toolchain_trees):
        hash_tree(path, digest)
    if needs_wibo:
        path = ROOT / "tools/compilers/wibo"
        if not path.is_file():
            raise LedgerError("required toolchain executable is missing: tools/compilers/wibo")
        hash_file(path, digest)
    if needs_linux32_runtime:
        hash_tree(ROOT / "tools/compilers/runtime/root/usr/lib32", digest)
    for executable in (
        "mipsel-linux-gnu-as",
        "mipsel-linux-gnu-ld",
        "mipsel-linux-gnu-nm",
        "mipsel-linux-gnu-objcopy",
    ):
        resolved = shutil.which(executable)
        if resolved is None:
            raise LedgerError(f"required host tool is missing from PATH: {executable}")
        hash_file(Path(resolved), digest)
    return digest.hexdigest()


def proof_id(proof: Proof, dependency_hash: str) -> str:
    digest = hashlib.sha256()
    digest.update(dependency_hash.encode())
    digest.update(b"\0")
    digest.update(json.dumps(proof.unit_identity(), sort_keys=True, separators=(",", ":")).encode())
    digest.update(b"\0")
    hash_file(ROOT / proof.source, digest)
    return digest.hexdigest()


def command(proof: Proof) -> list[str]:
    representative = proof.representative.function
    result = [
        sys.executable,
        "tools/match.py",
        representative,
        "--source",
        proof.source,
        "--profile",
        proof.profile,
        "--range-start",
        f"0x{proof.start:08X}",
        "--range-end",
        f"0x{proof.end:08X}",
        "--quiet",
    ]
    result.extend(f"--object-flag={flag}" for flag in proof.object_flags)
    if proof.rodata_start is not None:
        result.extend(["--rodata-start", f"0x{proof.rodata_start:08X}"])
    return result


def resume_record_valid(
    record: dict[str, object], proof: Proof, identifier: str, dependency_hash: str
) -> bool:
    status = record.get("status")
    if (
        record.get("schema") != SCHEMA
        or record.get("type") != "proof"
        or record.get("proof_id") != identifier
        or record.get("dependency_fingerprint") != dependency_hash
        or record.get("unit") != proof.unit_identity()
        or record.get("command") != command(proof)
        or status not in {"pass", "fail", "unsafe", "stale"}
    ):
        return False
    if status == "pass":
        return (
            record.get("returncode") == 0
            and record.get("dangerous_diagnostics") == []
            and record.get("source_stable_during_proof") is True
        )
    return True


def matches_filters(proof: Proof, args: argparse.Namespace) -> bool:
    function_matches = not args.function or any(
        fnmatch.fnmatchcase(claim.function, pattern)
        for claim in proof.claims
        for pattern in args.function
    )
    source_matches = not args.source or any(
        fnmatch.fnmatchcase(proof.source, pattern) for pattern in args.source
    )
    profile_matches = not args.profile or proof.profile in args.profile
    range_matches = (
        (args.address_start is None or proof.end > args.address_start)
        and (args.address_end is None or proof.start < args.address_end)
    )
    return function_matches and source_matches and profile_matches and range_matches


def shard_for(proof: Proof, count: int) -> int:
    identity = json.dumps(proof.unit_identity(), sort_keys=True, separators=(",", ":"))
    return int(hashlib.sha256(identity.encode()).hexdigest()[:16], 16) % count


def read_resume(path: Path) -> dict[str, dict[str, object]]:
    """Read the last complete record per proof, repairing a torn final append."""
    if not path.exists():
        return {}
    records: dict[str, dict[str, object]] = {}
    data = path.read_bytes()
    offset = 0
    repaired = False
    for index, raw in enumerate(data.splitlines(keepends=True)):
        next_offset = offset + len(raw)
        try:
            record = json.loads(raw)
        except json.JSONDecodeError as error:
            if next_offset == len(data):
                with path.open("r+b") as stream:
                    stream.truncate(offset)
                print(f"warning: removed torn final JSONL record from {path}", file=sys.stderr)
                repaired = True
                break
            raise LedgerError(f"invalid JSONL record {index + 1} in {path}: {error}") from error
        offset = next_offset
        if isinstance(record, dict) and isinstance(record.get("proof_id"), str):
            records[str(record["proof_id"])] = record
    if data and not data.endswith(b"\n") and not repaired:
        descriptor = os.open(path, os.O_WRONLY | os.O_APPEND)
        try:
            os.write(descriptor, b"\n")
            os.fsync(descriptor)
        finally:
            os.close(descriptor)
        print(f"warning: completed final JSONL newline in {path}", file=sys.stderr)
    return records


def append_record(path: Path, record: dict[str, object]) -> None:
    encoded = (json.dumps(record, sort_keys=True, separators=(",", ":")) + "\n").encode()
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor = os.open(path, os.O_WRONLY | os.O_CREAT | os.O_APPEND, 0o644)
    try:
        written = os.write(descriptor, encoded)
        if written != len(encoded):
            raise OSError(f"short JSONL append: {written} of {len(encoded)} bytes")
        os.fsync(descriptor)
    finally:
        os.close(descriptor)


def clipped(text: str, limit: int) -> tuple[str, bool]:
    if len(text) <= limit:
        return text, False
    if limit == 0:
        return "", True
    return text[-limit:], True


def run_proof(
    proof: Proof, identifier: str, dependency_hash: str, output_limit: int
) -> dict[str, object]:
    proof_command = command(proof)
    started = time.monotonic()
    try:
        result = subprocess.run(
            proof_command,
            cwd=ROOT,
            capture_output=True,
            text=True,
            errors="replace",
        )
    except OSError as error:
        result = subprocess.CompletedProcess(proof_command, 127, "", str(error))
    duration = time.monotonic() - started
    combined = result.stdout + "\n" + result.stderr
    diagnostics = dangerous_diagnostics(combined)
    source_stable = proof_id(proof, dependency_hash) == identifier
    status = (
        "stale"
        if not source_stable
        else ("unsafe" if diagnostics else ("pass" if result.returncode == 0 else "fail"))
    )
    stdout, stdout_truncated = clipped(result.stdout, output_limit)
    stderr, stderr_truncated = clipped(result.stderr, output_limit)
    return {
        "schema": SCHEMA,
        "type": "proof",
        "proof_id": identifier,
        "dependency_fingerprint": dependency_hash,
        "source_sha256": file_sha256(ROOT / proof.source),
        "timestamp_utc": dt.datetime.now(dt.timezone.utc).isoformat(),
        "unit": proof.unit_identity(),
        "claims": [claim.function for claim in proof.claims],
        "representative": proof.representative.function,
        "command": proof_command,
        "status": status,
        "returncode": result.returncode,
        "dangerous_diagnostics": diagnostics,
        "source_stable_during_proof": source_stable,
        "duration_seconds": round(duration, 6),
        "stdout": stdout,
        "stdout_truncated": stdout_truncated,
        "stderr": stderr,
        "stderr_truncated": stderr_truncated,
    }


def report_path(value: str | Path) -> Path:
    requested = Path(value)
    result = requested if requested.is_absolute() else ROOT / requested
    try:
        result.resolve().relative_to(WORK.resolve())
    except ValueError as error:
        raise argparse.ArgumentTypeError("report paths must remain below ignored work/") from error
    return result


def write_summary(path: Path, summary: dict[str, object]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n")
    temporary.replace(path)


def parser() -> argparse.ArgumentParser:
    result = argparse.ArgumentParser(description=__doc__)
    result.add_argument(
        "--report",
        type=report_path,
        help="append-only JSONL proof report below work/ (default is shard-specific)",
    )
    result.add_argument(
        "--summary", type=report_path, help="JSON summary path (default: beside report)"
    )
    result.add_argument("--function", action="append", help="function glob; repeatable")
    result.add_argument(
        "--source", action="append", help="repository-relative source glob; repeatable"
    )
    result.add_argument("--profile", action="append", help="exact claimed profile; repeatable")
    result.add_argument("--address-start", type=lambda value: int(value, 0))
    result.add_argument("--address-end", type=lambda value: int(value, 0))
    result.add_argument("--shard-index", type=int, default=0)
    result.add_argument("--shard-count", type=int, default=1)
    result.add_argument("--limit", type=int, help="run at most this many selected unique proofs")
    result.add_argument(
        "--no-resume",
        action="store_true",
        help="ignore prior records and replay all selected proofs",
    )
    result.add_argument(
        "--retry-failures",
        action="store_true",
        help="replay cached fail, unsafe, or stale records",
    )
    result.add_argument(
        "--output-limit",
        type=int,
        default=16384,
        help="saved stdout/stderr characters per stream",
    )
    result.add_argument(
        "--list",
        action="store_true",
        help="validate and list selected proofs without compiling",
    )
    return result


def main(argv: Iterable[str] | None = None) -> int:
    args = parser().parse_args(argv)
    if args.shard_count <= 0 or not 0 <= args.shard_index < args.shard_count:
        raise LedgerError("shard index must satisfy 0 <= index < count")
    if args.limit is not None and args.limit < 0:
        raise LedgerError("limit must be non-negative")
    if args.output_limit < 0:
        raise LedgerError("output-limit must be non-negative")
    if (
        args.address_start is not None
        and args.address_end is not None
        and args.address_end <= args.address_start
    ):
        raise LedgerError("address-end must be greater than address-start")
    if args.report is None:
        shard_suffix = (
            ""
            if args.shard_count == 1
            else f".shard-{args.shard_index:03d}-of-{args.shard_count:03d}"
        )
        args.report = WORK / "ledger-reverify" / f"proofs{shard_suffix}.jsonl"

    toolchains = load_json(TOOLCHAINS, dict)
    assert isinstance(toolchains, dict)
    profiles = toolchains.get("profiles")
    if not isinstance(profiles, dict):
        raise LedgerError("config/toolchains.json has invalid profiles")
    unknown_profiles = sorted(set(args.profile or ()) - set(profiles))
    if unknown_profiles:
        raise LedgerError("unknown profile filters: " + ", ".join(unknown_profiles))
    ledger = load_json(LEDGER, list)
    catalog = load_json(CATALOG, dict)
    assert isinstance(ledger, list) and isinstance(catalog, dict)
    catalog_entries = catalog.get("functions")
    if not isinstance(catalog_entries, list):
        raise LedgerError("config/functions.json has invalid functions")
    proofs = build_proofs(ledger, catalog_entries, profiles)
    selected = [
        proof
        for proof in proofs
        if matches_filters(proof, args) and shard_for(proof, args.shard_count) == args.shard_index
    ]
    if args.limit is not None:
        selected = selected[: args.limit]
    selected_claims = sum(len(proof.claims) for proof in selected)
    print(
        f"selected {len(selected)} unique unit/profile proofs covering "
        f"{selected_claims} function/profile claims"
    )
    if args.list:
        for proof in selected:
            functions = ",".join(claim.function for claim in proof.claims)
            print(
                f"{proof.profile} {proof.source} 0x{proof.start:08X}-0x{proof.end:08X} "
                f"claims={functions}"
            )
        return 0

    dependency_hash = dependency_fingerprint(toolchains)
    resume = {} if args.no_resume else read_resume(args.report)
    counts = {
        "pass": 0,
        "fail": 0,
        "unsafe": 0,
        "stale": 0,
        "reused": 0,
        "executed": 0,
    }
    final_records: list[dict[str, object]] = []
    for position, proof in enumerate(selected, 1):
        identifier = proof_id(proof, dependency_hash)
        cached = resume.get(identifier)
        if cached is not None and not resume_record_valid(
            cached, proof, identifier, dependency_hash
        ):
            print(
                f"warning: ignoring invalid resume record for {identifier}",
                file=sys.stderr,
            )
            cached = None
        if cached is not None and not (
            args.retry_failures and cached.get("status") in {"fail", "unsafe", "stale"}
        ):
            record = cached
            counts["reused"] += 1
            marker = "REUSE"
        else:
            record = run_proof(proof, identifier, dependency_hash, args.output_limit)
            append_record(args.report, record)
            counts["executed"] += 1
            marker = str(record["status"]).upper()
        status = str(record.get("status"))
        if status in {"pass", "fail", "unsafe", "stale"}:
            counts[status] += 1
        else:
            counts["fail"] += 1
        final_records.append(record)
        print(
            f"[{position}/{len(selected)}] {marker:6} {proof.profile} {proof.source} "
            f"0x{proof.start:08X}-0x{proof.end:08X} claims={len(proof.claims)}",
            flush=True,
        )

    final_dependency_hash = dependency_fingerprint(toolchains)
    inputs_stable = final_dependency_hash == dependency_hash
    failed_claims = sum(
        len(proof.claims)
        for proof, record in zip(selected, final_records)
        if record.get("status") != "pass"
    )
    summary_path = args.summary or args.report.with_name(args.report.stem + ".summary.json")
    summary = {
        "schema": SCHEMA,
        "type": "summary",
        "timestamp_utc": dt.datetime.now(dt.timezone.utc).isoformat(),
        "ledger_entries": len(ledger),
        "ledger_profile_claims": sum(
            len(entry.get("verified_profiles", [])) for entry in ledger
        ),
        "all_unique_proofs": len(proofs),
        "selected_unique_proofs": len(selected),
        "selected_claims": selected_claims,
        "failed_claims": failed_claims,
        "counts": counts,
        "dependency_fingerprint": dependency_hash,
        "inputs_stable_during_run": inputs_stable,
        "report": str(args.report.relative_to(ROOT)),
        "filters": {
            "function": args.function or [],
            "source": args.source or [],
            "profile": args.profile or [],
            "address_start": args.address_start,
            "address_end": args.address_end,
            "shard_index": args.shard_index,
            "shard_count": args.shard_count,
            "limit": args.limit,
        },
        "ok": failed_claims == 0 and inputs_stable,
    }
    write_summary(summary_path, summary)
    print(
        f"proofs: {counts['pass']} pass, {counts['fail']} fail, {counts['unsafe']} unsafe, "
        f"{counts['stale']} stale; "
        f"{counts['executed']} executed, {counts['reused']} resumed"
    )
    print(f"summary: {summary_path.relative_to(ROOT)}")
    if not inputs_stable:
        print("error: proof dependencies changed during the run; rerun required", file=sys.stderr)
        return 2
    return 1 if failed_claims else 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except LedgerError as error:
        print(f"error: {error}", file=sys.stderr)
        raise SystemExit(2)
