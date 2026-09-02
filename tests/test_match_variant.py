#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from match import compare, work_variant


class CompareDistanceTests(unittest.TestCase):
    def test_equal_sizes_report_the_word_distance(self) -> None:
        expected = bytes(range(64))
        actual = bytearray(expected)
        actual[8] ^= 1
        actual[20] ^= 1
        summary = compare(expected, bytes(actual), verbose=False)
        self.assertIn("first byte +0x8", summary)
        self.assertIn("2/16 words differ", summary)

    def test_size_difference_reports_size_rather_than_distance(self) -> None:
        expected = bytes(range(64))
        summary = compare(expected, expected[:60], verbose=False)
        self.assertIn("size expected 64, actual 60", summary)
        self.assertNotIn("words differ", summary)

    def test_partial_difference_with_unequal_sizes_omits_distance(self) -> None:
        expected = bytes(range(64))
        actual = bytearray(expected[:60])
        actual[8] ^= 1
        summary = compare(expected, bytes(actual), verbose=False)
        self.assertIn("first byte +0x8", summary)
        self.assertNotIn("words differ", summary)

    def test_identical_input_is_a_match(self) -> None:
        self.assertEqual(compare(b"abcd", b"abcd", verbose=False), "MATCH")


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
