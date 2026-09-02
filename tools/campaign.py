#!/usr/bin/env python3
"""Coordinate parallel, restartable Chulip matching work.

Campaign data is local-only under ``work/campaign``.  A candidate becomes
public progress only after ``match.py`` proves it and ``merge_candidates.py``
replays that proof as part of its transactional full-build import.
"""

from __future__ import annotations

import argparse
import contextlib
import datetime as dt
import fcntl
import hashlib
import json
import os
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import time
from pathlib import Path

import batch_verify
import candidate_queue
import similar_functions
from build_controls import object_flag_errors
from compiler_diagnostics import dangerous_diagnostics
from merge_candidates import source_has_definition
from source_audit import audit_c_source

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT / "work/campaign"
PACKETS = WORK / "packets"
CLAIMS = WORK / "claims"
VERIFIED = WORK / "verified"
STATE = WORK / "state.json"
ATTEMPTS = WORK / "attempts.jsonl"
LOCK = WORK / ".lock"
PROMOTE_LOCK = WORK / ".promote.lock"
CATALOG = ROOT / "config/functions.json"
RECONSTRUCTED = ROOT / "config/reconstructed.json"
MATCHED = ROOT / "config/matched.json"
TOOLCHAINS = ROOT / "config/toolchains.json"
UTC = dt.timezone.utc
FUNCTION_NAME = re.compile(r"^[A-Za-z_$][A-Za-z0-9_.$]*$")


def read_json(path: Path, default: object) -> object:
    if not path.is_file():
        return default
    return json.loads(path.read_text())


def atomic_json(path: Path, value: object) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary_name = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    temporary = Path(temporary_name)
    try:
        with os.fdopen(descriptor, "w") as stream:
            json.dump(value, stream, indent=2, sort_keys=True)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()


@contextlib.contextmanager
def campaign_lock(timeout: float = 10.0):
    WORK.mkdir(parents=True, exist_ok=True)
    deadline = time.monotonic() + timeout
    while True:
        try:
            LOCK.mkdir()
            break
        except FileExistsError:
            try:
                stale = time.time() - LOCK.stat().st_mtime > 30.0
            except FileNotFoundError:
                continue
            if stale:
                try:
                    LOCK.rmdir()
                except (FileNotFoundError, OSError):
                    pass
                continue
            if time.monotonic() >= deadline:
                raise SystemExit("campaign state is locked by another worker")
            time.sleep(0.05)
    try:
        yield
    finally:
        LOCK.rmdir()


def now() -> dt.datetime:
    return dt.datetime.now(UTC)


def timestamp(value: dt.datetime) -> str:
    return value.astimezone(UTC).isoformat().replace("+00:00", "Z")


def parse_timestamp(value: object) -> dt.datetime:
    return dt.datetime.fromisoformat(str(value).replace("Z", "+00:00"))


def catalog_by_name() -> dict[str, dict[str, object]]:
    document = read_json(CATALOG, {"functions": []})
    assert isinstance(document, dict)
    return {str(entry["name"]): entry for entry in document["functions"]}


def reconstructed_names() -> set[str]:
    entries = read_json(RECONSTRUCTED, [])
    assert isinstance(entries, list)
    return {str(entry["function"]) for entry in entries}


def claim_path(function: str) -> Path:
    if not FUNCTION_NAME.fullmatch(function):
        raise SystemExit(f"invalid function name: {function!r}")
    return CLAIMS / f"{function}.json"


def claim_state(path: Path, at: dt.datetime | None = None) -> tuple[dict[str, object], bool]:
    value = read_json(path, {})
    if not isinstance(value, dict):
        return {}, False
    try:
        active = parse_timestamp(value["expires_at"]) > (at or now())
    except (KeyError, TypeError, ValueError):
        active = False
    return value, active


def active_claims(at: dt.datetime | None = None) -> dict[str, dict[str, object]]:
    result: dict[str, dict[str, object]] = {}
    for path in sorted(CLAIMS.glob("*.json")) if CLAIMS.is_dir() else []:
        value, active = claim_state(path, at)
        if active:
            result[path.stem] = value
    return result


