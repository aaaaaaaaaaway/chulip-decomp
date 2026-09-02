#!/usr/bin/env python3

import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import permute


class PermuteScriptTests(unittest.TestCase):
    def test_compile_script_carries_profile_and_every_object_flag(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = permute.write_compile_script(
                Path(directory), "ee-gcc2.95.3-136-O2-G8-ps2as", ["-Wa,-G0", "-Wa,-G8"]
            )
            body = path.read_text()
            self.assertIn("--profile ee-gcc2.95.3-136-O2-G8-ps2as", body)
            self.assertIn("--object-flag=-Wa,-G0", body)
            self.assertIn("--object-flag=-Wa,-G8", body)
            self.assertIn("permute_compile.py", body)

    def test_compile_script_is_executable(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = permute.write_compile_script(Path(directory), "profile-a", [])
            self.assertTrue(path.stat().st_mode & 0o111)

    def test_compile_script_reads_output_from_anywhere_in_the_arguments(self) -> None:
        # The permuter passes -o among other flags and not always last, so the
        # script must scan rather than assume a position.
        with tempfile.TemporaryDirectory() as directory:
            body = permute.write_compile_script(Path(directory), "profile-a", []).read_text()
            self.assertIn("while [ $# -gt 0 ]", body)
            self.assertIn("-o) OUTPUT=", body)

    def test_unknown_function_is_rejected(self) -> None:
        with self.assertRaises(SystemExit):
            permute.catalog_entry("func_not_in_the_catalog")


if __name__ == "__main__":
    unittest.main()
