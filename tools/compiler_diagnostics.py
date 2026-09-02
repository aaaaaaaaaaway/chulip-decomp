#!/usr/bin/env python3
"""Classify compiler diagnostics that make an exact match unsafe to import."""

from __future__ import annotations

import re


_DANGEROUS = (
    ("implicit int return type", re.compile(r"return type defaults to\b", re.I)),
    ("implicit function declaration", re.compile(r"implicit declaration", re.I)),
    (
        "implicit declaration changed type",
        re.compile(r"(?:previous(?:ly)?\s+implicit|previous implicit declaration|type mismatch with previous implicit)", re.I),
    ),
    (
        "incompatible argument type",
        re.compile(r"passing (?:argument|arg)\b.*incompatible (?:pointer )?type", re.I),
    ),
    (
        "incompatible pointer assignment",
        re.compile(r"(?:assignment|initialization) from incompatible pointer type", re.I),
    ),
    (
        "integer converted to pointer",
        re.compile(r"makes pointer from integer without a cast", re.I),
    ),
    (
        "pointer converted to integer",
        re.compile(r"makes integer from pointer without a cast", re.I),
    ),
    (
        "value returned from void function",
        re.compile(r"return(?:['` ]+)? with a value.*function returning void", re.I),
    ),
    (
        "pointer/integer assignment",
        re.compile(r"assignment makes (?:pointer from integer|integer from pointer)(?: without a cast)?", re.I),
    ),
    (
        "pointer/integer comparison",
        re.compile(r"comparison between pointer and integer", re.I),
    ),
    (
        "incompatible pointer comparison",
        re.compile(r"comparison of distinct pointer types", re.I),
    ),
    (
        "conflicting declaration",
        re.compile(r"conflicting types for\b", re.I),
    ),
    (
        "non-void function falls through",
        re.compile(r"control reaches end of non-void function", re.I),
    ),
)


# Diagnostics a C compile may emit without putting the ABI, and therefore the
# match, in doubt. Anything outside this set is refused at the import boundary
# rather than silently accepted, so a warning class nobody has classified yet
# cannot reach the ledger the way the type-wrong matches of 65d638b did.
_BENIGN = (
    re.compile(r"unused (?:variable|parameter|function|value)\b", re.I),
    re.compile(r"defined but not used\b", re.I),
    re.compile(r"statement with no effect\b", re.I),
    re.compile(r"(?:may|might) be used uninitialized\b", re.I),
)

# Assemblers and linkers describe constraints that are not C ABI defects, and
# their warnings travel in the same captured stream. Skip anything a tool
# prefixed with its own name, matching the contract match.run_compiler states.
_TOOL_PREFIXED = re.compile(
    r"(?:^|[\s/])(?:[\w.-]*ld(?:\.bfd)?|[\w.-]*as|ps2eeas)\s*:", re.I
)

# The bundled assembler reports some constraints without naming itself. These
# are section-placement notes from the small-data work, not C defects.
_ASSEMBLER_DIAGNOSTIC = re.compile(
    r"Setting incorrect section type for\b", re.I
)

_DIAGNOSTIC_LINE = re.compile(r"\b(?:warning|error)\s*:\s*(?P<text>.+)$", re.I)


def dangerous_diagnostics(output: str) -> list[str]:
    """Return stable reason labels for ABI-dangerous diagnostics in output."""
    return [label for label, pattern in _DANGEROUS if pattern.search(output)]


def unexpected_diagnostics(output: str) -> list[str]:
    """Return C compiler diagnostics that are neither known-benign nor known-bad.

    :func:`dangerous_diagnostics` names thirteen specific defects, so a warning
    class it does not list passes untouched however unsafe it is. This inverts
    that default for the import gate: every compiler diagnostic must be
    recognised as harmless, or the candidate is refused and a human classifies
    it. Assembler and linker lines are not C diagnostics and are ignored.
    """
    unexpected: list[str] = []
    for line in output.splitlines():
        stripped = line.strip()
        if not stripped or _TOOL_PREFIXED.search(stripped):
            continue
        if _ASSEMBLER_DIAGNOSTIC.search(stripped):
            continue
        found = _DIAGNOSTIC_LINE.search(stripped)
        if found is None:
            continue
        message = found.group("text").strip()
        if any(pattern.search(message) for pattern in _BENIGN):
            continue
        if message not in unexpected:
            unexpected.append(message)
    return unexpected
