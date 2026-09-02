#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import progress


DATA = {
    "total_functions": 2189,
    "total_bytes": 663704,
    "matched_functions": 1213,
    "matched_bytes": 152452,
    "function_percent": 55.4134,
    "byte_percent": 22.9699,
}


class ProgressBlockTests(unittest.TestCase):
    def test_status_block_carries_the_ledger_counts(self) -> None:
        block = progress.status_markdown(DATA)
        self.assertIn("**1,213 functions / 152,452 bytes**", block)
        self.assertIn("**1,213 / 2,189 (55.4134%)**", block)
        self.assertIn("**152,452 / 663,704 (22.9699%)**", block)
        self.assertTrue(block.startswith(progress.STATUS_START))
        self.assertTrue(block.endswith(progress.STATUS_END))

    def test_block_error_accepts_a_current_document(self) -> None:
        block = progress.status_markdown(DATA)
        document = f"# Status\n\n{block}\n\ntail\n"
        self.assertIsNone(
            progress.block_error(
                document, block, progress.STATUS_START, progress.STATUS_END, "STATUS"
            )
        )

    def test_block_error_reports_stale_and_missing_markers(self) -> None:
        block = progress.status_markdown(DATA)
        stale = f"# Status\n\n{progress.STATUS_START}\nold\n{progress.STATUS_END}\n"
        self.assertIn(
            "stale",
            progress.block_error(
                stale, block, progress.STATUS_START, progress.STATUS_END, "STATUS"
            ),
        )
        self.assertIn(
            "markers are missing",
            progress.block_error(
                "# Status\n", block, progress.STATUS_START, progress.STATUS_END, "STATUS"
            ),
        )

    def test_reader_seam_defaults_to_the_worktree(self) -> None:
        data = progress.progress_data()
        self.assertEqual(data["total_functions"], len(
            __import__("json").loads((ROOT / "config/functions.json").read_text())["functions"]
        ))


if __name__ == "__main__":
    unittest.main()
