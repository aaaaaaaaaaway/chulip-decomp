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
    def test_rejects_unreviewed_object_flag(self) -> None:
        with self.assertRaisesRegex(
            merge_candidates.CandidateError, "unsanctioned object flags"
        ):
            merge_candidates.validate_object_flags(("-include", "target.inc"), "line 1")

    def test_accepts_reviewed_object_flags(self) -> None:
        merge_candidates.validate_object_flags(
            ("-Wa,-G8", "-mno-split-addresses"), "line 1"
        )

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


if __name__ == "__main__":
    unittest.main()
