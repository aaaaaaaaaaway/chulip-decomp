#!/usr/bin/env python3
"""Report where retail's assembler padded a div-family opcode, and where it did not.

The bundled Ps2EeAs applies a rule its binary states as "DIV related opcode too
near branch instruction - Added %i padding NOP/s". The padding is assembler
output, not compiler output, and the rule measures against branch destination
labels. At -O2 the SN driver emits no statement labels, so a profile without -g
can never reproduce a padded site; compiling with -g emits the $LM labels the
rule needs (config/toolchains.json carries that profile).

That makes each site evidence about the original source. A padded site says a
statement boundary fell close enough to the div for the assembler to react; an
unpadded site says none did. This reports both so an author can check a
candidate's statement structure against retail instead of guessing at a
two-nop difference.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/functions.json"
RECONSTRUCTED = ROOT / "config/reconstructed.json"

# "/* fileoffset vram encoding */  mnemonic operands", delay slots indented one
# further. spimdisasm renders unrepresentable encodings as .word with the
# decoded mnemonic in a trailing comment.
INSTRUCTION = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+(?P<vram>[0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/\s+(?P<mnemonic>\S+)"
)
LABEL = re.compile(r"^\s*(?P<name>\.L[0-9A-Fa-f]+|[A-Za-z_]\w*):\s*$")
GLABEL = re.compile(r"^glabel\s+(?P<name>\S+)")
ENDLABEL = re.compile(r"^endlabel\s+(?P<name>\S+)")

DIV_FAMILY = frozenset({"div", "divu", "div1", "divu1", "ddiv", "ddivu", "div.s", "div.d"})
BRANCH = re.compile(
    r"^(?:b|bal|beq|beql|bne|bnel|bgez|bgezal|bgezall|bgezl|bgtz|bgtzl|blez|blezl|"
    r"bltz|bltzal|bltzall|bltzl|bc1f|bc1fl|bc1t|bc1tl|j|jal|jalr|jr)$"
)


def sites() -> list[dict[str, object]]:
    """Every div-family instruction in the retail disassembly, with its context."""
    found: list[dict[str, object]] = []
    for path in sorted((ROOT / "asm/cod").glob("*.s")):
        function: str | None = None
        stream: list[tuple[str, bool]] = []  # (mnemonic, fills a delay slot)
        since_label: int | None = None
        since_branch: int | None = None
        for line in path.read_text(errors="replace").splitlines():
            start = GLABEL.match(line)
            if start:
                function = start.group("name")
                stream = []
                since_label = None
                since_branch = None
                continue
            if ENDLABEL.match(line):
                function = None
                continue
            if function is None:
                continue
            if LABEL.match(line):
                since_label = 0
                continue
            instruction = INSTRUCTION.match(line)
            if instruction is None:
                continue
            mnemonic = instruction.group("mnemonic")
            if mnemonic == ".word":
                mnemonic = "<word>"
            if mnemonic in DIV_FAMILY:
                # A nop filling a branch delay slot is scheduling, not the
                # assembler's padding, so stop the run when one is reached.
                padding = 0
                for previous, delay_slot in reversed(stream):
                    if previous == "nop" and not delay_slot:
                        padding += 1
                    else:
                        break
                found.append(
                    {
                        "function": function,
                        "address": f"0x{int(instruction.group('vram'), 16):08X}",
                        "mnemonic": mnemonic,
                        "leading_nops": padding,
                        "instructions_since_label": since_label,
                        "instructions_since_branch": since_branch,
                    }
                )
            previous_mnemonic = stream[-1][0] if stream else None
            stream.append(
                (mnemonic, previous_mnemonic is not None and bool(BRANCH.match(previous_mnemonic)))
            )
            if since_label is not None:
                since_label += 1
            since_branch = 0 if BRANCH.match(mnemonic) else (
                None if since_branch is None else since_branch + 1
            )
    return found


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", type=Path, help="write every site to this path")
    parser.add_argument(
        "--min-nops",
        type=int,
        default=2,
        help="leading nop run that counts as assembler padding (default 2)",
    )
    parser.add_argument("--limit", type=int, default=20, help="functions to list")
    arguments = parser.parse_args()

    records = sites()
    catalog = {
        entry["name"]: entry for entry in json.loads(CATALOG.read_text())["functions"]
    }
    reconstructed = {
        entry["function"] for entry in json.loads(RECONSTRUCTED.read_text())
    }

    padded = [r for r in records if int(r["leading_nops"]) >= arguments.min_nops]
    by_mnemonic: dict[str, list[int]] = {}
    for record in records:
        by_mnemonic.setdefault(str(record["mnemonic"]), []).append(
            int(record["leading_nops"])
        )

    print(f"div-family sites: {len(records)}")
    print(
        f"padded (>= {arguments.min_nops} leading nops): {len(padded)}"
        f"  unpadded: {len(records) - len(padded)}"
    )
    print()
    print("mnemonic   sites  padded")
    for mnemonic in sorted(by_mnemonic):
        runs = by_mnemonic[mnemonic]
        hits = sum(1 for run in runs if run >= arguments.min_nops)
        print(f"{mnemonic:9} {len(runs):6} {hits:7}")

    pending: dict[str, dict[str, int]] = {}
    for record in records:
        name = str(record["function"])
        if name in reconstructed or name not in catalog:
            continue
        bucket = pending.setdefault(
            name, {"padded": 0, "sites": 0, "size": int(catalog[name]["size"])}
        )
        bucket["sites"] += 1
        if int(record["leading_nops"]) >= arguments.min_nops:
            bucket["padded"] += 1
    affected = {name: v for name, v in pending.items() if v["padded"]}
    print()
    print(
        f"unmatched functions with a div-family site: {len(pending)}"
        f" ({sum(v['size'] for v in pending.values()):,} bytes)"
    )
    print(
        f"of those, carrying padded sites: {len(affected)}"
        f" ({sum(v['size'] for v in affected.values()):,} bytes)"
    )
    print()
    print("padded sites bytes function")
    ordered = sorted(affected.items(), key=lambda kv: (-kv[1]["size"], kv[0]))
    for name, bucket in ordered[: arguments.limit]:
        print(f"{bucket['padded']:6} {bucket['sites']:5} {bucket['size']:5} {name}")

    if arguments.json:
        output = arguments.json if arguments.json.is_absolute() else ROOT / arguments.json
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(records, indent=2) + "\n")
        print(f"\nwrote {len(records)} sites to {output.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
