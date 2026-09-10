#!/usr/bin/env python3

import sys
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest import mock

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


class PermuteTargetTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.directory = Path(self.temp.name)
        catalog = self.directory / "functions.json"
        catalog.write_text(json.dumps({"functions": [
            {"name": "func_00110000", "address": "0x00110000", "size": 8}
        ]}))
        patch = mock.patch.object(permute, "CATALOG", catalog)
        patch.start()
        self.addCleanup(patch.stop)

    def test_retail_extent_includes_alignment_and_rejects_truncation(self) -> None:
        target = self.directory / "retail.bin"
        target.write_bytes(b"abcdefgh")
        entry = {"address": "0x00100000", "size": 4}
        with mock.patch.object(permute, "TARGET", target):
            self.assertEqual(permute.retail_bytes(entry), b"abcd")
            self.assertEqual(permute.retail_bytes(entry, 0x100008), b"abcdefgh")
            with self.assertRaises(ValueError):
                permute.retail_bytes(entry, 0x100002)
            with self.assertRaises(SystemExit):
                permute.retail_bytes(entry, 0x10000C)

    def test_only_direct_calls_receive_catalog_relocations(self) -> None:
        body = struct.pack("<III", (3 << 26) | (0x110000 >> 2), 0, 0x03E00008)
        listing = permute.direct_call_listing("func_00100000", body, 0x100000)
        self.assertEqual(listing.count("\njal "), 1)
        self.assertIn("jal func_00110000", listing)
        self.assertIn(".word 0x03E00008", listing)

    def test_unknown_and_internal_call_destinations_are_rejected(self) -> None:
        for address, message in ((0x120000, "absent from the catalog"),
                                 (0x100000, "internal JAL")):
            body = struct.pack("<I", (3 << 26) | (address >> 2))
            with self.subTest(address=address), self.assertRaisesRegex(ValueError, message):
                permute.direct_call_listing("func_00100000", body, 0x100000)

    def test_partial_or_unaligned_instructions_are_rejected(self) -> None:
        for body, address in ((b"abc", 0x100000), (b"abcd", 0x100001)):
            with self.subTest(address=address), self.assertRaisesRegex(ValueError, "aligned"):
                permute.direct_call_listing("func_00100000", body, address)

    def test_linked_oracle_must_match_every_byte_including_alignment(self) -> None:
        obj = self.directory / "target.o"
        obj.touch()
        actual = b"abcdefgh"

        def link_output(command, **kwargs):
            if command[0] == "mipsel-linux-gnu-objcopy":
                Path(command[-1]).write_bytes(actual)

        with mock.patch.object(permute.match, "write_derived_symbols") as derived, \
             mock.patch.object(permute.subprocess, "run", side_effect=link_output):
            permute.verify_target_object(obj, self.directory, 0x100000, actual)
            derived.assert_called_once_with(obj.resolve(), self.directory / "target_derived.ld")
            for expected in (actual[:-4], b"abcdefgi"):
                with self.assertRaisesRegex(ValueError, "full retail-byte verification"):
                    permute.verify_target_object(obj, self.directory, 0x100000, expected)

    def test_failed_oracle_is_removed_before_it_can_be_used(self) -> None:
        def assemble(command, **kwargs):
            (self.directory / "target.o").write_bytes(b"invalid oracle")

        with mock.patch.object(permute.subprocess, "run", side_effect=assemble), \
             mock.patch.object(permute, "verify_target_object", side_effect=ValueError("mismatch")):
            with self.assertRaisesRegex(ValueError, "mismatch"):
                permute.write_target_object("func_00100000", bytes(4), self.directory,
                                            address=0x100000, relocate_direct_calls=True)
        self.assertFalse((self.directory / "target.o").exists())

    def test_reused_directory_drops_stale_target_on_early_build_failure(self) -> None:
        target = self.directory / "target.o"
        unknown_call = struct.pack("<I", (3 << 26) | (0x120000 >> 2))
        for body, error in ((unknown_call, ValueError), (bytes(4), RuntimeError)):
            with self.subTest(error=error):
                target.write_bytes(b"previous accepted target")
                with mock.patch.object(permute.subprocess, "run", side_effect=RuntimeError("assembler failed")):
                    with self.assertRaises(error):
                        permute.write_target_object("func_00100000", body, self.directory,
                                                    address=0x100000, relocate_direct_calls=True)
                self.assertFalse(target.exists())

    def test_invalid_range_does_not_mix_new_source_with_previous_oracle(self) -> None:
        source = self.directory / "new.c"
        source.write_text("new candidate")
        base = self.directory / "base.c"
        base.write_text("previous candidate")
        target = self.directory / "target.o"
        target.write_bytes(b"previous oracle")
        argv = ["permute.py", "func_00110000", "--source", str(source),
                "--profile", "test-profile", "--output-dir", str(self.directory),
                "--range-end", "0x00110004"]
        with mock.patch.object(sys, "argv", argv), \
             mock.patch.object(permute, "ledger_entry", return_value=None), \
             mock.patch.object(permute, "verified_candidate", return_value=None):
            with self.assertRaises(ValueError):
                permute.main()
        self.assertEqual(base.read_text(), "previous candidate")
        self.assertEqual(target.read_bytes(), b"previous oracle")


if __name__ == "__main__":
    unittest.main()
