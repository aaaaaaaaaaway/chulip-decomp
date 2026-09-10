"""Validate and place source-owned small data at its retail address.

Static check is object-independent. rewrite_linker validates actual compiled ELF
objects and returns a new final linker script; it never modifies files or claims.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
from dataclasses import dataclass
import json
from pathlib import Path, PurePosixPath
import re
import struct
import subprocess

ROOT = Path(__file__).resolve().parents[1]
FAMILIES = {"sdata": "SDATA", "sbss": "SBSS"}


class OwnershipError(ValueError):
    pass


def number(value):
    if isinstance(value, bool):
        raise OwnershipError("boolean is not an address or size")
    try:
        return value if isinstance(value, int) else int(str(value), 0)
    except (TypeError, ValueError) as exc:
        raise OwnershipError(f"invalid integer {value!r}") from exc


@dataclass(frozen=True)
class Claim:
    symbol: str
    source: str
    section: str
    address: int
    size: int

    @property
    def object(self):
        return "build/" + self.source[:-2] + ".o"


@dataclass(frozen=True)
class Fragment:
    section: str
    start: int
    end: int
    object: str


@dataclass(frozen=True)
class Section:
    name: str
    size: int
    alignment: int
    index: int


@dataclass(frozen=True)
class Symbol:
    name: str
    offset: int
    size: int
    section: str
    kind: int


@dataclass(frozen=True)
class ObjectInfo:
    sections: tuple[Section, ...]
    symbols: tuple[Symbol, ...]


@dataclass(frozen=True)
class Block:
    object: str
    section: str
    start: int
    end: int


def read_object(path: Path) -> ObjectInfo:
    """Read ELF32 little-endian MIPS relocatables without another dependency."""
    blob = path.read_bytes()
    if len(blob) < 52 or blob[:6] != b"\x7fELF\x01\x01":
        raise OwnershipError(f"{path}: expected ELF32 little-endian object")
    header = struct.unpack_from("<16sHHIIIIIHHHHHH", blob)
    if header[1] != 1 or header[2] != 8:
        raise OwnershipError(f"{path}: expected relocatable MIPS object")
    shoff, stride, count, names_index = header[6], header[11], header[12], header[13]
    if stride != 40 or not count or names_index >= count or shoff + count * stride > len(blob):
        raise OwnershipError(f"{path}: invalid or unsupported section table")
    raw = [struct.unpack_from("<10I", blob, shoff + i * stride) for i in range(count)]

    def data(section):
        start, size = section[4], section[5]
        if start + size > len(blob):
            raise OwnershipError(f"{path}: section extends past file")
        return blob[start:start + size]

    def string(table, offset):
        if offset >= len(table):
            raise OwnershipError(f"{path}: invalid string-table offset")
        end = table.find(b"\0", offset)
        if end < 0:
            raise OwnershipError(f"{path}: unterminated string")
        return table[offset:end].decode("utf-8", errors="strict")

    names = data(raw[names_index])
    sections = tuple(Section(string(names, x[0]), x[5], x[8], i) for i, x in enumerate(raw))
    symbols = []
    for section in raw:
        if section[1] != 2:
            continue
        if section[9] != 16 or section[5] % 16 or section[6] >= count:
            raise OwnershipError(f"{path}: malformed symbol table")
        strings = data(raw[section[6]])
        records = data(section)
        for offset in range(0, len(records), 16):
            name, value, size, info, _other, index = struct.unpack_from("<IIIBBH", records, offset)
            if not name or not index:
                continue
            section_name = sections[index].name if index < count else f"SPECIAL:{index}"
            symbols.append(Symbol(string(strings, name), value, size, section_name, info & 15))
    return ObjectInfo(sections, tuple(symbols))


def configuration(root: Path):
    config = json.loads((root / "config/data_ownership.json").read_text())
    if config.get("schema") != 1 or not isinstance(config.get("owned"), list):
        raise OwnershipError("data_ownership.json requires schema 1 and an owned list")
    claims = []
    seen = set()
    for entry in config["owned"]:
        if not isinstance(entry, dict):
            raise OwnershipError("ownership entry must be an object")
        try:
            source, symbol = entry["source"], entry["symbol"]
            section = entry.get("section", "sdata").removeprefix(".")
            address, size = number(entry["address"]), number(entry["size"])
        except (KeyError, AttributeError, TypeError) as exc:
            raise OwnershipError("malformed ownership entry") from exc
        if not isinstance(source, str) or not re.fullmatch(r"src/[A-Za-z0-9_./-]+\.c", source):
            raise OwnershipError(f"invalid source path {source!r}")
        if ".." in PurePosixPath(source).parts or not (root / source).is_file():
            raise OwnershipError(f"missing or unsafe owning source: {source}")
        if not (root / source).resolve().is_relative_to(root.resolve()):
            raise OwnershipError(f"owning source escapes repository: {source}")
        if not isinstance(symbol, str) or not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", symbol):
            raise OwnershipError(f"invalid symbol {symbol!r}")
        if symbol in seen:
            raise OwnershipError(f"duplicate claim for {symbol}")
        seen.add(symbol)
        if section not in FAMILIES or size <= 0 or address < 0:
            raise OwnershipError(f"{symbol}: invalid section, address, or size")
        named = re.fullmatch(r"D_([0-9A-Fa-f]{8})", symbol)
        if named and int(named[1], 16) != address:
            raise OwnershipError(f"{symbol}: address disagrees with its name")
        claims.append(Claim(symbol, source, section, address, size))
    return claims


def load_splat(root: Path):
    """Keep empty ownership and JSON fixtures independent of PyYAML."""
    path = root / "config/splat.us.yaml"
    text = path.read_text()
    try:
        return json.loads(text)
    except json.JSONDecodeError:
        pass
    try:
        import yaml
    except ModuleNotFoundError:
        python = root / ".venv/bin/python"
        if not python.is_file():
            raise OwnershipError("nonempty ownership needs PyYAML or repository .venv/bin/python")
        result = subprocess.run(
            [str(python), "-c", "import json,sys,yaml; print(json.dumps(yaml.safe_load(sys.stdin.read())))"],
            input=text, capture_output=True, text=True,
        )
        if result.returncode:
            raise OwnershipError("repository YAML parser failed: " + result.stderr.strip())
        try:
            return json.loads(result.stdout)
        except json.JSONDecodeError as exc:
            raise OwnershipError("repository YAML parser returned invalid JSON") from exc
    try:
        return yaml.safe_load(text)
    except yaml.YAMLError as exc:
        raise OwnershipError(f"invalid Splat YAML: {exc}") from exc


def layout(root: Path):
    metadata = json.loads((root / "config/elf.json").read_text())
    bounds = {}
    for entry in metadata["sections"]:
        section = entry["name"].removeprefix(".")
        if section in FAMILIES:
            start = number(entry["vram"])
            bounds[section] = (start, start + number(entry["size"]))
    if set(bounds) != set(FAMILIES):
        raise OwnershipError("retail ELF section metadata lacks small-data bounds")
    document = load_splat(root)
    if not isinstance(document, dict):
        raise OwnershipError("Splat configuration must be an object")
    marks = []
    for segment in document.get("segments", []):
        if not isinstance(segment, dict) or "subsegments" not in segment:
            continue
        base = number(segment.get("vram", metadata["load_segment"]["vram"])) - number(segment.get("start", 0))
        for item in segment["subsegments"]:
            if isinstance(item, list):
                if not item:
                    raise OwnershipError("empty Splat subsegment")
                start = number(item[0]) + base
                kind = item[1] if len(item) > 1 else None
                name = item[2] if len(item) > 2 else None
            elif isinstance(item, dict):
                if not isinstance(item.get("type"), str) or not item["type"]:
                    raise OwnershipError("Splat dict subsegment requires an explicit type")
                if "vram" in item:
                    start = number(item["vram"])
                elif "start" in item:
                    start = number(item["start"]) + base
                else:
                    raise OwnershipError("Splat dict subsegment lacks address")
                kind, name = item.get("type"), item.get("name")
            else:
                raise OwnershipError("unsupported Splat subsegment")
            marks.append((start, kind, name))
    marks.sort(key=lambda x: x[0])
    if len({x[0] for x in marks}) != len(marks):
        raise OwnershipError("ambiguous duplicate Splat subsegment addresses")
    gaps, fragments = defaultdict(list), []
    source_intervals = []
    for section, (low, high) in bounds.items():
        for index, (start, kind, name) in enumerate(marks):
            if not low <= start < high:
                continue
            following = marks[index + 1][0] if index + 1 < len(marks) else high
            end = min(high, following)
            if kind is None:
                gaps[section].append((start, end))
            elif kind in {".sdata", ".sbss"}:
                if kind != "." + section:
                    raise OwnershipError(f"{kind} source contribution is outside retail {kind}")
                if (
                    not isinstance(name, str)
                    or not re.fullmatch(r"[A-Za-z0-9_./-]+", name)
                    or PurePosixPath(name).is_absolute()
                    or ".." in PurePosixPath(name).parts
                ):
                    raise OwnershipError(f"invalid Splat source contribution name {name!r}")
                source = f"src/{name}.c"
                gaps[section].append((start, end))
                source_intervals.append((section, start, end, source))
            elif kind == section:
                if not isinstance(name, str) or not re.fullmatch(r"[A-Za-z0-9_/-]+", name) or ".." in PurePosixPath(name).parts:
                    raise OwnershipError(f"invalid Splat fragment name {name!r}")
                # Splat's final NOBITS span includes the real alignment tail
                # before the following BSS subsegment; ownership bounds do not.
                if section == "sbss" and following == ((high + 7) & -8):
                    end = following
                fragments.append(Fragment(section, start, end, f"build/asm/data/{name}.{section}.o"))
    return bounds, gaps, fragments, source_intervals


def static_plan(root: Path):
    claims = configuration(root)
    if not claims:
        return claims, {}, {}, []
    bounds, gaps, fragments, source_intervals = layout(root)
    for claim in claims:
        low, high = bounds[claim.section]
        end = claim.address + claim.size
        if not low <= claim.address < end <= high:
            raise OwnershipError(f"{claim.symbol}: claim is outside retail .{claim.section}")
        if not any(a <= claim.address < end <= b for a, b in gaps[claim.section]):
            raise OwnershipError(f"{claim.symbol}: claim is not covered by an explicit Splat gap")
    for section, start, end, source in source_intervals:
        providers = {
            claim.source for claim in claims
            if claim.section == section and start <= claim.address < end
        }
        if providers != {source}:
            raise OwnershipError(
                f".{section} source contribution {source} at 0x{start:08X}: "
                f"claims must name exactly that provider; found {sorted(providers)}"
            )
    ordered = sorted(claims, key=lambda c: (c.section, c.address))
    for left, right in zip(ordered, ordered[1:]):
        if left.section == right.section and left.address + left.size > right.address:
            raise OwnershipError(f"overlapping claims: {left.symbol} and {right.symbol}")
    return claims, bounds, gaps, fragments


def check(root: Path = ROOT) -> list[str]:
    """Object-independent configuration checks suitable for public-check/split."""
    try:
        static_plan(root)
    except (OwnershipError, OSError, ValueError, KeyError, TypeError, AttributeError) as exc:
        return [str(exc)]
    return []


def required_fragment_objects(root: Path = ROOT) -> list[Path]:
    """Call before compilation: Splat can omit a fragment immediately after a gap."""
    claims, _bounds, _gaps, fragments = static_plan(root)
    sections = {claim.section for claim in claims}
    return [root / frag.object for frag in fragments if frag.section in sections]


def input_section(info: ObjectInfo, family: str, owner: str) -> Section:
    name = "." + family
    sections = [s for s in info.sections if s.name == name]
    if len(sections) != 1 or sections[0].size <= 0:
        raise OwnershipError(f"{owner}: missing/nonunique nonempty {name}")
    if any(s.size and s.name.startswith(name + ".") for s in info.sections):
        raise OwnershipError(f"{owner}: {name} subsections need an explicit placement model")
    if family == "sbss":
        if any(s.size and s.name.startswith(".scommon") for s in info.sections) or any(
            s.section in {"SPECIAL:65522", "SPECIAL:65283"} for s in info.symbols
        ):
            raise OwnershipError(f"{owner}: COMMON/.scommon bytes lack an explicit placement model")
    section = sections[0]
    if not section.alignment or section.alignment & (section.alignment - 1):
        raise OwnershipError(f"{owner}: invalid ELF section alignment")
    return section


def validated_blocks(claims, bounds, gaps, infos):
    groups = defaultdict(list)
    for claim in claims:
        groups[(claim.object, claim.section)].append(claim)
    blocks = []
    for (owner, family), entries in groups.items():
        info = infos.get(owner)
        if info is None:
            raise OwnershipError(f"owning object is missing from the build: {owner}")
        name = "." + family
        section = input_section(info, family, owner)
        by_name = {claim.symbol: claim for claim in entries}
        definitions = [s for s in info.symbols if s.section == name and s.kind != 3]
        if {s.name for s in definitions} != set(by_name):
            raise OwnershipError(f"{owner}: claims do not enumerate all {name} definitions")
        origins = set()
        for symbol in definitions:
            claim = by_name[symbol.name]
            if symbol.size != claim.size or symbol.offset + symbol.size > section.size:
                raise OwnershipError(f"{symbol.name}: claimed size disagrees with ELF symbol/section")
            providers = [obj for obj, other in infos.items() for s in other.symbols if s.name == symbol.name]
            if providers != [owner]:
                raise OwnershipError(f"{symbol.name}: duplicate or ambiguous ELF providers: {providers}")
            origins.add(claim.address - symbol.offset)
        if len(origins) != 1:
            raise OwnershipError(f"{owner}: {name} definitions imply inconsistent section origins")
        start = origins.pop()
        end = start + section.size
        low, high = bounds[family]
        if not low <= start < end <= high:
            raise OwnershipError(f"{owner}: complete {name} section exceeds retail bounds")
        # Small-data outputs preserve natural ELF input alignment. Text and
        # ordinary BSS may have SUBALIGN(8), but it must not govern these inputs.
        if start % section.alignment:
            raise OwnershipError(f"{owner}: origin violates section/input alignment")
        if (start, end) not in gaps[family]:
            raise OwnershipError(f"{owner}: complete {name} section must exactly fill one explicit gap")
        blocks.append(Block(owner, family, start, end))
    ordered = sorted(blocks, key=lambda b: (b.section, b.start))
    for left, right in zip(ordered, ordered[1:]):
        if left.section == right.section and left.end > right.start:
            raise OwnershipError(f"overlapping source sections: {left.object} and {right.object}")
    return ordered


def rewrite_linker(linker: str, objects: list[Path], root: Path = ROOT) -> str:
    """Validate compiled claims and return the final consumed linker script.

    Empty claims return the input byte-for-byte, preserving unregistered camera
    globals. No files are written. All actual linked objects must be supplied.
    """
    claims, bounds, gaps, fragments = static_plan(root)
    if not claims:
        return linker
    infos = {}
    for path in objects:
        path = path if path.is_absolute() else root / path
        try:
            key = path.resolve().relative_to(root.resolve()).as_posix()
        except ValueError as exc:
            raise OwnershipError(f"linked object is outside repository: {path}") from exc
        if key not in infos:
            infos[key] = read_object(path)
    blocks = validated_blocks(claims, bounds, gaps, infos)
    for family, marker in FAMILIES.items():
        owned = [b for b in blocks if b.section == family]
        if not owned:
            continue
        begin = f"        cod_{marker}_START = .;\n"
        end = f"        cod_{marker}_END = .;"
        if linker.count(begin) != 1 or linker.count(end) != 1:
            raise OwnershipError(f"nonunique/missing {family} linker boundaries")
        prefix, body = linker.split(begin, 1)
        # A SUBALIGN override would invalidate the native-alignment proof.
        output_header = prefix.rsplit("{", 1)[0].rsplit("}", 1)[-1]
        if re.search(r"\bSUBALIGN\s*\(", output_header):
            raise OwnershipError(f"{family}: output must preserve native input alignment")
        body, suffix = body.split(end, 1)
        if "cod_" in body:
            raise OwnershipError(f"unexpected nested boundary within {family}")
        selected = [f for f in fragments if f.section == family]
        moving = {b.object for b in owned} | {f.object for f in selected}
        counts = defaultdict(int)
        kept = []
        selectors = {}
        for line in body.splitlines(keepends=True):
            found = re.fullmatch(r"\s*(build/[^\s()]+\.o)\(([^\n]+)\);\s*", line)
            if found and found[1] in moving:
                if "." + family not in found[2]:
                    raise OwnershipError(f"unexpected input selector for {found[1]}")
                counts[found[1]] += 1
                selectors[found[1]] = found[2]
            else:
                kept.append(line)
        for block in owned:
            if counts[block.object] != 1:
                raise OwnershipError(f"{block.object}: source contribution must occur once before rewrite")
        for frag in selected:
            if counts[frag.object] > 1 or frag.object not in infos:
                raise OwnershipError(f"{frag.object}: missing or duplicated assembled fragment")
            section = input_section(infos[frag.object], family, frag.object)
            if section.size != frag.end - frag.start:
                raise OwnershipError(f"{frag.object}: ELF fragment extent disagrees with Splat interval")
        run = [(b.start, b.end, b.object) for b in owned] + [(f.start, f.end, f.object) for f in selected]
        run.sort()
        for left, right in zip(run, run[1:]):
            if left[1] > right[0]:
                raise OwnershipError(f"overlapping {family} placement intervals")
        tail = []
        default_selector = ".sdata*" if family == "sdata" else ".sbss COMMON .scommon"
        for start, finish, obj in run:
            alignment = input_section(infos[obj], family, obj).alignment
            if start % alignment:
                raise OwnershipError(f"{obj}: fragment violates native ELF alignment")
            tail.append(f'        ASSERT(ALIGN(ABSOLUTE(.), {alignment}) == 0x{start:08X}, "{family} placement: {obj}");\n')
            tail.append(f"        {obj}({selectors.get(obj, default_selector)});\n")
            tail.append(f'        ASSERT(ABSOLUTE(.) == 0x{finish:08X}, "{family} extent: {obj}");\n')
        linker = prefix + begin + "".join(kept + tail) + end + suffix
    return linker


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--root", type=Path, default=ROOT)
    args = parser.parse_args()
    errors = check(args.root)
    for error in errors:
        print(f"data ownership: {error}")
    if not errors:
        print(f"DATA OWNERSHIP CONFIG OK: {len(configuration(args.root))} claimed symbol(s)")
    return bool(errors)


if __name__ == "__main__":
    raise SystemExit(main())
