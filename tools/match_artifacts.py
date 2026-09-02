#!/usr/bin/env python3
"""Build an isolated candidate with the authoritative Chulip match pipeline.

This module is deliberately a thin adapter around :mod:`match`: diagnostic
tools must not acquire a subtly different compiler, assembler, linker script,
symbol set, or verification range from ``tools/match.py``.
"""

from __future__ import annotations

import json
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path

import match
from normalize_asm import normalize

DEFAULT_PROFILE = "ee-gcc2.95.3-136-O2-G8"


@dataclass(frozen=True)
class MatchSpec:
    function: str
    source: Path
    profile_name: str
    profile: dict[str, object]
    address: int
    end: int
    object_flags: tuple[str, ...]
    rodata: int | None

    @property
    def size(self) -> int:
        return self.end - self.address


def resolve_spec(
    function: str,
    source: Path | None = None,
    profile_name: str | None = None,
    range_start: int | None = None,
    range_end: int | None = None,
    object_flags: list[str] | None = None,
    rodata_start: int | None = None,
    no_rodata: bool = False,
) -> MatchSpec:
    """Resolve defaults exactly as ``match.py`` does and validate the range."""
    record = match.function_record(function)
    reconstructed = match.reconstruction_record(function)
    function_address = match.parse_address(record["address"])
    function_end = function_address + int(record["size"])
    address = range_start
    if address is None:
        address = (
            match.parse_address(reconstructed.get("unit_start", record["address"]))
            if reconstructed
            else function_address
        )
    end = range_end
    if end is None:
        end = (
            match.parse_address(reconstructed.get("unit_end", function_end))
            if reconstructed
            else function_end
        )
    if address > function_address or end < function_end or end <= address:
        raise ValueError("verification range must contain the requested function")

    if source is None:
        relative = reconstructed["source"] if reconstructed else f"src/game/{function}.c"
        source = match.ROOT / str(relative)
    elif not source.is_absolute():
        source = match.ROOT / source
    if not source.is_file():
        raise FileNotFoundError(f"missing source: {source}")

    flags = list(object_flags or [])
    if not flags and reconstructed:
        flags = [str(flag) for flag in reconstructed.get("object_flags", [])]

    rodata = rodata_start
    if rodata is None and reconstructed and reconstructed.get("rodata_start"):
        rodata = match.parse_address(reconstructed["rodata_start"])
    if rodata is None:
        rodata = match.jump_table_address(address, end)
    if no_rodata:
        rodata = None

    profiles = json.loads(match.TOOLCHAINS.read_text())["profiles"]
    if profile_name is None:
        profile_name = str(reconstructed["build_profile"]) if reconstructed else DEFAULT_PROFILE
    if profile_name not in profiles:
        raise ValueError(f"unknown profile: {profile_name}")
    return MatchSpec(
        function=function,
        source=source,
        profile_name=profile_name,
        profile=profiles[profile_name],
        address=address,
        end=end,
        object_flags=tuple(flags),
        rodata=rodata,
    )


def expected_bytes(spec: MatchSpec) -> bytes:
    target = match.TARGET.read_bytes()
    offset = spec.address - match.TEXT_VRAM
    data = target[offset : offset + spec.size]
    if len(data) != spec.size:
        raise ValueError("verification range is outside the retail load image")
    return data


def compile_bytes(spec: MatchSpec) -> bytes:
    """Compile, link, relocate, and extract candidate ``.text`` bytes."""
    for script in ("build/undefined_funcs_auto.txt", "build/undefined_syms_auto.txt"):
        if not (match.ROOT / script).is_file():
            raise FileNotFoundError(f"missing generated linker symbols: {script}; run make split")
    with tempfile.TemporaryDirectory(prefix="chulip-match-") as directory:
        work = Path(directory)
        assembly = work / "compiled.s"
        normalized = work / "compiled.normalized.s"
        obj = work / "compiled.o"
        linked = work / "compiled.elf"
        binary = work / "compiled.bin"
        script = work / "function.ld"
        derived = work / "derived_symbols.ld"

        match.run(match.profile_command(spec.profile, spec.source, assembly))
        normalized.write_text(normalize(assembly.read_text()))
        if not match.compile_historical_object(
            spec.profile, spec.source, obj, list(spec.object_flags)
        ):
            match.run(
                [
                    "mipsel-linux-gnu-as",
                    "-EL",
                    "-march=r5900",
                    "-mabi=eabi",
                    "-no-pad-sections",
                    "-Iinclude",
                    "-o",
                    str(obj),
                    str(normalized),
                ]
            )
        placement: dict[str, int | None] = {
            ".data": match.source_owned_section_origin(obj, ".data")[0],
            ".sdata": None,
            ".sbss": None,
        }
        for section in match.SMALL_SECTIONS:
            placement[section] = match.source_owned_section_origin(obj, section)[0]
        script.write_text(
            match.linker_script(
                spec.address,
                spec.rodata,
                placement[".sdata"] if placement[".sdata"] is not None else match.SDATA_VRAM,
                placement[".sbss"],
                placement[".data"],
            )
        )
        match.write_derived_symbols(obj, derived)
        match.run(
            [
                "mipsel-linux-gnu-ld",
                "-EL",
                "-m",
                "elf32ltsmip",
                "--no-check-sections",
                "-T",
                str(script),
                "-T",
                str(derived),
                "-T",
                "config/linker_aliases.ld",
                "-T",
                "build/undefined_funcs_auto.txt",
                "-T",
                "build/undefined_syms_auto.txt",
                "-o",
                str(linked),
                str(obj),
            ]
        )
        match.run(
            ["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", str(linked), str(binary)]
        )
        return binary.read_bytes()


def add_match_arguments(parser) -> None:
    parser.add_argument("function")
    parser.add_argument("--source", type=Path, help="candidate C; defaults to reconstructed source")
    parser.add_argument("--profile", help="toolchain profile; defaults to reconstruction profile")
    parser.add_argument("--range-start", type=lambda value: int(value, 0))
    parser.add_argument("--range-end", type=lambda value: int(value, 0))
    parser.add_argument("--object-flag", action="append", default=[])
    parser.add_argument("--rodata-start", type=lambda value: int(value, 0))
    parser.add_argument("--no-rodata", action="store_true")


def spec_from_args(args) -> MatchSpec:
    return resolve_spec(
        args.function,
        args.source,
        args.profile,
        args.range_start,
        args.range_end,
        args.object_flag,
        args.rodata_start,
        args.no_rodata,
    )


def compile_error_text(error: subprocess.CalledProcessError) -> str:
    detail = error.stderr or error.stdout or ""
    if isinstance(detail, bytes):
        detail = detail.decode(errors="replace")
    return str(detail).strip()[-2000:]