def acquire(function: str, owner: str, hours: float) -> dict[str, object]:
    if function not in catalog_by_name():
        raise SystemExit(f"unknown function: {function}")
    if function in reconstructed_names():
        raise SystemExit(f"function is already reconstructed: {function}")
    if not owner.strip():
        raise SystemExit("owner must not be empty")
    if hours <= 0:
        raise SystemExit("lease duration must be positive")
    path = claim_path(function)
    with campaign_lock():
        existing, active = claim_state(path)
        if active and existing.get("owner") != owner:
            raise SystemExit(
                f"{function} is claimed by {existing.get('owner')} until "
                f"{existing.get('expires_at')}"
            )
        acquired = now()
        value = {
            "schema": 1,
            "function": function,
            "owner": owner,
            "acquired_at": (
                existing.get("acquired_at", timestamp(acquired))
                if active
                else timestamp(acquired)
            ),
            "renewed_at": timestamp(acquired),
            "expires_at": timestamp(acquired + dt.timedelta(hours=hours)),
        }
        atomic_json(path, value)
    return value


def release(function: str, owner: str, *, force: bool = False) -> None:
    path = claim_path(function)
    with campaign_lock():
        existing, active = claim_state(path)
        if not path.exists():
            raise SystemExit(f"no claim exists for {function}")
        if active and existing.get("owner") != owner and not force:
            raise SystemExit(f"{function} is owned by {existing.get('owner')}, not {owner}")
        path.unlink()


def nearest_references(function: str, limit: int = 5) -> list[dict[str, object]]:
    try:
        index = similar_functions.build_opcode_index()
        target = index[function]
    except Exception:
        return []
    matched_entries = read_json(MATCHED, [])
    assert isinstance(matched_entries, list)
    matched = {str(entry["function"]): entry for entry in matched_entries}
    scored = sorted(
        (
            (similar_functions.similarity(target, sequence), name)
            for name, sequence in index.items()
            if name != function and name in matched
        ),
        reverse=True,
    )
    result = []
    for score, name in scored:
        if score < 0.30:
            continue
        entry = matched[name]
        result.append(
            {
                "function": name,
                "similarity": round(score, 3),
                "source": entry.get("source"),
                "profile": entry.get("profile"),
            }
        )
        if len(result) == limit:
            break
    return result


def ranked_targets() -> list[dict[str, object]]:
    catalog = list(catalog_by_name().values())
    excluded = reconstructed_names() | set(active_claims())
    assembly = candidate_queue.assembly_functions()
    reconstructed = reconstructed_names()
    rows = [
        candidate_queue.features(
            entry, assembly.get(str(entry["name"]), ""), reconstructed
        )
        for entry in catalog
        if str(entry["name"]) not in excluded and int(entry["size"]) >= 8
    ]
    rows.sort(key=lambda row: (float(row["score"]), int(row["size"]), str(row["address"])))
    return rows


def assembly_slice(function: str) -> tuple[str | None, str]:
    start_marker = f"glabel {function}"
    end_marker = f"endlabel {function}"
    for path in sorted((ROOT / "asm").rglob("*.s")):
        lines = path.read_text(errors="replace").splitlines()
        try:
            start = next(index for index, line in enumerate(lines) if line.strip() == start_marker)
        except StopIteration:
            continue
        end = next(
            (
                index + 1
                for index in range(start + 1, len(lines))
                if lines[index].strip() == end_marker
            ),
            next(
                (
                    index
                    for index in range(start + 1, len(lines))
                    if lines[index].startswith("glabel ")
                ),
                len(lines),
            ),
        )
        return str(path.relative_to(ROOT)), "\n".join(lines[start:end]) + "\n"
    return None, ""


def usage_hits(function: str, limit: int = 40) -> list[str]:
    result: list[str] = []
    pattern = re.compile(rf"\b{re.escape(function)}\b")
    for path in sorted((ROOT / "src").rglob("*.[ch]")):
        for number, line in enumerate(path.read_text(errors="replace").splitlines(), 1):
            if pattern.search(line):
                result.append(f"{path.relative_to(ROOT)}:{number}:{line.strip()}")
                if len(result) == limit:
                    return result
    return result


def analysis_context(function: str, address: object) -> tuple[str | None, str]:
    """Find a local Ghidra export without making it part of public evidence."""
    address_text = f"{int(str(address), 0):08x}"
    exact = ROOT / "work/ghidra/src" / f"{function}.c"
    candidates = [exact] if exact.is_file() else []
    decompiled = ROOT / "work/ghidra-decompiled"
    if decompiled.is_dir():
        candidates.extend(sorted(decompiled.rglob(f"{address_text}_*.c")))
    if not candidates:
        return None, ""
    path = candidates[0]
    text = path.read_text(errors="replace")
    if len(text) > 20000:
        text = text[:20000] + "\n/* truncated in packet */\n"
    return str(path.relative_to(ROOT)), text


