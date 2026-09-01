import struct
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import elf_completeness


def synthetic_elf(payload: bytes, load_offset: int, paddr: int, memsz: int, align: int) -> bytes:
    names = b"\0.text\0.bss\0.shstrtab\0"
    names_offset = load_offset + len(payload)
    shoff = (names_offset + len(names) + 3) & ~3
    total = shoff + 4 * 40
    blob = bytearray(total)
    ident = b"\x7fELF\x01\x01\x01" + bytes(9)
    struct.pack_into(
        "<16sHHIIIIIHHHHHH",
        blob,
        0,
        ident,
        2,
        8,
        1,
        0x1000,
        52,
        shoff,
        0,
        52,
        32,
        1,
        40,
        4,
        3,
    )
    struct.pack_into("<IIIIIIII", blob, 52, 1, load_offset, 0x1000, paddr, len(payload), memsz, 7, align)
    blob[load_offset : load_offset + len(payload)] = payload
    blob[names_offset : names_offset + len(names)] = names
    struct.pack_into("<IIIIIIIIII", blob, shoff + 40, 1, 1, 6, 0x1000, load_offset, len(payload), 0, 0, 4, 0)
    struct.pack_into(
        "<IIIIIIIIII",
        blob,
        shoff + 80,
        7,
        8,
        3,
        0x1000 + len(payload),
        load_offset + len(payload),
        memsz - len(payload),
        0,
        0,
        4,
        0,
    )
    struct.pack_into("<IIIIIIIIII", blob, shoff + 120, 12, 3, 0, 0, names_offset, len(names), 0, 0, 1, 0)
    return bytes(blob)


def config_for(path: Path, payload: bytes, memsz: int) -> dict:
    data = path.read_bytes()
    return {
        "size": len(data),
        "sha256": elf_completeness.sha256(data),
        "entry": "0x1000",
        "load_segment": {
            "file_offset": "0x100",
            "vram": "0x1000",
            "file_size": hex(len(payload)),
            "memory_size": hex(memsz),
            "sha256": elf_completeness.sha256(payload),
        },
        "sections": [
            {"name": ".text", "vram": "0x1000", "offset": "0x100", "size": hex(len(payload))},
            {
                "name": ".bss",
                "vram": hex(0x1000 + len(payload)),
                "size": hex(memsz - len(payload)),
            },
        ],
    }


class ElfCompletenessTest(unittest.TestCase):
    def test_virtual_mapping_separates_load_bytes_from_container(self):
        payload = b"retail payload"
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            target_path = root / "target.elf"
            candidate_path = root / "candidate.elf"
            target_path.write_bytes(synthetic_elf(payload, 0x100, 0x1000, 0x80, 0x100))
            candidate_path.write_bytes(synthetic_elf(payload, 0x200, 0, 0x70, 0x200))
            target = elf_completeness.parse_elf(target_path)
            candidate = elf_completeness.parse_elf(candidate_path)
            report = elf_completeness.compare(target, candidate, config_for(target_path, payload, 0x80))
            self.assertTrue(report["target_config"]["exact"])
            self.assertTrue(report["load_image_bytes"]["exact"])
            self.assertFalse(report["full_elf_container"]["exact"])
            self.assertFalse(report["program_header_layout"]["exact"])
            self.assertFalse(report["program_header_layout"]["candidate_covers_target_memory"])

    def test_identical_container_passes_every_identity_check(self):
        payload = b"same"
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "same.elf"
            path.write_bytes(synthetic_elf(payload, 0x100, 0x1000, 0x20, 0x100))
            parsed = elf_completeness.parse_elf(path)
            report = elf_completeness.compare(parsed, parsed, config_for(path, payload, 0x20))
            self.assertTrue(report["full_elf_container"]["exact"])
            self.assertTrue(report["load_image_bytes"]["exact"])
            self.assertTrue(report["elf_header"]["exact"])
            self.assertTrue(report["program_header_layout"]["exact"])
            self.assertTrue(report["allocated_section_layout"]["exact"])
            self.assertTrue(report["bss_layout"]["exact"])


if __name__ == "__main__":
    unittest.main()
