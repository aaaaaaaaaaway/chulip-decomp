from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import asm_diff
import dup_guard
import match_artifacts
import region_match
import similar_functions


class AsmDiffTests(unittest.TestCase):
    def test_difference_classification(self):
        self.assertEqual(asm_diff.classify_difference("addu $v0,$a0,$a1", "subu $v0,$a0,$a1"), "opcode")
        self.assertEqual(asm_diff.classify_difference("lw $v0,4($sp)", "lw $v1,4($sp)"), "register")
        self.assertEqual(asm_diff.classify_difference("lw v0,4(sp)", "lw v1,4(sp)"), "register")
        self.assertEqual(
            asm_diff.classify_difference("addiu $sp,$sp,-16", "addiu $sp,$sp,-32"),
            "immediate/target",
        )

    def test_render_match_and_mismatch(self):
        left = [(0, "00000000", "nop")]
        self.assertEqual(asm_diff.render(left, left, 0x1000, 4)[1], 0)
        report, status = asm_diff.render(left, [(0, "03e00008", "jr $ra")], 0x1000, 4)
        self.assertEqual(status, 1)
        self.assertIn("opcode", report)


class SimilarityTests(unittest.TestCase):
    def test_edit_distance_and_similarity(self):
        self.assertEqual(similar_functions.levenshtein(["lw", "jr"], ["lw", "nop", "jr"]), 1)
        self.assertEqual(similar_functions.similarity(["lw", "jr"], ["lw", "jr"]), 1.0)
        self.assertEqual(similar_functions.similarity(["lw"], ["lw"] * 4), 0.0)

    def test_ngram_jaccard(self):
        self.assertEqual(similar_functions.ngram_jaccard(["a", "b", "c"], ["a", "b", "c"]), 1.0)
        self.assertEqual(similar_functions.ngram_jaccard([], []), 1.0)


class MatchArtifactTests(unittest.TestCase):
    def test_reconstruction_defaults_are_authoritative(self):
        with patch.object(match_artifacts.match, "jump_table_address", return_value=None):
            spec = match_artifacts.resolve_spec("func_00100488")
        self.assertEqual(spec.address, 0x00100488)
        self.assertEqual(spec.end, 0x00100490)
        self.assertEqual(spec.profile_name, "ee-gcc2.95.3-136-O2-G8")

    def test_range_must_contain_function(self):
        with self.assertRaises(ValueError):
            match_artifacts.resolve_spec(
                "func_00100488", range_start=0x0010048C, range_end=0x00100490
            )


class RegionTests(unittest.TestCase):
    def test_delay_slot_fallthrough_and_direct_target_are_leaders(self):
        instructions = [
            (0, "0", "beq $a0,$zero,0x1010"),
            (4, "0", "nop"),
            (8, "0", "addiu $v0,$zero,1"),
            (12, "0", "jr $ra"),
            (16, "0", "nop"),
        ]
        self.assertEqual(region_match.basic_block_leaders(instructions, 0x1000, 20), [0, 2, 4])

    def test_window_parser(self):
        self.assertEqual(region_match.parse_window("0x10:32"), (16, 32))
        region_match.validate_window((16, 32), 64)
        with self.assertRaises(ValueError):
            region_match.validate_window((2, 8), 64)
        with self.assertRaises(ValueError):
            region_match.validate_window((16, 68), 64)


class DuplicateGuardTests(unittest.TestCase):
    def test_comments_and_formatting_do_not_change_fingerprint(self):
        context = {"profile": "p", "object_flags": []}
        left = dup_guard.fingerprint("int f(void) { return 1; }", context)
        right = dup_guard.fingerprint("/* note */ int f(void){return 1;}// x", context)
        self.assertEqual(left, right)

    def test_literals_and_profile_do_change_fingerprint(self):
        base = dup_guard.fingerprint('char *s = "a b";', {"profile": "p"})
        self.assertNotEqual(base, dup_guard.fingerprint('char *s = "ab";', {"profile": "p"}))
        self.assertNotEqual(base, dup_guard.fingerprint('char *s = "a b";', {"profile": "q"}))

    def test_ledger_round_trip(self):
        with tempfile.TemporaryDirectory() as directory:
            ledger = Path(directory) / "attempts.jsonl"
            dup_guard.record("abc", "func_x", {"profile": "p"}, "mismatch", 3, ledger)
            found = dup_guard.find_duplicate("abc", "func_x", ledger)
            self.assertIsNotNone(found)
            self.assertEqual(found["differing_instructions"], 3)


if __name__ == "__main__":
    unittest.main()