def prior_candidate_paths(function: str, limit: int = 30) -> list[str]:
    work = ROOT / "work"
    if not work.is_dir():
        return []
    result = []
    for path in sorted(work.rglob(f"*{function}*.c")):
        if WORK in path.parents:
            continue
        result.append(str(path.relative_to(ROOT)))
        if len(result) == limit:
            break
    return result


def write_packet(function: str, owner: str, hours: float) -> Path:
    entry = catalog_by_name()[function]
    asm_path, assembly = assembly_slice(function)
    if asm_path is None or not assembly:
        raise SystemExit(
            f"generated assembly for {function} is missing; run make split first"
        )
    references = nearest_references(function)
    analysis_path, analysis = analysis_context(function, entry["address"])
    prior = prior_candidate_paths(function)
    lease = acquire(function, owner, hours)
    packet_dir = PACKETS / function
    candidates = packet_dir / "candidates"
    candidates.mkdir(parents=True, exist_ok=True)
    packet = {
        "schema": 1,
        "function": function,
        "address": entry["address"],
        "size": entry["size"],
        "ownership": entry.get("ownership"),
        "handwritten": bool(entry.get("handwritten")),
        "assembly_source": asm_path,
        "analysis_source": analysis_path,
        "claim": lease,
        "references": references,
        "prior_candidates": prior,
        "usage_hits": usage_hits(function),
    }
    atomic_json(packet_dir / "packet.json", packet)
    (packet_dir / "retail.s").write_text(assembly)
    analysis_file = packet_dir / "analysis.c"
    if analysis:
        analysis_file.write_text(analysis)
    elif analysis_file.exists():
        analysis_file.unlink()
    reference_lines = "\n".join(
        f"- `{item['function']}` {item['similarity']:.3f}: `{item.get('source') or '?'}` "
        f"(`{item.get('profile') or '?'}`)"
        for item in references
    ) or "- None above the similarity threshold."
    readme = f"""# {function}

Address `{entry['address']}`, {entry['size']} bytes. Claimed by `{owner}` until
`{lease['expires_at']}`.

Put C candidates in `candidates/`. A candidate must define `{function}`.
Optional metadata goes in a sibling file such as `candidate.c.json`:

```json
{{
  "profiles": ["ee-gcc2.95.3-136-O2-G8"],
  "build_profile": "ee-gcc2.95.3-136-O2-G8",
  "object_flags": [],
  "destination": "src/game/{function}.c"
}}
```

From the repository root:

```sh
python3 tools/campaign.py harvest work/campaign/packets/{function}/candidates
python3 tools/campaign.py promote {function}
```

`promote` is a dry run. Add `--write` only after reviewing the C and the reported exact proof.

## Matched references

{reference_lines}

The assembly is in `retail.s`; machine-generated packet data is in
`packet.json`. A local Ghidra export, when available, is copied to `analysis.c`
as a non-authoritative reference. `tools/match.py` and
`tools/merge_candidates.py` are the proof authorities.
"""
    (packet_dir / "README.md").write_text(readme)
    return packet_dir


def candidate_files(paths: list[Path]) -> list[Path]:
    roots = paths or [PACKETS]
    found: set[Path] = set()
    for value in roots:
        path = value if value.is_absolute() else ROOT / value
        if path.is_file() and path.suffix == ".c":
            found.add(path.resolve())
        elif path.is_dir():
            found.update(item.resolve() for item in path.rglob("*.c"))
        else:
            raise SystemExit(f"candidate path does not exist: {path}")
    return sorted(found)


def packet_function(source: Path) -> str:
    try:
        relative = source.resolve().relative_to(PACKETS.resolve())
    except ValueError as error:
        raise SystemExit(f"candidate is outside campaign packets: {source}") from error
    if len(relative.parts) < 3 or relative.parts[1] != "candidates":
        raise SystemExit(f"candidate must be under packets/<function>/candidates: {source}")
    return relative.parts[0]


