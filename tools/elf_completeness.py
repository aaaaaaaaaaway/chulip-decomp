#!/usr/bin/env python3
"""Report load-image, ELF-container, and memory-layout completeness separately."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PT_LOAD = 1
SHT_NOBITS = 8
SHF_ALLOC = 2


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def checked_slice(blob: bytes, offset: int, size: int, description: str) -> bytes:
    end = offset + size
    if offset < 0 or size < 0 or end > len(blob):
        raise SystemExit(f"{description} lies outside its ELF file")
    return blob[offset:end]


def parse_elf(path: Path) -> dict[str, object]:
    blob = path.read_bytes()
    if len(blob) < 52 or blob[:7] != b"\x7fELF\x01\x01\x01":
        raise SystemExit(f"not a 32-bit little-endian ELF: {path}")
    fields = struct.unpack_from("<16sHHIIIIIHHHHHH", blob)
    header_names = (
        "ident",
        "type",
        "machine",
        "version",
        "entry",
        "phoff",
        "shoff",
        "flags",
        "ehsize",
        "phentsize",
        "phnum",
        "shentsize",
        "shnum",
        "shstrndx",
    )
    header = dict(zip(header_names, fields))
    if header["ehsize"] != 52 or header["phentsize"] not in (0, 32):
        raise SystemExit(f"unsupported ELF header layout: {path}")
    if header["shentsize"] not in (0, 40):
        raise SystemExit(f"unsupported ELF section layout: {path}")

    programs = []
    for index in range(header["phnum"]):
        offset = header["phoff"] + index * header["phentsize"]
        values = struct.unpack("<IIIIIIII", checked_slice(blob, offset, 32, "program header"))
        names = ("type", "offset", "vaddr", "paddr", "filesz", "memsz", "flags", "align")
        program = dict(zip(names, values))
        program["index"] = index
        if program["type"] == PT_LOAD:
            payload = checked_slice(blob, program["offset"], program["filesz"], "PT_LOAD data")
            program["sha256"] = sha256(payload)
        programs.append(program)

    raw_sections = []
    for index in range(header["shnum"]):
        offset = header["shoff"] + index * header["shentsize"]
        values = struct.unpack("<IIIIIIIIII", checked_slice(blob, offset, 40, "section header"))
        names = (
            "name_offset",
            "type",
            "flags",
            "addr",
            "offset",
            "size",
            "link",
            "info",
            "addralign",
            "entsize",
        )
        raw_sections.append(dict(zip(names, values)))
    names = b""
    if raw_sections:
        if header["shstrndx"] >= len(raw_sections):
            raise SystemExit(f"invalid section-name table index: {path}")
        table = raw_sections[header["shstrndx"]]
        names = checked_slice(blob, table["offset"], table["size"], "section-name table")

    sections = []
    for index, section in enumerate(raw_sections):
        start = section.pop("name_offset")
        end = names.find(b"\0", start) if start < len(names) else -1
        name = names[start:end].decode("ascii", errors="replace") if end >= 0 else ""
        section["index"] = index
        section["name"] = name
        sections.append(section)

    public_header = {key: value for key, value in header.items() if key != "ident"}
    public_header.update(
        {
            "class": header["ident"][4],
            "data": header["ident"][5],
            "ident_version": header["ident"][6],
            "osabi": header["ident"][7],
            "abi_version": header["ident"][8],
        }
    )
    return {
        "path": str(path),
        "size": len(blob),
        "sha256": sha256(blob),
        "header": public_header,
        "program_headers": programs,
        "sections": sections,
        "blob": blob,
    }


def layout(record: dict[str, object], fields: tuple[str, ...]) -> dict[str, object]:
    return {field: record[field] for field in fields}


def mapped_load_bytes(candidate: dict[str, object], address: int, size: int) -> bytes | None:
    for segment in candidate["program_headers"]:
        if segment["type"] != PT_LOAD:
            continue
        start = segment["vaddr"]
        end = start + segment["filesz"]
        if start <= address and address + size <= end:
            file_offset = segment["offset"] + address - start
            return checked_slice(candidate["blob"], file_offset, size, "candidate mapped load image")
    return None


def config_check(target: dict[str, object], config: dict[str, object]) -> dict[str, object]:
    errors = []
    if target["size"] != config["size"]:
        errors.append("ELF size")
    if target["sha256"] != config["sha256"]:
        errors.append("ELF sha256")
    if target["header"]["entry"] != int(config["entry"], 0):
        errors.append("entry point")
    loads = [item for item in target["program_headers"] if item["type"] == PT_LOAD]
    expected_load = config["load_segment"]
    expected_tuple = (
        int(expected_load["file_offset"], 0),
        int(expected_load["vram"], 0),
        int(expected_load["file_size"], 0),
        int(expected_load["memory_size"], 0),
        expected_load["sha256"],
    )
    actual_loads = [
        (item["offset"], item["vaddr"], item["filesz"], item["memsz"], item["sha256"])
        for item in loads
    ]
    if actual_loads != [expected_tuple]:
        errors.append("PT_LOAD record")
    by_name = {item["name"]: item for item in target["sections"]}
    for expected in config["sections"]:
        actual = by_name.get(expected["name"])
        if actual is None:
            errors.append(f"section {expected['name']} missing")
            continue
        for config_key, elf_key in (("vram", "addr"), ("offset", "offset"), ("size", "size")):
            if config_key in expected and actual[elf_key] != int(expected[config_key], 0):
                errors.append(f"section {expected['name']} {config_key}")
    return {"exact": not errors, "differences": errors}


def compare(target: dict[str, object], candidate: dict[str, object], config: dict[str, object]) -> dict[str, object]:
    load_fields = ("type", "offset", "vaddr", "paddr", "filesz", "memsz", "flags", "align")
    target_loads = [item for item in target["program_headers"] if item["type"] == PT_LOAD]
    candidate_loads = [item for item in candidate["program_headers"] if item["type"] == PT_LOAD]
    mapped = []
    target_bytes = bytearray()
    candidate_bytes = bytearray()
    mapped_exact = True
    for item in target_loads:
        expected = checked_slice(target["blob"], item["offset"], item["filesz"], "target PT_LOAD data")
        actual = mapped_load_bytes(candidate, item["vaddr"], item["filesz"])
        target_bytes.extend(expected)
        if actual is None:
            mapped_exact = False
            mapped.append({"vaddr": item["vaddr"], "size": item["filesz"], "covered": False})
            continue
        candidate_bytes.extend(actual)
        exact = actual == expected
        mapped_exact &= exact
        mapped.append(
            {
                "vaddr": item["vaddr"],
                "size": item["filesz"],
                "covered": True,
                "exact": exact,
                "candidate_sha256": sha256(actual),
            }
        )

    header_fields = (
        "class",
        "data",
        "ident_version",
        "osabi",
        "abi_version",
        "type",
        "machine",
        "version",
        "entry",
        "phoff",
        "shoff",
        "flags",
        "ehsize",
        "phentsize",
        "phnum",
        "shentsize",
        "shnum",
        "shstrndx",
    )
    header_differences = [
        field for field in header_fields if target["header"][field] != candidate["header"][field]
    ]
    section_fields = ("name", "type", "flags", "addr", "offset", "size", "link", "info", "addralign", "entsize")
    target_alloc = [layout(item, section_fields) for item in target["sections"] if item["flags"] & SHF_ALLOC]
    candidate_alloc = [layout(item, section_fields) for item in candidate["sections"] if item["flags"] & SHF_ALLOC]
    target_bss = [item for item in target_alloc if item["type"] == SHT_NOBITS]
    candidate_bss = [item for item in candidate_alloc if item["type"] == SHT_NOBITS]

    target_memory_end = max((item["vaddr"] + item["memsz"] for item in target_loads), default=0)
    candidate_covers_memory = all(
        any(
            other["vaddr"] <= item["vaddr"]
            and other["vaddr"] + other["memsz"] >= item["vaddr"] + item["memsz"]
            for other in candidate_loads
        )
        for item in target_loads
    )
    return {
        "schema": 1,
        "target": {key: target[key] for key in ("path", "size", "sha256")},
        "candidate": {key: candidate[key] for key in ("path", "size", "sha256")},
        "target_config": config_check(target, config),
        "full_elf_container": {
            "exact": target["size"] == candidate["size"] and target["sha256"] == candidate["sha256"],
        },
        "load_image_bytes": {
            "exact": mapped_exact,
            "size": len(target_bytes),
            "target_sha256": sha256(target_bytes),
            "candidate_sha256": sha256(candidate_bytes) if len(candidate_bytes) == len(target_bytes) else None,
            "mapping": mapped,
        },
        "elf_header": {"exact": not header_differences, "differences": header_differences},
        "program_header_layout": {
            "exact": [layout(item, load_fields) for item in target_loads]
            == [layout(item, load_fields) for item in candidate_loads],
            "target": [layout(item, load_fields) for item in target_loads],
            "candidate": [layout(item, load_fields) for item in candidate_loads],
            "candidate_covers_target_memory": candidate_covers_memory,
            "target_memory_end": target_memory_end,
        },
        "allocated_section_layout": {
            "exact": target_alloc == candidate_alloc,
            "target": target_alloc,
            "candidate": candidate_alloc,
        },
        "bss_layout": {"exact": target_bss == candidate_bss, "target": target_bss, "candidate": candidate_bss},
    }


def status(exact: bool) -> str:
    return "PASS" if exact else "DIFF"


def human_report(report: dict[str, object]) -> str:
    load = report["load_image_bytes"]
    header = report["elf_header"]
    program = report["program_header_layout"]
    lines = [
        "ELF COMPLETENESS REPORT",
        f"target: {report['target']['path']}",
        f"candidate: {report['candidate']['path']}",
        "",
        f"[{status(report['target_config']['exact'])}] target matches config/elf.json",
        (
            f"[{status(load['exact'])}] PT_LOAD bytes mapped by virtual address: "
            f"{load['size']} bytes, sha256 {load['target_sha256']}"
        ),
        f"[{status(report['full_elf_container']['exact'])}] full ELF container identity",
        (
            f"[{status(header['exact'])}] ELF header identity"
            + (f"; differing fields: {', '.join(header['differences'])}" if header["differences"] else "")
        ),
        f"[{status(program['exact'])}] program-header layout identity",
        (
            f"[{status(program['candidate_covers_target_memory'])}] candidate PT_LOAD covers target memory extent"
        ),
        f"[{status(report['allocated_section_layout']['exact'])}] allocated section layout identity",
        f"[{status(report['bss_layout']['exact'])}] NOBITS/BSS layout identity",
        "",
    ]
    if load["exact"] and not report["full_elf_container"]["exact"]:
        lines.append(
            "Conclusion: the reconstructed load-image bytes are exact, but the ELF container is not identical."
        )
    elif report["full_elf_container"]["exact"]:
        lines.append("Conclusion: the complete ELF container is identical.")
    else:
        lines.append("Conclusion: the reconstructed load image is not exact.")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--target", type=Path, default=ROOT / "original/SLUS_207.42")
    parser.add_argument("--candidate", type=Path, default=ROOT / "build/current/chulip.us.elf")
    parser.add_argument("--config", type=Path, default=ROOT / "config/elf.json")
    parser.add_argument("--json", action="store_true", help="print machine-readable JSON")
    parser.add_argument("--require-load-image", action="store_true")
    parser.add_argument("--require-layout", action="store_true")
    parser.add_argument("--require-container", action="store_true")
    args = parser.parse_args()
    for path in (args.target, args.candidate, args.config):
        if not path.is_file():
            raise SystemExit(f"missing input: {path}")
    report = compare(parse_elf(args.target), parse_elf(args.candidate), json.loads(args.config.read_text()))
    print(json.dumps(report, indent=2) if args.json else human_report(report))
    failed = (
        (args.require_load_image and not report["load_image_bytes"]["exact"])
        or (
            args.require_layout
            and not all(
                report[key]["exact"]
                for key in ("elf_header", "program_header_layout", "allocated_section_layout", "bss_layout")
            )
        )
        or (args.require_container and not report["full_elf_container"]["exact"])
    )
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
