from __future__ import annotations

import sys
import struct
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import build


class BuildLayoutTests(unittest.TestCase):
    def test_load_layout_rejects_inflated_zero_fill_and_wrong_file_extent(self):
        ident = b"\x7fELF\x01\x01\x01" + b"\0" * 9
        header = struct.pack("<16sHHIIIIIHHHHHH", ident, 2, 8, 1,
                             0x100000, 52, 0, 0, 52, 32, 1, 0, 0, 0)
        expected = {"vram": "0x100000", "file_size": "0x4", "memory_size": "0x10"}
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "linked.elf"
            for file_size, memory_size in [(4, 16), (4, 0x100010), (8, 16)]:
                with self.subTest(file_size=file_size, memory_size=memory_size):
                    segment = struct.pack("<IIIIIIII", 1, 84, 0x100000, 0,
                                          file_size, memory_size, 7, 4)
                    path.write_bytes(header + segment + b"\0" * file_size)
                    if (file_size, memory_size) == (4, 16):
                        build.verify_load_layout(path, expected)
                    else:
                        with self.assertRaisesRegex(SystemExit, "PT_LOAD layout mismatch"):
                            build.verify_load_layout(path, expected)

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
        self.assertIn(". = ABSOLUTE(0x002E53AC);", rendered)

    def test_source_owned_data_is_moved_between_split_assembly_spans(self):
        obj = build.ROOT / "build/src/game/newlib_mallocr.o"
        listed = "        build/src/game/newlib_mallocr.o(.data*);\n"
        suffix = "        build/asm/data/cod/data_001E5310.data.o(.data*);\n"
        rendered = build.pin_source_data(
            listed + suffix, {obj: (0x001E4EB8, 0x001E5310)}
        )
        self.assertEqual(rendered.count(listed), 1)
        self.assertLess(rendered.index(listed), rendered.index(suffix))


if __name__ == "__main__":
    unittest.main()
