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
        re.compile(r"return with a value.*function returning void", re.I),
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


def dangerous_diagnostics(output: str) -> list[str]:
    """Return stable reason labels for ABI-dangerous diagnostics in output."""
    return [label for label, pattern in _DANGEROUS if pattern.search(output)]
