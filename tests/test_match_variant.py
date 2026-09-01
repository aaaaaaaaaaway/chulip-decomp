#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from match import work_variant


class MatchVariantTests(unittest.TestCase):
    def test_sdata_and_sbss_origins_change_variant(self) -> None:
        base = (Path("src/game/example.c"), [], 0x100000, 0x100020, None)
        self.assertNotEqual(
            work_variant(*base, 0x1EC880, None),
            work_variant(*base, 0x1EC884, None),
        )
        self.assertNotEqual(
            work_variant(*base, 0x1EC880, None),
            work_variant(*base, 0x1EC880, 0x1ED080),
        )


if __name__ == "__main__":
    unittest.main()
