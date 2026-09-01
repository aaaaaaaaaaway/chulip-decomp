from __future__ import annotations

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import build


class BuildLayoutTests(unittest.TestCase):
    def test_jump_table_proofs_are_not_loadable_sections(self):
        obj = build.ROOT / "build/example.o"
        listed = "        build/example.o(.rodata*);\n"
        linker = listed + "    /DISCARD/ :\n"
        rendered = build.pin_jump_tables(linker, {obj: 0x001E7000})
        self.assertNotIn(listed, rendered)
        self.assertIn(".jtbl_example 0x001E7000 (INFO)", rendered)

    def test_bss_tail_uses_configured_memory_end(self):
        linker = "        cod_BSS_END = .;\n"
        rendered = build.extend_bss_to_memory_end(linker, 0x002E53AC)
        self.assertIn(". = 0x002E53AC;", rendered)


if __name__ == "__main__":
    unittest.main()
