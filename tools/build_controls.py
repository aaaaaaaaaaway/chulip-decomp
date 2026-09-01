#!/usr/bin/env python3
"""Reviewed per-object controls allowed in exact reconstruction metadata."""

from __future__ import annotations


ALLOWED_OBJECT_FLAGS = frozenset(
    {
        "-Wa,-G0",
        "-Wa,-G1",
        "-Wa,-G3",
        "-Wa,-G4",
        "-Wa,-G8",
        "-Wa,-mcpu=4000",
        "-mno-split-addresses",
    }
)


def object_flag_errors(flags: object) -> list[str]:
    if not isinstance(flags, list) or not all(isinstance(flag, str) for flag in flags):
        return ["object_flags must be a list of strings"]
    unknown = sorted(set(flags) - ALLOWED_OBJECT_FLAGS)
    errors = ["unsanctioned object flags: " + ", ".join(unknown)] if unknown else []
    small_data = [flag for flag in flags if flag.startswith("-Wa,-G")]
    if len(small_data) > 1:
        errors.append("conflicting assembler small-data controls: " + ", ".join(small_data))
    return errors

