#!/usr/bin/env python3
"""List or extract a conventional ISO9660 filesystem without mounting it."""

from __future__ import annotations

import argparse
import json
from dataclasses import dataclass
from pathlib import Path, PurePosixPath

SECTOR = 2048


@dataclass(frozen=True)
class Entry:
    path: PurePosixPath
    extent: int
    size: int
    flags: int

    @property
    def is_dir(self) -> bool:
        return bool(self.flags & 0x02)


def read_at(stream, offset: int, size: int) -> bytes:
    stream.seek(offset)
    data = stream.read(size)
    if len(data) != size:
        raise ValueError(f"short read at {offset:#x}: wanted {size}, got {len(data)}")
    return data


def parse_record(record: bytes, parent: PurePosixPath) -> Entry | None:
    if len(record) < 34:
        raise ValueError("short ISO9660 directory record")
    extent = int.from_bytes(record[2:6], "little")
    size = int.from_bytes(record[10:14], "little")
    flags = record[25]
    name_len = record[32]
    raw_name = record[33 : 33 + name_len]
    if raw_name in (b"\x00", b"\x01"):
        return None
    name = raw_name.decode("ascii", errors="strict")
    if ";" in name:
        name = name.rsplit(";", 1)[0]
    if not name or name in (".", "..") or "/" in name or "\\" in name:
        raise ValueError(f"unsafe ISO9660 name: {name!r}")
    return Entry(parent / name, extent, size, flags)


def directory_entries(stream, directory: Entry) -> list[Entry]:
    blob = read_at(stream, directory.extent * SECTOR, directory.size)
    entries: list[Entry] = []
    offset = 0
    while offset < len(blob):
        length = blob[offset]
        if length == 0:
            offset = ((offset // SECTOR) + 1) * SECTOR
            continue
        end = offset + length
        if end > len(blob):
            raise ValueError(f"directory record overruns {directory.path}")
        entry = parse_record(blob[offset:end], directory.path)
        if entry is not None:
            entries.append(entry)
        offset = end
    return entries


def scan(iso: Path) -> list[Entry]:
    with iso.open("rb") as stream:
        pvd = read_at(stream, 16 * SECTOR, SECTOR)
        if pvd[0] != 1 or pvd[1:6] != b"CD001" or pvd[6] != 1:
            raise ValueError("sector 16 is not an ISO9660 primary volume descriptor")
        root_len = pvd[156]
        root_record = pvd[156 : 156 + root_len]
        root = Entry(PurePosixPath("/"), int.from_bytes(root_record[2:6], "little"),
                     int.from_bytes(root_record[10:14], "little"), root_record[25])
        found: list[Entry] = []
        pending = [root]
        seen_extents: set[tuple[int, int]] = set()
        while pending:
            directory = pending.pop()
            key = (directory.extent, directory.size)
            if key in seen_extents:
                continue
            seen_extents.add(key)
            children = directory_entries(stream, directory)
            found.extend(children)
            pending.extend(reversed([entry for entry in children if entry.is_dir]))
        return sorted(found, key=lambda item: str(item.path))


def extract(iso: Path, output: Path, entries: list[Entry]) -> None:
    output.mkdir(parents=True, exist_ok=True)
    root = output.resolve()
    with iso.open("rb") as stream:
        for entry in entries:
            relative = Path(*entry.path.parts[1:])
            target = (output / relative).resolve()
            if target != root and root not in target.parents:
                raise ValueError(f"unsafe extraction target: {target}")
            if entry.is_dir:
                target.mkdir(parents=True, exist_ok=True)
                continue
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(read_at(stream, entry.extent * SECTOR, entry.size))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("iso", type=Path)
    parser.add_argument("--extract", type=Path, metavar="DIRECTORY")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    entries = scan(args.iso)
    if args.extract:
        extract(args.iso, args.extract, entries)
    records = [
        {
            "path": str(entry.path),
            "extent": entry.extent,
            "size": entry.size,
            "type": "directory" if entry.is_dir else "file",
            "flags": entry.flags,
        }
        for entry in entries
    ]
    if args.json:
        print(json.dumps(records, indent=2))
    else:
        for record in records:
            print(f"{record['type'][0]} {record['size']:10d} {record['extent']:8d} {record['path']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