def candidate_spec(source: Path) -> dict[str, object]:
    function = packet_function(source)
    sidecar = Path(str(source) + ".json")
    value = read_json(sidecar, {})
    if not isinstance(value, dict):
        raise SystemExit(f"candidate metadata must be a JSON object: {sidecar}")
    allowed = {
        "function", "profiles", "build_profile", "object_flags", "range_start", "range_end",
        "rodata_start", "sdata_start", "sbss_start", "destination",
    }
    unknown = sorted(set(value) - allowed)
    if unknown:
        raise SystemExit(f"unknown candidate metadata in {sidecar}: {', '.join(unknown)}")
    if value.get("function", function) != function:
        raise SystemExit(f"candidate metadata function disagrees with packet: {sidecar}")
    profiles_document = read_json(TOOLCHAINS, {"profiles": {}})
    assert isinstance(profiles_document, dict)
    known_profiles = list(profiles_document["profiles"])
    profiles = value.get("profiles", known_profiles)
    if (
        not isinstance(profiles, list)
        or not profiles
        or not all(isinstance(item, str) for item in profiles)
    ):
        raise SystemExit(f"profiles must be a non-empty string list: {sidecar}")
    unknown_profiles = sorted(set(profiles) - set(known_profiles))
    if unknown_profiles:
        raise SystemExit("unknown profiles: " + ", ".join(unknown_profiles))
    build_profile = value.get("build_profile")
    if build_profile is not None and build_profile not in profiles:
        raise SystemExit(f"build_profile must appear in profiles: {sidecar}")
    flags = value.get("object_flags", [])
    errors = object_flag_errors(flags)
    if errors:
        raise SystemExit(f"invalid object_flags in {sidecar}: {'; '.join(errors)}")
    has_start = value.get("range_start") is not None
    has_end = value.get("range_end") is not None
    if has_start != has_end:
        raise SystemExit(f"range_start and range_end must appear together: {sidecar}")
    destination = value.get("destination", f"src/game/{function}.c")
    if not isinstance(destination, str):
        raise SystemExit(f"destination must be a string: {sidecar}")
    pure = Path(destination)
    if (
        pure.is_absolute()
        or ".." in pure.parts
        or pure.parts[:1] != ("src",)
        or pure.suffix != ".c"
    ):
        raise SystemExit(
            f"destination must be a repository-relative path below src/: {destination}"
        )
    return {
        "function": function,
        "profiles": profiles,
        "build_profile": build_profile,
        "object_flags": list(flags),
        "range_start": value.get("range_start"),
        "range_end": value.get("range_end"),
        "rodata_start": value.get("rodata_start"),
        "sdata_start": value.get("sdata_start"),
        "sbss_start": value.get("sbss_start"),
        "destination": destination,
    }


def experiment_key(source: Path, spec: dict[str, object]) -> str:
    digest = hashlib.sha256(source.read_bytes())
    digest.update(json.dumps(spec, sort_keys=True, separators=(",", ":")).encode())
    return digest.hexdigest()


def match_command(source: Path, spec: dict[str, object], profile: str) -> list[str]:
    entry = {
        "function": spec["function"],
        "object_flags": spec["object_flags"],
        "range_start": spec["range_start"],
        "range_end": spec["range_end"],
        "rodata_start": spec["rodata_start"],
        "sdata_start": spec["sdata_start"],
        "sbss_start": spec["sbss_start"],
    }
    return batch_verify.command(entry, source, profile)


def append_attempt(record: dict[str, object]) -> None:
    with campaign_lock():
        ATTEMPTS.parent.mkdir(parents=True, exist_ok=True)
        with ATTEMPTS.open("a") as stream:
            stream.write(json.dumps(record, sort_keys=True) + "\n")
            stream.flush()
            os.fsync(stream.fileno())


