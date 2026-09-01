#!/usr/bin/env python3
"""Show an instruction-level diff against Chulip's retail R5900 bytes."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

import match_artifacts

OBJDUMP = "mipsel-linux-gnu-objdump"
INSN_RE = re.compile(r"^\s*([0-9a-fA-F]+):\s+([0-9a-fA-F]{8})\s+(.*?)\s*$")


def disassemble(blob: bytes, vram: int) -> list[tuple[int, str, str]]:
    """Return ``(byte offset, encoded word, instruction text)`` tuples.

    GNU objdump may render an unsupported EE-only instruction as ``.word``;
    that remains useful because both sides use the same decoder and the encoded
    word is always retained for byte-exact comparison.
    """
    with tempfile.TemporaryDirectory(prefix="chulip-disasm-") as directory:
        binary = Path(directory) / "text.bin"
        binary.write_bytes(blob)
        output = subprocess.run(
            [
                OBJDUMP,
                "-D",
                "-b",
                "binary",
                "-m",
                "mips",
                "-EL",
                "-M",
                "r5900",
                f"--adjust-vma={vram:#x}",
                str(binary),
            ],
            check=True,
            capture_output=True,
            text=True,
        ).stdout
    instructions = []
    for line in output.splitlines():
        found = INSN_RE.match(line)
        if not found:
            continue
        address = int(found.group(1), 16)
        text = re.sub(r"\s+", " ", found.group(3)).strip()
        text = re.sub(r"\s*#.*$", "", text)
        instructions.append((address - vram, found.group(2).lower(), text))
    return instructions


def classify_difference(left: str, right: str) -> str:
    left_parts = left.split(None, 1)
    right_parts = right.split(None, 1)
    if left_parts[0] != right_parts[0]:
        return "opcode"
    left_operands = left_parts[1] if len(left_parts) == 2 else ""
    right_operands = right_parts[1] if len(right_parts) == 2 else ""
    registers = (
        r"(?<![A-Za-z0-9_])\$?"
        r"(?:zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f[0-9]+)\b"
    )
    if re.findall(registers, left_operands) != re.findall(registers, right_operands):
        return "register"
    numbers = r"(?<![A-Za-z_])(?:0x[0-9a-fA-F]+|-?\d+)"
    if re.findall(numbers, left_operands) != re.findall(numbers, right_operands):
        return "immediate/target"
    return "operand"


def render(
    original: list[tuple[int, str, str]],
    candidate: list[tuple[int, str, str]],
    address: int,
    size: int,
    context: int = 2,
    show_all: bool = False,
) -> tuple[str, int]:
    count = max(len(original), len(candidate))
    differing = [
        index
        for index in range(count)
        if (original[index][1:] if index < len(original) else None)
        != (candidate[index][1:] if index < len(candidate) else None)
    ]
    if not differing:
        return f"MATCH {size}B / {len(original)} instructions - byte identical", 0

    lines = [
        f"MISMATCH {address:#010x} ({size}B): {len(differing)}/{len(original)} instructions differ"
    ]
    if len(original) != len(candidate):
        lines.append(f"  size drift: candidate {len(candidate)}, original {len(original)} instructions")
    visible = set(range(count)) if show_all else {
        near
        for index in differing
        for near in range(max(0, index - context), min(count, index + context + 1))
    }
    previous = None
    for index in sorted(visible):
        if previous is not None and index != previous + 1:
            lines.append("        ...")
        previous = index
        left = original[index] if index < len(original) else (index * 4, "--------", "(end)")
        right = candidate[index] if index < len(candidate) else (index * 4, "--------", "(end)")
        if left[1:] == right[1:]:
            lines.append(f"  {left[0]:#06x} {left[2]}")
            continue
        kind = "size" if "(end)" in (left[2], right[2]) else classify_difference(left[2], right[2])
        lines.append(f"! {left[0]:#06x} [{kind:>16}] original: {left[2]} | candidate: {right[2]}")
    return "\n".join(lines), 1


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    match_artifacts.add_match_arguments(parser)
    parser.add_argument("--context", type=int, default=2)
    parser.add_argument("--all", action="store_true", help="show every instruction")
    args = parser.parse_args()
    try:
        spec = match_artifacts.spec_from_args(args)
        original_bytes = match_artifacts.expected_bytes(spec)
        candidate_bytes = match_artifacts.compile_bytes(spec)
        original = disassemble(original_bytes, spec.address)
        candidate = disassemble(candidate_bytes, spec.address)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        detail = (
            match_artifacts.compile_error_text(error)
            if isinstance(error, subprocess.CalledProcessError)
            else str(error)
        )
        print(f"FAILED: {detail}", file=sys.stderr)
        return 2
    report, status = render(original, candidate, spec.address, spec.size, args.context, args.all)
    print(report)
    return status


if __name__ == "__main__":
    raise SystemExit(main())
