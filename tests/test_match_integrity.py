from __future__ import annotations

import subprocess
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import match


class MatchIntegrityTests(unittest.TestCase):
    def test_missing_or_mismatched_jump_table_fails_profile(self):
        report, exact = match.compare_rodata(b"", match.TEXT_VRAM, b"abcd")
        self.assertFalse(exact)
        self.assertIn("MISSING", report)

        report, exact = match.compare_rodata(b"xx", match.TEXT_VRAM, b"abcd")
        self.assertFalse(exact)
        self.assertIn("MISMATCH", report)

    def test_exact_jump_table_passes_profile(self):
        report, exact = match.compare_rodata(b"ab", match.TEXT_VRAM, b"abcd")
        self.assertTrue(exact)
        self.assertIn("MATCH", report)

    def test_linker_places_source_owned_data_at_derived_retail_address(self):
        script = match.linker_script(
            match.TEXT_VRAM, None, match.SDATA_VRAM, data=0x001E4EB8
        )
        self.assertIn(".data 0x001E4EB8", script)

    @patch("match.subprocess.run")
    def test_requested_function_must_be_defined_in_object(self, run):
        run.return_value = subprocess.CompletedProcess(
            [], 0, "00000000 T another_function\n", ""
        )
        self.assertFalse(match.object_defines_symbol(Path("candidate.o"), "wanted"))


if __name__ == "__main__":
    unittest.main()