def verify_source(
    source: Path, *, recheck: bool = False, timeout: float = 300.0
) -> dict[str, object]:
    spec = candidate_spec(source)
    function = str(spec["function"])
    text = source.read_text(errors="replace")
    issues = audit_c_source(source, repo_root=ROOT)
    if issues:
        raise SystemExit(issues[0].format(ROOT))
    if not source_has_definition(text, function, source):
        raise SystemExit(f"candidate does not define {function}: {source}")
    if batch_verify.FORBIDDEN_BRIDGES.search(text):
        found = batch_verify.FORBIDDEN_BRIDGES.search(text)
        assert found is not None
        raise SystemExit(f"assembly bridge rejected in {source}: {found.group(0).strip()}")
    key = experiment_key(source, spec)
    state = read_json(STATE, {"schema": 1, "experiments": {}})
    assert isinstance(state, dict)
    experiments = state.setdefault("experiments", {})
    assert isinstance(experiments, dict)
    if not recheck and key in experiments:
        cached = experiments[key]
        assert isinstance(cached, dict)
        if cached.get("exact"):
            atomic_json(VERIFIED / f"{function}-{key[:12]}.json", cached)
        return cached

    attempts: dict[str, dict[str, object]] = {}
    matched: list[str] = []
    for profile in spec["profiles"]:
        command = match_command(source, spec, str(profile))
        try:
            proof = subprocess.run(
                command,
                cwd=ROOT,
                capture_output=True,
                text=True,
                timeout=timeout,
            )
            returncode = proof.returncode
            output = (proof.stdout + proof.stderr).strip()
        except subprocess.TimeoutExpired as error:
            returncode = 124
            output = f"timeout after {timeout:g}s: {error}"
        attempts[str(profile)] = {
            "returncode": returncode,
            "summary": output[:1000],
        }
        dangerous = dangerous_diagnostics(output)
        if dangerous:
            attempts[str(profile)]["dangerous_diagnostics"] = dangerous
        if returncode == 0 and not dangerous:
            matched.append(str(profile))
    record = {
        "schema": 1,
        "key": key,
        "checked_at": timestamp(now()),
        "function": function,
        "source": str(source.relative_to(ROOT)),
        "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
        "matched_profiles": matched,
        "attempts": attempts,
        "exact": bool(matched),
        "spec": spec,
    }
    append_attempt(record)
    with campaign_lock():
        current = read_json(STATE, {"schema": 1, "experiments": {}})
        assert isinstance(current, dict)
        current_experiments = current.setdefault("experiments", {})
        assert isinstance(current_experiments, dict)
        current_experiments[key] = record
        atomic_json(STATE, current)
    if matched:
        atomic_json(VERIFIED / f"{function}-{key[:12]}.json", record)
    return record


def verified_records(function: str) -> list[tuple[Path, dict[str, object]]]:
    result = []
    for path in sorted(VERIFIED.glob(f"{function}-*.json")) if VERIFIED.is_dir() else []:
        value = read_json(path, {})
        if isinstance(value, dict) and value.get("exact"):
            result.append((path, value))
    return result


def promotion_manifest(record: dict[str, object], destination: str) -> dict[str, object]:
    spec = record["spec"]
    assert isinstance(spec, dict)
    profiles = record["matched_profiles"]
    assert isinstance(profiles, list) and profiles
    build_profile = spec.get("build_profile")
    if build_profile is None:
        if len(profiles) != 1:
            raise SystemExit(
                "candidate matches multiple profiles; record a reviewed build_profile "
                "in its metadata and harvest it again"
            )
        build_profile = profiles[0]
    if build_profile not in profiles:
        raise SystemExit("reviewed build_profile did not produce an exact match")
    candidate: dict[str, object] = {
        "function": record["function"],
        "source": destination,
        "build_profile": build_profile,
        "verified_profiles": profiles,
        "object_flags": spec["object_flags"],
        "evidence": (
            "isolated exact match discovered by the restartable campaign and "
            "independently replayed during transactional import"
        ),
        "provenance_note": (
            "authentic translation-unit ownership remains provisional unless "
            "an explicit unit range is recorded"
        ),
    }
    if spec.get("range_start") is not None:
        candidate["unit_start"] = spec["range_start"]
        candidate["unit_end"] = spec["range_end"]
    if spec.get("rodata_start") is not None:
        candidate["rodata_start"] = spec["rodata_start"]
    return candidate


class PromotionInterrupted(BaseException):
    """Raised when a signal reaches a promotion so its cleanup still runs."""


@contextlib.contextmanager
def cleanup_on_termination():
    """Unwind promotions that receive SIGTERM or SIGINT.

    Lanes wrap promotions in ``timeout``.  The default SIGTERM disposition
    exits without running ``finally`` blocks, which strands the copied
    candidate in ``src`` as an unledgered public source; every later import
    then fails its repository audit until the file is removed by hand.
    """

    def interrupt(number, _frame):
        raise PromotionInterrupted(f"promotion terminated by signal {number}")

    restore: dict[int, object] = {}
    for number in (signal.SIGTERM, signal.SIGINT):
        try:
            restore[number] = signal.getsignal(number)
            signal.signal(number, interrupt)
        except (OSError, ValueError):
            continue
    try:
        yield
    finally:
        for number, previous in restore.items():
            with contextlib.suppress(OSError, ValueError):
                signal.signal(number, previous)


