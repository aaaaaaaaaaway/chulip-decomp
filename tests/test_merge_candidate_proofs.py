#!/usr/bin/env python3

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

import merge_candidates


def candidate(**overrides: object) -> merge_candidates.Candidate:
    values: dict[str, object] = {
        "function": "func_00100000",
        "source": "src/game/func_00100000.c",
        "build_profile": "profile-a",
        "verified_profiles": ("profile-a", "profile-b"),
        "object_flags": ("-Wa,-G0",),
        "unit_start": "0x00100000",
        "unit_end": "0x00100020",
        "rodata_start": "0x001E1000",
        "profile_evidence": None,
        "evidence": "exact retail bytes",
        "provenance_note": None,
        "line": 7,
    }
    values.update(overrides)
    return merge_candidates.Candidate(**values)


class CandidateProofTests(unittest.TestCase):
    @staticmethod
    def catalog() -> dict[str, object]:
        return {
            "functions": [
                {
                    "name": "func_00100000",
                    "address": "0x00100000",
                    "size": 32,
                }
            ]
        }

    @staticmethod
    def reconstructed_entry() -> dict[str, object]:
        return {
            "function": "func_00100000",
            "source": "src/game/old.c",
            "address": "0x00100000",
            "size": 32,
            "verified_profiles": ["profile-a"],
            "build_profile": "profile-a",
            "isolated_match": True,
            "whole_program_match": True,
        }

    @staticmethod
    def matched_entry() -> dict[str, object]:
        return {
            "function": "func_00100000",
            "source": "src/game/old.c",
            "address": "0x00100000",
            "size": 32,
            "profile": "profile-a",
            "evidence": "old exact proof",
        }

    def test_rejects_unreviewed_object_flag(self) -> None:
        with self.assertRaisesRegex(
            merge_candidates.CandidateError, "unsanctioned object flags"
        ):
            merge_candidates.validate_object_flags(("-include", "target.inc"), "line 1")

    def test_accepts_reviewed_object_flags(self) -> None:
        merge_candidates.validate_object_flags(
            ("-Wa,-G8", "-mno-split-addresses"), "line 1"
        )

    def test_existing_entry_requires_explicit_replacement(self) -> None:
        with self.assertRaisesRegex(
            merge_candidates.CandidateError, "function already exists in a ledger"
        ):
            merge_candidates.planned_entries(
                [candidate(verified_profiles=("profile-a",), object_flags=())],
                self.catalog(),
                [self.reconstructed_entry()],
                [self.matched_entry()],
            )

    def test_explicit_replacement_updates_both_ledgers(self) -> None:
        reconstructed, matched = merge_candidates.planned_entries(
            [candidate(verified_profiles=("profile-a",), object_flags=())],
            self.catalog(),
            [self.reconstructed_entry()],
            [self.matched_entry()],
            replace_existing=True,
        )
        self.assertEqual(len(reconstructed), 1)
        self.assertEqual(len(matched), 1)
        self.assertEqual(reconstructed[0]["source"], "src/game/func_00100000.c")
        self.assertEqual(matched[0]["source"], "src/game/func_00100000.c")

    def test_replacement_rejects_one_sided_ledger_entry(self) -> None:
        with self.assertRaisesRegex(
            merge_candidates.CandidateError, "inconsistent ledger entry"
        ):
            merge_candidates.planned_entries(
                [candidate(verified_profiles=("profile-a",), object_flags=())],
                self.catalog(),
                [self.reconstructed_entry()],
                [],
                replace_existing=True,
            )

    def test_replacement_identifies_only_superseded_sources(self) -> None:
        existing = [
            self.reconstructed_entry(),
            {
                **self.reconstructed_entry(),
                "function": "func_00100020",
                "source": "src/game/kept.c",
            },
        ]
        planned = [
            {
                **self.reconstructed_entry(),
                "source": "src/game/unit_00100000.c",
            },
            existing[1],
        ]
        obsolete = merge_candidates.obsolete_replaced_sources(
            [candidate(verified_profiles=("profile-a",), object_flags=())],
            existing,
            planned,
            replace_existing=True,
        )
        self.assertEqual(obsolete, (merge_candidates.ROOT / "src/game/old.c",))

    def test_rejects_conflicting_small_data_flags(self) -> None:
        with self.assertRaisesRegex(
            merge_candidates.CandidateError, "conflicting assembler small-data"
        ):
            merge_candidates.validate_object_flags(("-Wa,-G0", "-Wa,-G4"), "line 1")

    def test_definition_text_in_a_literal_does_not_count(self) -> None:
        self.assertFalse(
            merge_candidates.source_has_definition(
                'const char *claim = "int func_00100000(void) {";\n',
                "func_00100000",
            )
        )

    def test_vendored_c_alias_definition_counts(self) -> None:
        with tempfile.TemporaryDirectory(dir=merge_candidates.ROOT) as temporary:
            directory = Path(temporary)
            included = directory / "upstream.c"
            wrapper = directory / "wrapper.c"
            included.write_text("int original_name(void) { return 1; }\n")
            text = '#define original_name func_00100000\n#include "upstream.c"\n'
            wrapper.write_text(text)
            self.assertTrue(
                merge_candidates.source_has_definition(
                    text, "func_00100000", wrapper
                )
            )

    def test_legacy_conditional_macro_definition_counts(self) -> None:
        with tempfile.TemporaryDirectory(dir=merge_candidates.ROOT) as temporary:
            directory = Path(temporary)
            included = directory / "upstream.c"
            wrapper = directory / "wrapper.c"
            included.write_text(
                "#define internal_name upstream_name\n"
                "#if __STDC__\n"
                "int internal_name(int value)\n"
                "#else\n"
                "int internal_name(value) int value;\n"
                "#endif\n"
                "{ return value; }\n"
            )
            text = '#define upstream_name func_00100000\n#include "upstream.c"\n'
            wrapper.write_text(text)
            self.assertTrue(
                merge_candidates.source_has_definition(
                    text, "func_00100000", wrapper
                )
            )

    def test_legacy_conditional_definition_with_two_knr_parameters_counts(self) -> None:
        text = (
            "#if __STDC__\n"
            "void *upstream_name(unsigned int count, unsigned int size)\n"
            "#else\n"
            "void *upstream_name(count, size) unsigned int count; unsigned int size;\n"
            "#endif\n"
            "{ return 0; }\n"
        )
        self.assertTrue(
            merge_candidates.source_has_definition(text, "upstream_name")
        )

    def test_legacy_knr_macro_definition_counts(self) -> None:
        with tempfile.TemporaryDirectory(dir=merge_candidates.ROOT) as temporary:
            directory = Path(temporary)
            included = directory / "upstream.c"
            wrapper = directory / "wrapper.c"
            included.write_text(
                "int\n"
                "upstream_name(value)\n"
                "    int value;\n"
                "{ return value; }\n"
            )
            text = '#define upstream_name func_00100000\n#include "upstream.c"\n'
            wrapper.write_text(text)
            self.assertTrue(
                merge_candidates.source_has_definition(
                    text, "func_00100000", wrapper
                )
            )

    def test_command_carries_complete_candidate_configuration(self) -> None:
        command = merge_candidates.proof_command(candidate(), "profile-b")
        self.assertEqual(
            command,
            [
                sys.executable,
                "tools/match.py",
                "func_00100000",
                "--source",
                "src/game/func_00100000.c",
                "--profile",
                "profile-b",
                "--quiet",
                "--range-start",
                "0x00100000",
                "--range-end",
                "0x00100020",
                "--rodata-start",
                "0x001E1000",
                "--object-flag=-Wa,-G0",
            ],
        )

    @patch("merge_candidates.subprocess.run")
    def test_replays_every_claimed_profile(self, run: object) -> None:
        run.return_value = subprocess.CompletedProcess([], 0, "profile: MATCH\n", "")
        summary = merge_candidates.verify_candidate_proofs([candidate()])
        self.assertEqual(summary, (2, 2))
        self.assertEqual(run.call_count, 2)

    @patch("merge_candidates.subprocess.run")
    def test_each_function_gets_its_own_symbol_checked_proof(self, run: object) -> None:
        run.return_value = subprocess.CompletedProcess([], 0, "profile: MATCH\n", "")
        second = candidate(function="func_00100010", line=8)
        summary = merge_candidates.verify_candidate_proofs(
            [candidate(verified_profiles=("profile-a",)), second]
        )
        self.assertEqual(summary, (3, 3))
        self.assertEqual(run.call_count, 3)

    @patch("merge_candidates.subprocess.run")
    def test_rejects_failed_match(self, run: object) -> None:
        run.return_value = subprocess.CompletedProcess([], 1, "profile: MISMATCH\n", "")
        with self.assertRaisesRegex(merge_candidates.CandidateError, "independent proof failed"):
            merge_candidates.verify_candidate_proofs([candidate(verified_profiles=("profile-a",))])

    @patch("merge_candidates.subprocess.run")
    def test_rejects_unsafe_warning_even_when_bytes_match(self, run: object) -> None:
        run.return_value = subprocess.CompletedProcess(
            [],
            0,
            "profile: MATCH\n",
            "warning: implicit declaration of function `callee'\n",
        )
        with self.assertRaisesRegex(merge_candidates.CandidateError, "unsafe compiler diagnostics"):
            merge_candidates.verify_candidate_proofs([candidate(verified_profiles=("profile-a",))])

    def test_transaction_removes_a_regenerated_obsolete_source_before_audit(self) -> None:
        with tempfile.TemporaryDirectory(dir=merge_candidates.ROOT) as temporary:
            obsolete = Path(temporary) / "old.c"
            obsolete.write_text("old source\n")

            def saved(paths: tuple[Path, ...]) -> dict[Path, merge_candidates.Backup]:
                return {
                    path: merge_candidates.Backup(b"", 0o644)
                    for path in paths
                }

            def run(command: list[str]) -> None:
                if command == ["make", "verify"]:
                    obsolete.write_text("generated fallback\n")
                if command == ["make", "public-check"]:
                    self.assertFalse(obsolete.exists())

            with (
                patch("merge_candidates.backups", side_effect=saved),
                patch("merge_candidates.atomic_write"),
                patch("merge_candidates.run", side_effect=run),
            ):
                merge_candidates.write_transaction([], [], (obsolete,))

            self.assertFalse(obsolete.exists())


if __name__ == "__main__":
    unittest.main()
