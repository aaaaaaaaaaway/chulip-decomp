#!/usr/bin/env python3
"""Convert a raw 2352-byte Mode 2 data track to a 2048-byte-sector ISO.

The source BIN is never changed. The resulting ISO is suitable for reading the
ISO9660 filesystem. Mode 2 Form 2 sectors have a 2324-byte payload; their first
2048 bytes are copied for filesystem layout compatibility and a count is
reported. Those media sectors are not decompilation inputs.
"""

from __future__ import annotations

import argparse
import hashlib
import os
from pathlib import Path

RAW_SECTOR = 2352
ISO_SECTOR = 2048
PAYLOAD_OFFSET = 24
SYNC = b"\x00" + b"\xff" * 10 + b"\x00"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    size = args.source.stat().st_size
    if size % RAW_SECTOR:
        raise SystemExit(
            f"source size {size} is not divisible by {RAW_SECTOR}; not a raw track"
        )
    if args.output.exists():
        raise SystemExit(f"refusing to overwrite {args.output}")

    sectors = size // RAW_SECTOR
    partial = args.output.with_name(args.output.name + ".partial")
    if partial.exists():
        raise SystemExit(f"remove stale partial output first: {partial}")
    args.output.parent.mkdir(parents=True, exist_ok=True)

    source_sha256 = hashlib.sha256()
    iso_sha256 = hashlib.sha256()
    form2 = 0
    bad_sync = 0
    bad_mode = 0
    pvd = b""

    try:
        with args.source.open("rb") as source, partial.open("xb") as output:
            for index in range(sectors):
                sector = source.read(RAW_SECTOR)
                if len(sector) != RAW_SECTOR:
                    raise SystemExit(f"short read at sector {index}")
                source_sha256.update(sector)
                if sector[:12] != SYNC:
                    bad_sync += 1
                if sector[15] != 2:
                    bad_mode += 1
                # In Mode 2, bit 5 of the submode byte marks Form 2.
                if sector[18] & 0x20:
                    form2 += 1
                payload = sector[PAYLOAD_OFFSET : PAYLOAD_OFFSET + ISO_SECTOR]
                output.write(payload)
                iso_sha256.update(payload)
                if index == 16:
                    pvd = payload
            output.flush()
            os.fsync(output.fileno())
        partial.rename(args.output)
    except BaseException:
        if partial.exists():
            partial.unlink()
        raise

    if len(pvd) < 7 or pvd[1:6] != b"CD001":
        args.output.unlink()
        raise SystemExit("converted sector 16 is not an ISO9660 primary descriptor")

    print(f"source: {args.source}")
    print(f"sectors: {sectors}")
    print(f"mode2_form2_sectors: {form2}")
    print(f"bad_sync_sectors: {bad_sync}")
    print(f"non_mode2_sectors: {bad_mode}")
    print(f"source_sha256: {source_sha256.hexdigest()}")
    print(f"iso_sha256: {iso_sha256.hexdigest()}")
    print(f"output: {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
