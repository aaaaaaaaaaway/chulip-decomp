#!/usr/bin/env python3
"""Map exact candidate matches by original-function basic block."""

from __future__ import annotations

import argparse
import difflib
import re
import subprocess
import sys

import asm_diff
import match_artifacts

CONTROL_FLOW = {
    "j", "jal", "jr", "jalr", "b", "bal", "beq", "bne", "beqz", "bnez",
    "blez", "bgtz", "bltz", "bgez", "bltzal", "bgezal", "beql", "bnel",
    "blezl", "bgtzl", "bltzl", "bgezl", "bltzall", "bgezall", "bc0f", "bc0t",
    "bc0fl", "bc0tl", "bc1f", "bc1t", "bc1fl", "bc1tl", "bc2f", "bc2t",
    "bc2fl", "bc2tl",
}


def basic_block_leaders(
    instructions: list[tuple[int, str, str]], vram: int, size: int
) -> list[int]:
    """Find leaders from direct targets and post-delay-slot fallthroughs."""
    leaders = {0}
    offset_to_index = {offset: index for index, (offset, _word, _text) in enumerate(instructions)}
    for index, (_offset, _word, text) in enumerate(instructions):
        mnemonic = text.split(None, 1)[0] if text else ""
        if mnemonic not in CONTROL_FLOW:
            continue
        targets = re.findall(r"0x([0-9a-fA-F]+)", text)
        if targets:
            target_offset = int(targets[-1], 16) - vram
            if 0 <= target_offset < size and target_offset in offset_to_index:
                leaders.add(offset_to_index[target_offset])
        if index + 2 < len(instructions):
            leaders.add(index + 2)
    return sorted(leaders)


def parse_window(value: str) -> tuple[int, int]:
    start, end = value.split(":", 1)
    result = int(start, 0), int(end, 0)
    if result[0] < 0 or result[1] <= result[0]:
        raise argparse.ArgumentTypeError("range must be non-negative START:END with END > START")
    return result


def validate_window(window: tuple[int, int], size: int) -> None:
    if window[0] % 4 or window[1] % 4:
        raise ValueError("range boundaries must be four-byte aligned")
    if window[1] > size:
        raise ValueError(f"range ends outside the {size:#x}-byte verification unit")


def normalized_instruction(text: str) -> str:
    mnemonic = text.split(None, 1)[0] if text else ""
    return re.sub(r"0x[0-9a-fA-F]+", "<target>", text) if mnemonic in CONTROL_FLOW else text


def alignment_lines(original, candidate, address: int) -> list[str]:
    left = [normalized_instruction(item[2]) for item in original]
    right = [normalized_instruction(item[2]) for item in candidate]
    matcher = difflib.SequenceMatcher(a=left, b=right, autojunk=False)
    lines = ["alignment (control targets normalized):"]
    for tag, left_start, left_end, right_start, right_end in matcher.get_opcodes():
        if tag != "equal":
            lines.append(
                f"  {tag:<7} original[{left_start}:{left_end}] {address + left_start * 4:#010x} "
                f"candidate[{right_start}:{right_end}] {address + right_start * 4:#010x}"
            )
    return lines


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    match_artifacts.add_match_arguments(parser)
    parser.add_argument("--block", type=int)
    parser.add_argument(
        "--range",
        type=parse_window,
        dest="window",
        metavar="START:END",
        help="compare one function-relative byte window",
    )
    parser.add_argument("--align", action="store_true")
    args = parser.parse_args()
    try:
        spec = match_artifacts.spec_from_args(args)
        original = asm_diff.disassemble(match_artifacts.expected_bytes(spec), spec.address)
        candidate = asm_diff.disassemble(match_artifacts.compile_bytes(spec), spec.address)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        detail = (
            match_artifacts.compile_error_text(error)
            if isinstance(error, subprocess.CalledProcessError)
            else str(error)
        )
        print(f"FAILED: {detail}", file=sys.stderr)
        return 2

    candidate_by_offset = {entry[0]: entry for entry in candidate}

    def differences(low: int, high: int) -> int:
        return sum(
            candidate_by_offset.get(original[index][0], (None, None))[1] != original[index][1]
            for index in range(low, high)
        )

    if args.window:
        low_offset, high_offset = args.window
        try:
            validate_window(args.window, spec.size)
        except ValueError as error:
            print(f"FAILED: {error}", file=sys.stderr)
            return 2
        low = next((index for index, item in enumerate(original) if item[0] >= low_offset), len(original))
        high = next((index for index, item in enumerate(original) if item[0] >= high_offset), len(original))
        count = differences(low, high)
        label = "MATCH" if not count else f"DIFF {count}/{high - low}"
        print(f"range [{low_offset:#x}:{high_offset:#x}] {high - low} instructions {label}")
        return 0 if not count else 1

    leaders = basic_block_leaders(original, spec.address, spec.size)
    bounds = leaders + [len(original)]
    blocks = list(zip(bounds, bounds[1:]))
    if args.block is not None:
        if not 0 <= args.block < len(blocks):
            print(f"block {args.block} out of range (0..{len(blocks) - 1})", file=sys.stderr)
            return 2
        low, high = blocks[args.block]
        candidate_slice = [
            candidate_by_offset.get(item[0], (item[0], "--------", "(end)"))
            for item in original[low:high]
        ]
        report, status = asm_diff.render(
            original[low:high], candidate_slice, spec.address + original[low][0], (high - low) * 4, 0, True
        )
        print(f"# block {args.block}: instructions [{low}:{high}]")
        print(report)
        return status

    total = 0
    matched = 0
    print(f"# {spec.function}: {len(original)} instructions, {len(blocks)} basic blocks ({spec.size}B)")
    for index, (low, high) in enumerate(blocks):
        count = differences(low, high)
        total += count
        matched += count == 0
        label = "MATCH" if not count else f"DIFF {count}/{high - low}"
        block_address = spec.address + original[low][0]
        print(f"  block {index:>3} [{block_address:#010x}] {high - low:>3} instructions  {label}")
    print(f"summary: {matched}/{len(blocks)} blocks match, {total}/{len(original)} instructions differ")
    if len(candidate) != len(original):
        print(f"size drift: candidate {len(candidate)}, original {len(original)} instructions")
    if args.align:
        print("\n".join(alignment_lines(original, candidate, spec.address)))
    return 0 if not total and len(candidate) == len(original) else 1


if __name__ == "__main__":
    raise SystemExit(main())
