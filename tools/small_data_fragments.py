"""Preserve explicit 1..3-byte raw sdata fragments omitted by pinned spimdisasm.

These generated assembly bytes are NOT reconstructed C and retain NON_MATCHING
markers. The caller must supply the authenticated image from configure.py's
checked_load_image(); the on-disk payload must agree with that image.
"""
from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
import re

try:
    from . import data_ownership as own
except ImportError:
    import data_ownership as own


class FragmentError(ValueError):
    pass


@dataclass(frozen=True)
class Label:
    name: str
    address: int
    size: int | None = None
    kind: str | None = None


ASSIGNMENT = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*;\s*(?://(.*))?$")
DEFINITION = re.compile(r"^\s*(?:dlabel|glabel|jlabel|alabel)\s+([A-Za-z_][A-Za-z0-9_]*)\b", re.M)


def safe_path(root: Path, relative: str) -> Path:
    path = root / relative
    if Path(relative).is_absolute() or not path.resolve().is_relative_to(root.resolve()):
        raise FragmentError(f"path escapes repository: {relative}")
    return path


def configured_labels(root: Path, document: dict) -> dict[str, Label]:
    labels = {}
    paths = document.get("options", {}).get("symbol_addrs_path", [])
    if isinstance(paths, str):
        paths = [paths]
    if not isinstance(paths, list) or not all(isinstance(x, str) for x in paths):
        raise FragmentError("symbol_addrs_path must name repository files")
    for relative in paths:
        for line in safe_path(root, relative).read_text().splitlines():
            line = line.strip()
            if not line or line.startswith("//"):
                continue
            match = ASSIGNMENT.fullmatch(line)
            if not match:
                raise FragmentError(f"unsupported symbol declaration in {relative}: {line}")
            name, value, comment = match.groups()
            address = int(value, 16 if value.startswith("0x") else 10)
            if name in labels:
                raise FragmentError(f"duplicate configured symbol: {name}")
            size_match = re.search(r"\bsize:(0x[0-9A-Fa-f]+|[0-9]+)\b", comment or "")
            kind_match = re.search(r"\btype:([A-Za-z0-9_]+)\b", comment or "")
            tags = {name for name, _value in re.findall(r"\b([A-Za-z_][A-Za-z0-9_]*):([^\s]+)", comment or "")}
            if tags - {"size", "type"} or ("size" in tags and size_match is None):
                raise FragmentError(f"unsupported symbol metadata in {relative}: {line}")
            size = int(size_match[1], 0) if size_match else None
            labels[name] = Label(name, address, size, kind_match[1] if kind_match else None)
    return labels


def render(fragment: own.Fragment, data: bytes, labels: list[Label]) -> str:
    size = fragment.end - fragment.start
    if fragment.section != "sdata" or not 1 <= size <= 3 or len(data) != size:
        raise FragmentError("only complete 1..3-byte raw sdata fragments are supported")
    if not labels or not any(x.address == fragment.start for x in labels):
        raise FragmentError("fragment requires a start label")
    names = set()
    by_address: dict[int, list[Label]] = {}
    for label in labels:
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", label.name) or label.name in names:
            raise FragmentError(f"duplicate or invalid symbol: {label.name}")
        names.add(label.name)
        if not fragment.start <= label.address < fragment.end:
            raise FragmentError(f"symbol outside fragment: {label.name}")
        if label.kind == "func":
            raise FragmentError(f"function symbol in raw sdata: {label.name}")
        named = re.fullmatch(r"D_([0-9A-Fa-f]{8})", label.name)
        if named and int(named[1], 16) != label.address:
            raise FragmentError(f"symbol address disagreement: {label.name}")
        if label.size is not None and not 0 < label.size <= fragment.end - label.address:
            raise FragmentError(f"symbol extends outside fragment: {label.name}")
        by_address.setdefault(label.address, []).append(label)
    addresses = sorted(by_address)
    result = ['.include "macro.inc"', '', '.section .sdata, "wa"', '.balign 1',
              '/* Raw retail data; subword preservation for pinned spimdisasm. */']
    for offset, byte in enumerate(data):
        address = fragment.start + offset
        for label in by_address.get(address, []):
            next_address = next((x for x in addresses if x > address), fragment.end)
            label_size = label.size if label.size is not None else next_address - address
            result.extend([f"nonmatching {label.name}, {label_size}", f"dlabel {label.name}",
                           f".size {label.name}, {label_size}"])
        result.append(f"    /* {address:08X} */ .byte 0x{byte:02X}")
    return "\n".join(result) + "\n"


def repair(root: Path, authenticated_image: bytes) -> list[Path]:
    """Validate every proposed output before writing any generated assembly."""
    claims, _bounds, _gaps, fragments = own.static_plan(root)
    if not claims:
        return []
    targets = []
    for fragment in fragments:
        if fragment.section != "sdata":
            continue
        size = fragment.end - fragment.start
        if fragment.start % 4 == 0 and size % 4 == 0:
            continue
        if not 1 <= size <= 3:
            raise FragmentError("unaligned raw sdata must split into a 1..3-byte edge and aligned words: " + fragment.object)
        targets.append(fragment)
    if not targets:
        return []
    payload = (root / "original/SLUS_207.42.rom").read_bytes()
    if payload != authenticated_image:
        raise FragmentError("payload differs from configure.py authenticated image")
    document = own.load_splat(root)
    labels = configured_labels(root, document)
    metadata = json.loads((root / "config/elf.json").read_text())
    base = own.number(metadata["load_segment"]["vram"])
    claim_names = {claim.symbol for claim in claims}
    active_outputs = {}
    for fragment in fragments:
        if not fragment.object.startswith("build/") or not fragment.object.endswith(".o"):
            raise FragmentError("unexpected fragment object path")
        path = safe_path(root, fragment.object.removeprefix("build/")[:-2] + ".s")
        active_outputs[path] = set(DEFINITION.findall(path.read_text())) if path.exists() else set()
    planned = []
    produced_names = set()
    for fragment in targets:
        offset = fragment.start - base
        if offset < 0 or offset + fragment.end - fragment.start > len(payload):
            raise FragmentError("fragment outside authenticated file-backed image")
        selected = [label for label in labels.values() if fragment.start <= label.address < fragment.end]
        if not any(label.address == fragment.start for label in selected):
            name = f"D_{fragment.start:08X}"
            if name in labels:
                raise FragmentError(f"synthetic start label collides with configured symbol: {name}")
            selected.append(Label(name, fragment.start))
        path = safe_path(root, fragment.object.removeprefix("build/")[:-2] + ".s")
        outside_names = set().union(*(names for other, names in active_outputs.items() if other != path))
        for label in selected:
            if label.name in claim_names | outside_names | produced_names:
                raise FragmentError(f"symbol has another active provider: {label.name}")
            produced_names.add(label.name)
        content = render(fragment, payload[offset:offset + fragment.end - fragment.start], selected)
        planned.append((path, content))
    for path, content in planned:
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists() or path.read_text() != content:
            path.write_text(content)
    return [path for path, _content in planned]