@contextlib.contextmanager
def promote_transaction_lock():
    """Serialize whole promotions, the copy into ``src`` included.

    ``merge_candidates.py`` already locks ``work/promotion.lock`` around the
    ledger generation, but a promotion becomes visible to every other worker
    the moment the candidate lands in ``src``: a concurrent import reads that
    unledgered public source and fails.  Hold a campaign-side descriptor
    across the copy as well.  It is deliberately not the merge lock, which the
    child acquires for itself and would deadlock against its own parent.
    """
    WORK.mkdir(parents=True, exist_ok=True)
    handle = PROMOTE_LOCK.open("a+")
    try:
        fcntl.flock(handle, fcntl.LOCK_EX)
        yield
    finally:
        handle.close()


def promote(function: str, *, record_path: Path | None, write: bool) -> int:
    records = verified_records(function)
    if record_path is not None:
        selected_path = record_path if record_path.is_absolute() else ROOT / record_path
        selected = read_json(selected_path, {})
        if (
            not isinstance(selected, dict)
            or not selected.get("exact")
            or selected.get("function") != function
        ):
            raise SystemExit(f"not an exact verified record for {function}: {selected_path}")
        record = selected
    elif len(records) == 1:
        selected_path, record = records[0]
    elif not records:
        raise SystemExit(f"no exact verified campaign candidate for {function}")
    else:
        choices = "\n  ".join(str(path.relative_to(ROOT)) for path, _ in records)
        raise SystemExit(f"multiple exact candidates; select one with --record:\n  {choices}")
    source = ROOT / str(record["source"])
    if hashlib.sha256(source.read_bytes()).hexdigest() != record.get("source_sha256"):
        raise SystemExit("verified candidate changed; harvest it again")
    spec = record["spec"]
    assert isinstance(spec, dict)
    destination = str(spec["destination"])
    target = ROOT / destination
    manifest_path = WORK / "promotions" / f"{function}.jsonl"
    manifest_path.parent.mkdir(parents=True, exist_ok=True)
    with cleanup_on_termination(), promote_transaction_lock():
        if target.exists():
            raise SystemExit(f"promotion destination already exists: {destination}")
        target.parent.mkdir(parents=True, exist_ok=True)
        copied = False
        try:
            shutil.copyfile(source, target)
            copied = True
            issues = audit_c_source(target, repo_root=ROOT)
            if issues:
                raise SystemExit(issues[0].format(ROOT))
            manifest = promotion_manifest(record, destination)
            manifest_path.write_text(json.dumps(manifest, sort_keys=True) + "\n")
            command = [
                sys.executable,
                "tools/merge_candidates.py",
                str(manifest_path.relative_to(ROOT)),
            ]
            if write:
                command.append("--write")
            merge = subprocess.Popen(command, cwd=ROOT)
            try:
                returncode = merge.wait()
            except BaseException:
                # Never leave the import running against a ledger this
                # promotion is about to roll back.
                merge.terminate()
                with contextlib.suppress(subprocess.TimeoutExpired):
                    merge.wait(timeout=60)
                if merge.poll() is None:
                    merge.kill()
                    merge.wait()
                raise
            if returncode:
                return returncode
            if write:
                copied = False
                try:
                    owner = str(claim_state(claim_path(function))[0].get("owner", ""))
                    release(function, owner, force=True)
                except SystemExit:
                    pass
            return 0
        finally:
            if copied and target.exists():
                target.unlink()


def show_plan(limit: int, as_json: bool) -> None:
    rows = ranked_targets()[:limit]
    if as_json:
        print(json.dumps(rows, indent=2))
        return
    print("rank  cost/B bytes call br glob gp fp ee raw dep function")
    for rank, row in enumerate(rows, 1):
        print(
            f"{rank:4} {row['score']:7.2f} {row['size']:5} {row['calls']:4} "
            f"{row['branches']:2} {row['globals']:4} {row['gp_refs']:2} "
            f"{row['float_ops']:2} {row['ee_ops']:2} {row['unknown_words']:3} "
            f"{row['pending_callees']:3} {row['function']}"
        )


