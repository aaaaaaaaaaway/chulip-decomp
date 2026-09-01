#!/usr/bin/env python3
"""Report evidence that constrains authentic source-object boundaries.

The scanner deliberately separates mandatory boundaries from anchors and
compatibility observations. A successful combined compile is not promoted to
an authentic object boundary by this tool.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ELF = ROOT / "original/SLUS_207.42"
ROM = ROOT / "original/SLUS_207.42.rom"
CATALOG = ROOT / "config/functions.json"
RECONSTRUCTED = ROOT / "config/reconstructed.json"
BOUNDARY_EVIDENCE = ROOT / "config/object-boundary-evidence.json"
BASELINE_ASM = ROOT / "asm-baseline/cod/text.s"

SDK_MARKERS = (
    b"PsIIlibgraph2400",
    b"PsIIlibdma  2400",
    b"PsIIlibcdvd 2420",
    b"PsIIlibkernl2430",
)
METADATA_SECTIONS = (
    ".symtab",
    ".strtab",
    ".mdebug",
    ".pdr",
    ".debug_info",
    ".debug_line",
    ".rel.text",
    ".rela.text",
)
LABEL = re.compile(r"^glabel\s+(\S+)")
END = re.compile(r"^endlabel\b")
JUMP_TABLE = re.compile(r"\bjtbl_([0-9A-Fa-f]{8})\b")


def elf_sections(data: bytes) -> list[str]:
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
        raise SystemExit("expected a 32-bit little-endian ELF")
    shoff = struct.unpack_from("<I", data, 32)[0]
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 46)
    headers = [
        struct.unpack_from("<10I", data, shoff + index * shentsize)
        for index in range(shnum)
    ]
    strings_header = headers[shstrndx]
    strings = data[strings_header[4] : strings_header[4] + strings_header[5]]

    def name(offset: int) -> str:
        end = strings.find(b"\0", offset)
        return strings[offset : len(strings) if end < 0 else end].decode(
            "ascii", errors="replace"
        )

    return [name(header[0]) for header in headers]


def sdk_markers(elf: bytes, layout: dict[str, object]) -> list[dict[str, object]]:
    segment = layout["load_segment"]
    file_start = int(str(segment["file_offset"]), 16)
    file_end = file_start + int(str(segment["file_size"]), 16)
    vram = int(str(segment["vram"]), 16)
    result = []
    for marker in SDK_MARKERS:
        offset = elf.find(marker)
        address = vram + offset - file_start if file_start <= offset < file_end else None
        result.append(
            {
                "marker": marker.decode("ascii"),
                "file_offset": None if offset < 0 else f"0x{offset:X}",
                "vram": None if address is None else f"0x{address:08X}",
            }
        )
    return result


def is_syscall_stub(data: bytes) -> bool:
    if len(data) != 16:
        return False
    words = struct.unpack("<4I", data)
    return words[0] >> 16 == 0x2403 and words[1:] == (0x0000000C, 0x03E00008, 0)


def syscall_runs(rom: bytes, functions: list[dict[str, object]]) -> list[dict[str, object]]:
    stubs = []
    for entry in functions:
        address = int(str(entry["address"]), 16)
        size = int(entry["size"])
        body = rom[address - 0x00100000 : address - 0x00100000 + size]
        if size == 16 and is_syscall_stub(body):
            immediate = struct.unpack_from("<h", body, 0)[0]
            stubs.append((address, immediate, body))

    runs: list[list[tuple[int, int, bytes]]] = []
    for stub in stubs:
        if not runs or stub[0] != runs[-1][-1][0] + 16:
            runs.append([])
        runs[-1].append(stub)
    result = []
    for run in runs:
        payload = b"".join(stub[2] for stub in run)
        result.append(
            {
                "start": f"0x{run[0][0]:08X}",
                "end": f"0x{run[-1][0] + 16:08X}",
                "functions": len(run),
                "bytes": len(payload),
                "first_immediate": run[0][1],
                "last_immediate": run[-1][1],
                "sha256": hashlib.sha256(payload).hexdigest(),
            }
        )
    return sorted(result, key=lambda run: int(run["functions"]), reverse=True)


def jump_table_order() -> dict[str, object]:
    rows = []
    current: str | None = None
    references: set[int] = set()
    for line in BASELINE_ASM.read_text(errors="replace").splitlines():
        found = LABEL.match(line)
        if found:
            current = found.group(1)
            references = set()
            continue
        if current is not None:
            references.update(int(value, 16) for value in JUMP_TABLE.findall(line))
        if current is not None and END.match(line):
            if references:
                rows.append((current, tuple(sorted(references))))
            current = None
    reversals = []
    for left, right in zip(rows, rows[1:]):
        if min(right[1]) < min(left[1]):
            reversals.append({"left": left[0], "right": right[0]})
    return {
        "functions": len(rows),
        "tables": sum(len(row[1]) for row in rows),
        "order_reversals": reversals,
    }


def matrix_boundaries() -> list[dict[str, object]]:
    document = json.loads(BOUNDARY_EVIDENCE.read_text())
    result = []
    for matrix in document["configuration_matrices"]:
        profiles = {row["profile"] for row in matrix["results"]}
        flags = {row["object_flag"] for row in matrix["results"]}
        unexcluded = [
            row
            for row in matrix["results"]
            if row["left"] != "mismatch" and row["right"] != "mismatch"
        ]
        left_matches = [
            f"{row['profile']} {row['object_flag']}"
            for row in matrix["results"]
            if row["left"] == "match"
        ]
        right_matches = [
            f"{row['profile']} {row['object_flag']}"
            for row in matrix["results"]
            if row["right"] == "match"
        ]
        result.append(
            {
                "boundary": matrix["boundary"],
                "conclusion": matrix["conclusion"],
                "profiles": len(profiles),
                "assembler_thresholds": len(flags),
                "configurations": len(matrix["results"]),
                "all_configurations_excluded": not unexcluded,
                "unexcluded": unexcluded,
                "left_matches": left_matches,
                "right_matches": right_matches,
            }
        )
    return result


def classify_match_run(proof: subprocess.CompletedProcess[str]) -> str:
    output = proof.stdout + proof.stderr
    if proof.returncode == 0 and ": MATCH" in output:
        return "match"
    if ": MISMATCH" in output:
        return "mismatch"
    return "layout_error"


def verify_matrices() -> bool:
    document = json.loads(BOUNDARY_EVIDENCE.read_text())
    ok = True
    for matrix in document["configuration_matrices"]:
        for row in matrix["results"]:
            for side in ("left", "right"):
                subject = matrix[side]
                command = [
                    sys.executable,
                    "tools/match.py",
                    str(subject["function"]),
                    "--profile",
                    str(row["profile"]),
                    f"--object-flag={row['object_flag']}",
                    "--quiet",
                ]
                proof = subprocess.run(
                    command, cwd=ROOT, capture_output=True, text=True
                )
                actual = classify_match_run(proof)
                expected = str(row[side])
                state = "OK" if actual == expected else "DRIFT"
                print(
                    f"{state:5} {matrix['boundary']} {side:5} "
                    f"{row['profile']} {row['object_flag']}: {actual}"
                )
                if actual != expected:
                    ok = False
    return ok


def source_unit_summary(reconstructed: list[dict[str, object]]) -> dict[str, int]:
    sources: dict[str, int] = {}
    for entry in reconstructed:
        source = str(entry["source"])
        sources[source] = sources.get(source, 0) + 1
    shared = {source: count for source, count in sources.items() if count > 1}
    return {
        "source_files": len(sources),
        "shared_source_files": len(shared),
        "functions_in_shared_sources": sum(shared.values()),
    }


def report() -> dict[str, object]:
    elf = ELF.read_bytes()
    layout = json.loads((ROOT / "config/elf.json").read_text())
    sections = elf_sections(elf)
    functions = json.loads(CATALOG.read_text())["functions"]
    reconstructed = json.loads(RECONSTRUCTED.read_text())
    return {
        "elf": {
            "sections": sections,
            "surviving_boundary_metadata": [
                name for name in METADATA_SECTIONS if name in sections
            ],
            "missing_boundary_metadata": [
                name for name in METADATA_SECTIONS if name not in sections
            ],
        },
        "mandatory_boundaries": matrix_boundaries(),
        "sdk_version_markers": sdk_markers(elf, layout),
        "syscall_stub_runs": syscall_runs(ROM.read_bytes(), functions),
        "jump_table_order": jump_table_order(),
        "current_source_grouping": source_unit_summary(reconstructed),
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--json", type=Path, help="write the complete JSON report")
    parser.add_argument(
        "--verify-matrices",
        action="store_true",
        help="replay every recorded compiler matrix before reporting",
    )
    args = parser.parse_args()
    if args.verify_matrices and not verify_matrices():
        raise SystemExit("recorded object-boundary matrix has drifted")
    data = report()
    print(
        "surviving direct boundary metadata: "
        + (", ".join(data["elf"]["surviving_boundary_metadata"]) or "none")
    )
    for boundary in data["mandatory_boundaries"]:
        print(
            f"mandatory source boundary: {boundary['boundary']} "
            f"({boundary['configurations']} configurations; "
            f"all excluded={boundary['all_configurations_excluded']})"
        )
    for marker in data["sdk_version_markers"]:
        print(f"SDK marker: {marker['marker']} at {marker['vram'] or marker['file_offset']}")
    for run in data["syscall_stub_runs"][:3]:
        print(
            f"syscall run: {run['start']}-{run['end']} "
            f"{run['functions']} functions / {run['bytes']} bytes"
        )
    order = data["jump_table_order"]
    print(
        f"jump-table order: {order['functions']} functions / {order['tables']} tables / "
        f"{len(order['order_reversals'])} reversals"
    )
    grouping = data["current_source_grouping"]
    print(
        f"current shared-source grouping: {grouping['functions_in_shared_sources']} functions "
        f"in {grouping['shared_source_files']} files (compatibility, not provenance)"
    )
    if args.json:
        output = args.json if args.json.is_absolute() else ROOT / args.json
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(data, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
