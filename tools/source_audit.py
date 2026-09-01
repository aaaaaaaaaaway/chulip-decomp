#!/usr/bin/env python3
"""Shared no-cheat audit for public Chulip C reconstructions.

Exact C progress is C source recovered from the program.  Inline assembly,
assembly inclusion, instruction dumps, and byte-padding substitutes therefore
never qualify, even when hidden behind a preprocessor macro.  Authentic SDK or
hardware assembly belongs in a separately classified assembly input and is not
counted by this audit as reconstructed C.

The scanner follows repository-local quoted includes so that a candidate
cannot hide an emitting macro in a private header.  It intentionally does not
run the C preprocessor: all conditional branches are audited conservatively.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class SourceAuditIssue:
    path: Path
    line: int
    kind: str
    detail: str

    def format(self, root: Path | None = None) -> str:
        display = self.path
        if root is not None:
            try:
                display = self.path.resolve().relative_to(root.resolve())
            except ValueError:
                pass
        return f"{display}:{self.line}: {self.kind}: {self.detail}"


@dataclass(frozen=True)
class _Macro:
    name: str
    body: str
    path: Path
    line: int
    function_like: bool


_DEFINE = re.compile(
    r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\([^\n)]*\))?[ \t]*"
    r"(?P<body>(?:\\\r?\n|[^\r\n])*)",
    re.M,
)
_QUOTED_INCLUDE = re.compile(
    r'^[ \t]*#[ \t]*include[ \t]+"([^"\n]+)"', re.M
)
_IDENTIFIER = re.compile(r"\b[A-Za-z_]\w*\b")
_INLINE_ASM = re.compile(
    r"\b(?:__asm__|__asm|asm)\s*"
    r"(?:(?:__volatile__|__volatile|volatile|inline|goto)\s*)*\(",
    re.I,
)
_ASM_IDENTIFIER = re.compile(r"\b(?:__asm__|__asm|asm)\b", re.I)
_ASSEMBLY_INCLUDE = re.compile(
    r"\b(?:INCLUDE_ASM|GLOBAL_ASM|include_asm)\b", re.I
)
_ASSEMBLY_LABEL = re.compile(r"\b(?:glabel|endlabel)\b")
_BINARY_INCLUDE = re.compile(r"(?:^|[^A-Za-z0-9_]|\\[nt])\.incbin\s+", re.I)
_WORD_DIRECTIVE = re.compile(
    r"(?:^|[^A-Za-z0-9_]|\\[nt])\.(?:word|4byte|long)\s+"
    r"(?:0x[0-9A-Fa-f]+|[-+]?\d)",
    re.I,
)
_FUNCTION_DIRECTIVE = re.compile(
    r"(?:^|[^A-Za-z0-9_]|\\[nt])\.(?:globl|global|ent|aent)\s+[A-Za-z_.$]",
    re.I,
)
_TEXT_SECTION = re.compile(
    r"(?:^|[^A-Za-z0-9_]|\\[nt])\.section\s+\.text\b", re.I
)
_NOREORDER = re.compile(
    r"(?:^|[^A-Za-z0-9_]|\\[nt])\.set\s+(?:noat|noreorder)\b", re.I
)
_RAW_BRIDGE = re.compile(r"raw[ -](?:byte|instruction)[ -]match[ -]bridge", re.I)
_INVENTED_SYMBOL = re.compile(
    r"(?<!\w)(?<!struct )(?<!union )(?<!enum )"
    r"(?!D_|func_|jtbl_)[A-Za-z]\w*_[0-9A-Fa-f]{8}\b"
)
_DECLARATION = re.compile(
    r"\b(?:(?:const|static|volatile|register)\s+)*"
    r"(?:(?:signed|unsigned)(?:\s+(?:char|short|int|long))?|"
    r"char|short|int|long|u?int(?:8|16|32|64)_t)\s+"
    r"(?P<name>[A-Za-z_]\w*)\s*"
    r"(?P<array>\[[^\]]*\])?\s*=\s*\{(?P<body>.*?)\}\s*;",
    re.I | re.S,
)
_SUSPICIOUS_STORAGE_NAME = re.compile(
    r"(?:^|_)(?:asm|code|codes|instruction|instructions|machine_code|opcode|"
    r"opcodes|pad|padding|raw_code|text_words)(?:_|$)",
    re.I,
)
_INTEGER = re.compile(
    r"(?<![A-Za-z0-9_])(?:0[xX][0-9A-Fa-f]+|\d+)(?:[uUlL]{0,3})(?![A-Za-z0-9_])"
)
_WORD_LITERAL = re.compile(
    r"(?<![A-Za-z0-9_])0[xX][0-9A-Fa-f]{8}(?:[uUlL]{0,3})(?![A-Za-z0-9_])"
)

_DIRECT_RULES = (
    ("inline-assembly", _INLINE_ASM, "inline assembly is not reconstructed C"),
    (
        "assembly-inclusion",
        _ASSEMBLY_INCLUDE,
        "assembly inclusion is not reconstructed C",
    ),
    ("assembly-label", _ASSEMBLY_LABEL, "assembly function labels are prohibited"),
    ("binary-inclusion", _BINARY_INCLUDE, "binary inclusion is prohibited"),
    (
        "instruction-word",
        _WORD_DIRECTIVE,
        "hardcoded assembler words are not reconstructed C",
    ),
    (
        "assembly-function-directive",
        _FUNCTION_DIRECTIVE,
        "assembler function directives are prohibited",
    ),
    (
        "assembly-text-section",
        _TEXT_SECTION,
        "an assembler text-section bridge is prohibited",
    ),
    (
        "assembly-mode-directive",
        _NOREORDER,
        "assembler mode directives are prohibited",
    ),
)


def _strip_comments(text: str) -> str:
    """Replace comments with spaces while retaining strings and line offsets."""
    result = list(text)
    index = 0
    state = "code"
    while index < len(text):
        char = text[index]
        next_char = text[index + 1] if index + 1 < len(text) else ""
        if state == "code":
            if char == '"':
                state = "string"
            elif char == "'":
                state = "character"
            elif char == "/" and next_char == "/":
                result[index] = result[index + 1] = " "
                index += 1
                state = "line-comment"
            elif char == "/" and next_char == "*":
                result[index] = result[index + 1] = " "
                index += 1
                state = "block-comment"
        elif state == "string":
            if char == "\\":
                index += 1
            elif char == '"':
                state = "code"
        elif state == "character":
            if char == "\\":
                index += 1
            elif char == "'":
                state = "code"
        elif state == "line-comment":
            if char == "\n":
                state = "code"
            else:
                result[index] = " "
        elif state == "block-comment":
            if char == "*" and next_char == "/":
                result[index] = result[index + 1] = " "
                index += 1
                state = "code"
            elif char != "\n":
                result[index] = " "
        index += 1
    return "".join(result)


def _line(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def _resolve_include(name: str, including: Path, root: Path) -> Path | None:
    for candidate in (including.parent / name, root / name, root / "include" / name):
        try:
            resolved = candidate.resolve()
            resolved.relative_to(root.resolve())
        except (OSError, ValueError):
            continue
        if resolved.is_file():
            return resolved
    return None


def _read_graph(source: Path, root: Path) -> dict[Path, str]:
    pending = [source.resolve()]
    files: dict[Path, str] = {}
    while pending:
        path = pending.pop()
        if path in files:
            continue
        try:
            text = path.read_text(errors="replace")
        except OSError:
            continue
        files[path] = text
        clean = _strip_comments(text)
        for match in _QUOTED_INCLUDE.finditer(clean):
            included = _resolve_include(match.group(1), path, root)
            if included is not None and included not in files:
                pending.append(included)
    return files


def _macros(files: dict[Path, str]) -> list[_Macro]:
    result: list[_Macro] = []
    for path, text in files.items():
        clean = _strip_comments(text)
        for match in _DEFINE.finditer(clean):
            result.append(
                _Macro(
                    name=match.group(1),
                    body=re.sub(r"\\\r?\n", " ", match.group("body")),
                    path=path,
                    line=_line(clean, match.start()),
                    function_like=match.group(2) is not None,
                )
            )
    return result


def _primitive_kind(text: str) -> str | None:
    for kind, pattern, _detail in _DIRECT_RULES:
        if pattern.search(text):
            return kind
    if _RAW_BRIDGE.search(text):
        return "raw-bridge-marker"
    # A macro may alias only the asm keyword and leave the opening parenthesis
    # to an outer wrapper, e.g. `#define EMIT __asm__`.
    if _ASM_IDENTIFIER.search(text):
        return "inline-assembly"
    if "##" in text and re.search(r"asm", text, re.I):
        return "inline-assembly"
    return None


def _macro_taint(macros: list[_Macro]) -> dict[str, str]:
    tainted: dict[str, str] = {}
    definitions: dict[str, list[_Macro]] = {}
    for macro in macros:
        definitions.setdefault(macro.name, []).append(macro)
        primitive = _primitive_kind(macro.body)
        if primitive is not None:
            tainted[macro.name] = primitive

    changed = True
    while changed:
        changed = False
        for name, variants in definitions.items():
            if name in tainted:
                continue
            dependencies = {
                identifier
                for macro in variants
                for identifier in _IDENTIFIER.findall(macro.body)
            }
            dependency = next(
                (item for item in sorted(dependencies) if item in tainted), None
            )
            if dependency is not None:
                tainted[name] = f"macro {dependency} -> {tainted[dependency]}"
                changed = True
    return tainted


def _definition_spans(text: str) -> list[tuple[int, int]]:
    clean = _strip_comments(text)
    return [(match.start(), match.end()) for match in _DEFINE.finditer(clean)]


def _in_spans(offset: int, spans: list[tuple[int, int]]) -> bool:
    return any(start <= offset < end for start, end in spans)


def audit_c_source(source: Path, *, repo_root: Path) -> list[SourceAuditIssue]:
    """Return all no-cheat violations reachable from one public C source."""
    source = source.resolve()
    root = repo_root.resolve()
    try:
        source.relative_to(root)
    except ValueError:
        return [
            SourceAuditIssue(
                source,
                1,
                "source-outside-repository",
                "a reconstructed C source must stay inside the repository",
            )
        ]
    files = _read_graph(source, root)
    issues: list[SourceAuditIssue] = []

    for path, text in files.items():
        clean = _strip_comments(text)
        for kind, pattern, detail in _DIRECT_RULES:
            for match in pattern.finditer(clean):
                issues.append(
                    SourceAuditIssue(path, _line(clean, match.start()), kind, detail)
                )
        for match in _RAW_BRIDGE.finditer(text):
            issues.append(
                SourceAuditIssue(
                    path,
                    _line(text, match.start()),
                    "raw-bridge-marker",
                    "a declared raw byte/instruction bridge is prohibited",
                )
            )
        invented = _INVENTED_SYMBOL.search(clean)
        if invented is not None:
            issues.append(
                SourceAuditIssue(
                    path,
                    _line(clean, invented.start()),
                    "invented-address-symbol",
                    f"{invented.group(0)} is not a disassembly-owned D_, "
                    "func_, or jtbl_ name",
                )
            )
        for declaration in _DECLARATION.finditer(clean):
            name = declaration.group("name")
            if _SUSPICIOUS_STORAGE_NAME.search(name) is None:
                continue
            body = declaration.group("body")
            integers = _INTEGER.findall(body)
            word_literals = _WORD_LITERAL.findall(body)
            explicit_array = declaration.group("array") or ""
            if len(word_literals) >= 4:
                detail = (
                    f"{name} contains a hardcoded {len(word_literals)}-word "
                    "instruction-like image"
                )
            elif len(integers) >= 4 or ("pad" in name.lower() and explicit_array):
                detail = f"{name} is suspicious hardcoded code/padding storage"
            else:
                continue
            issues.append(
                SourceAuditIssue(
                    path,
                    _line(clean, declaration.start()),
                    "hardcoded-code-storage",
                    detail,
                )
            )

    macros = _macros(files)
    tainted = _macro_taint(macros)
    for macro in macros:
        reason = tainted.get(macro.name)
        if reason is None:
            continue
        issues.append(
            SourceAuditIssue(
                macro.path,
                macro.line,
                "hidden-emitting-macro",
                f"macro {macro.name} expands through prohibited {reason}",
            )
        )

    for path, text in files.items():
        clean = _strip_comments(text)
        spans = _definition_spans(text)
        macro_forms: dict[str, bool] = {}
        for macro in macros:
            if macro.name in tainted:
                macro_forms[macro.name] = (
                    macro_forms.get(macro.name, True) and macro.function_like
                )
        for name, function_like in macro_forms.items():
            suffix = r"\s*\(" if function_like else r"\b"
            pattern = re.compile(rf"\b{re.escape(name)}{suffix}")
            for match in pattern.finditer(clean):
                if _in_spans(match.start(), spans):
                    continue
                issues.append(
                    SourceAuditIssue(
                        path,
                        _line(clean, match.start()),
                        "emitting-macro-use",
                        f"macro {name} expands to prohibited {tainted[name]}",
                    )
                )

    unique: dict[tuple[Path, int, str, str], SourceAuditIssue] = {}
    for issue in issues:
        unique[(issue.path, issue.line, issue.kind, issue.detail)] = issue
    return sorted(
        unique.values(), key=lambda issue: (str(issue.path), issue.line, issue.kind)
    )
