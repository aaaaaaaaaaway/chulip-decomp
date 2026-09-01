from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import merge_candidates
import repo_audit
from source_audit import audit_c_source


class SourceAuditTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        (self.root / "src").mkdir()
        (self.root / "include").mkdir()

    def tearDown(self) -> None:
        self.temporary.cleanup()

    def write(self, relative: str, text: str) -> Path:
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
        return path

    def issues(self, text: str):
        source = self.write("src/test.c", text)
        return audit_c_source(source, repo_root=self.root)

    def kinds(self, text: str) -> set[str]:
        return {issue.kind for issue in self.issues(text)}

    def test_benign_natural_c_and_comments_pass(self) -> None:
        issues = self.issues(
            """
            /* An example such as asm(\".word 0x03e00008\") is forbidden. */
            static const unsigned color_words[] = {
                0x11223344, 0x55667788, 0x99aabbcc, 0xddeeff00
            };
            #define DOUBLE(value) ((value) + (value))
            int func_00100000(int value) { return DOUBLE(value); }
            """
        )
        self.assertEqual(issues, [])

    def test_every_inline_asm_spelling_is_rejected(self) -> None:
        for spelling in ("asm", "__asm", "__asm__"):
            with self.subTest(spelling=spelling):
                self.assertIn(
                    "inline-assembly",
                    self.kinds(f'int f(void) {{ {spelling} volatile ("nop"); }}'),
                )
        self.assertIn(
            "inline-assembly",
            self.kinds(
                'int f(void) { asm volatile goto ("nop" :::: done); '
                "done: return 0; }"
            ),
        )

    def test_full_function_bridge_markers_are_rejected(self) -> None:
        text = """
        INCLUDE_ASM("asm/game", func_00100000);
        const char *body = ".globl func_00100000\\n.word 0x03e00008";
        const char *blob = ".incbin \\\"original/text.bin\\\"";
        """
        kinds = self.kinds(text)
        self.assertIn("assembly-inclusion", kinds)
        self.assertIn("assembly-function-directive", kinds)
        self.assertIn("instruction-word", kinds)
        self.assertIn("binary-inclusion", kinds)

    def test_nested_and_continued_macros_are_tainted(self) -> None:
        issues = self.issues(
            """
            #define EMIT_ONE() \\
                __asm__("nop")
            #define INNER() EMIT_ONE()
            #define OUTER() INNER()
            void f(void) { OUTER(); }
            """
        )
        hidden = {issue.detail for issue in issues if issue.kind == "hidden-emitting-macro"}
        self.assertTrue(any("INNER" in detail for detail in hidden))
        self.assertTrue(any("OUTER" in detail for detail in hidden))
        self.assertTrue(
            any(
                issue.kind == "emitting-macro-use" and "OUTER" in issue.detail
                for issue in issues
            )
        )

    def test_bare_asm_alias_cannot_hide_an_outer_call(self) -> None:
        issues = self.issues(
            """
            #define LOW_LEVEL __asm__
            #define EMIT(template) LOW_LEVEL(template)
            void f(void) { EMIT("nop"); }
            """
        )
        self.assertTrue(
            any(
                issue.kind == "hidden-emitting-macro" and "EMIT" in issue.detail
                for issue in issues
            )
        )

    def test_local_header_macros_are_followed(self) -> None:
        header = self.write(
            "include/private_emit.h",
            '#define EMIT_RETURN() __asm__(".word 0x03e00008")\n',
        )
        source = self.write(
            "src/test.c",
            '#include "private_emit.h"\nvoid f(void) { EMIT_RETURN(); }\n',
        )
        issues = audit_c_source(source, repo_root=self.root)
        self.assertTrue(any(issue.path == header.resolve() for issue in issues))
        self.assertTrue(
            any(
                issue.path == source.resolve()
                and issue.kind == "emitting-macro-use"
                for issue in issues
            )
        )

    def test_suspicious_instruction_and_padding_storage_is_rejected(self) -> None:
        issues = self.issues(
            """
            static const uint32_t code_words[] = {
                0x27bdffe0, 0xafbf001c, 0x03e00008, 0x00000000
            };
            static unsigned char alignment_pad[32] = { 0 };
            """
        )
        storage = [issue for issue in issues if issue.kind == "hardcoded-code-storage"]
        self.assertEqual(len(storage), 2)

    def test_raw_bridge_declaration_is_rejected_even_in_comment(self) -> None:
        self.assertIn(
            "raw-bridge-marker",
            self.kinds("/* raw byte match bridge */\nint f(void) { return 0; }\n"),
        )

    def test_only_disassembly_owned_address_symbols_are_allowed(self) -> None:
        self.assertIn(
            "invented-address-symbol",
            self.kinds(
                "extern int state_00123456; "
                "int f(void) { return state_00123456; }"
            ),
        )
        self.assertNotIn(
            "invented-address-symbol",
            self.kinds(
                "struct layout_00123456 { int x; }; "
                "extern int D_00123456; int f(void) { return D_00123456; }"
            ),
        )

    def test_candidate_ingestion_uses_shared_audit(self) -> None:
        self.write(
            "src/candidate.c",
            'int wanted(void) { __asm__("nop"); return 0; }\n',
        )
        old_root = merge_candidates.ROOT
        merge_candidates.ROOT = self.root
        try:
            with self.assertRaisesRegex(merge_candidates.CandidateError, "inline-assembly"):
                merge_candidates.validate_source("src/candidate.c", ["wanted"])
        finally:
            merge_candidates.ROOT = old_root

    def test_repository_audit_uses_shared_audit(self) -> None:
        self.write(
            "src/ledgered.c",
            'int wanted(void) { __asm__("nop"); return 0; }\n',
        )
        self.write(
            "config/reconstructed.json",
            '[{"function":"wanted","source":"src/ledgered.c"}]\n',
        )
        old_root = repo_audit.ROOT
        repo_audit.ROOT = self.root
        try:
            errors: list[str] = []
            repo_audit.matched_sources_are_decompiled(errors)
            self.assertTrue(any("inline-assembly" in error for error in errors))
        finally:
            repo_audit.ROOT = old_root


if __name__ == "__main__":
    unittest.main()