def show_status(as_json: bool) -> None:
    at = now()
    active = active_claims(at)
    stale = []
    for path in sorted(CLAIMS.glob("*.json")) if CLAIMS.is_dir() else []:
        _value, is_active = claim_state(path, at)
        if not is_active:
            stale.append(path.stem)
    packets = (
        sorted(path.name for path in PACKETS.iterdir() if path.is_dir())
        if PACKETS.is_dir()
        else []
    )
    exact = []
    if VERIFIED.is_dir():
        exact = sorted(
            {
                str(value["function"])
                for path in VERIFIED.glob("*.json")
                if isinstance((value := read_json(path, {})), dict) and value.get("exact")
            }
        )
    status = {
        "active_claims": active,
        "stale_claims": stale,
        "packets": packets,
        "verified_functions": exact,
    }
    if as_json:
        print(json.dumps(status, indent=2, sort_keys=True))
    else:
        print(f"active claims: {len(active)}")
        for function, claim in active.items():
            print(f"  {function}: {claim.get('owner')} until {claim.get('expires_at')}")
        print(f"stale claims: {len(stale)}")
        print(f"packets: {len(packets)}")
        print(f"verified candidates: {len(exact)}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)

    plan = subparsers.add_parser("plan", help="rank currently unclaimed unmatched functions")
    plan.add_argument("--limit", type=int, default=50)
    plan.add_argument("--json", action="store_true")

    claim = subparsers.add_parser("claim", help="claim or renew one function")
    claim.add_argument("function")
    claim.add_argument("--owner", required=True)
    claim.add_argument("--lease-hours", type=float, default=8.0)

    packet = subparsers.add_parser(
        "packet", help="claim a function and materialize its work packet"
    )
    packet.add_argument("function", nargs="?")
    packet.add_argument("--next", action="store_true", dest="take_next")
    packet.add_argument("--owner", required=True)
    packet.add_argument("--lease-hours", type=float, default=8.0)

    release_parser = subparsers.add_parser("release", help="release a function claim")
    release_parser.add_argument("function")
    release_parser.add_argument("--owner", required=True)
    release_parser.add_argument("--force", action="store_true")

    harvest = subparsers.add_parser("harvest", help="verify new or changed packet candidates")
    harvest.add_argument("paths", nargs="*", type=Path)
    harvest.add_argument("--recheck", action="store_true")
    harvest.add_argument("--timeout", type=float, default=300.0, help="seconds allowed per profile")

    promotion = subparsers.add_parser(
        "promote", help="send an exact candidate through transactional import"
    )
    promotion.add_argument("function")
    promotion.add_argument("--record", type=Path)
    promotion.add_argument("--write", action="store_true")

    status = subparsers.add_parser("status", help="summarize local campaign state")
    status.add_argument("--json", action="store_true")

    args = parser.parse_args()
    if args.command == "plan":
        show_plan(args.limit, args.json)
    elif args.command == "claim":
        print(json.dumps(acquire(args.function, args.owner, args.lease_hours), indent=2))
    elif args.command == "packet":
        if bool(args.function) == bool(args.take_next):
            raise SystemExit("provide exactly one of FUNCTION or --next")
        function = args.function
        if args.take_next:
            rows = ranked_targets()
            if not rows:
                raise SystemExit("no unmatched unclaimed functions remain")
            function = str(rows[0]["function"])
        assert function is not None
        print(write_packet(function, args.owner, args.lease_hours).relative_to(ROOT))
    elif args.command == "release":
        release(args.function, args.owner, force=args.force)
        print(f"released {args.function}")
    elif args.command == "harvest":
        failures = 0
        sources = candidate_files(args.paths)
        if not sources:
            raise SystemExit("no C candidates found")
        for source in sources:
            record = verify_source(source, recheck=args.recheck, timeout=args.timeout)
            state = "MATCH" if record["exact"] else "MISS"
            profiles = ",".join(record["matched_profiles"]) or "-"
            print(f"{state:5} {record['function']} profiles={profiles} source={record['source']}")
            failures += not bool(record["exact"])
        return 1 if failures else 0
    elif args.command == "promote":
        return promote(args.function, record_path=args.record, write=args.write)
    elif args.command == "status":
        show_status(args.json)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
