#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from build_controls import object_flag_errors


class BuildControlsTests(unittest.TestCase):
    def test_current_small_data_controls_are_reviewed(self) -> None:
        self.assertEqual(object_flag_errors(["-Wa,-G8"]), [])

    def test_unknown_and_conflicting_controls_fail(self) -> None:
        self.assertEqual(
            object_flag_errors(["-include", "target.inc"]),
            ["unsanctioned object flags: -include, target.inc"],
        )
        self.assertEqual(
            object_flag_errors(["-Wa,-G0", "-Wa,-G8"]),
            ["conflicting assembler small-data controls: -Wa,-G0, -Wa,-G8"],
        )


if __name__ == "__main__":
    unittest.main()
