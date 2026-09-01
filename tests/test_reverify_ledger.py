#!/usr/bin/env python3

import argparse
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

import reverify_ledger


def catalog(*functions: tuple[str, int, int]) -> list[dict[str, object]]:
    return [
        {"name": name, "address": f"0x{address:08X}", "size": size}
        for name, address, size in functions
    ]


def entry(
    function: str,
    source: str,
    address: int,
    size: int,
    profiles: list[str],
    **extra: object,
) -> dict[str, object]:
    result: dict[str, object] = {
        "function": function,
        "source": source,
        "address": f"0x{address:08X}",
        "size": size,
        "verified_profiles": profiles,
        "build_profile": profiles[0],
        "isolated_match": True,
        "whole_program_match": True,
    }
    result.update(extra)
    return result


class LedgerProofTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        (self.root / "src/game").mkdir(parents=True)
        (self.root / "src/game/unit.c").write_text("void a(void) {}\nvoid b(void) {}\n")
        self.root_patch = patch.object(reverify_ledger, "ROOT", self.root)
        self.root_patch.start()

    def tearDown(self) -> None:
        self.root_patch.stop()
        self.temporary.cleanup()

    def test_collapses_shared_complete_unit_once_per_claimed_profile(self) -> None:
        ledger = [
            entry(
                "a", "src/game/unit.c", 0x1000, 8, ["p1", "p2"],
                unit_start="0x1000", unit_end="0x1010", object_flags=["-Wa,-G0"],
            ),
            entry(
                "b", "src/game/unit.c", 0x1008, 8, ["p1"],
                unit_start="0x1000", unit_end="0x1010", object_flags=["-Wa,-G0"],
            ),
        ]
        proofs = reverify_ledger.build_proofs(
            ledger, catalog(("a", 0x1000, 8), ("b", 0x1008, 8)), {"p1": {}, "p2": {}}
        )
        self.assertEqual(len(proofs), 2)
        by_profile = {proof.profile: proof for proof in proofs}
        self.assertEqual([claim.function for claim in by_profile["p1"].claims], ["a", "b"])
        self.assertEqual([claim.function for claim in by_profile["p2"].claims], ["a"])

    def test_rejects_inconsistent_shared_source_range(self) -> None:
        ledger = [
            entry(
                "a", "src/game/unit.c", 0x1000, 8, ["p"],
                unit_start="0x1000", unit_end="0x1010",
            ),
            entry(
                "b", "src/game/unit.c", 0x1008, 8, ["p"],
                unit_start="0x1008", unit_end="0x1010",
            ),
        ]
        with self.assertRaisesRegex(reverify_ledger.LedgerError, "inconsistent complete range"):
            reverify_ledger.build_proofs(
                ledger, catalog(("a", 0x1000, 8), ("b", 0x1008, 8)), {"p": {}}
            )

    def test_rejects_range_that_truncates_claimed_function(self) -> None:
        ledger = [
            entry(
                "a", "src/game/unit.c", 0x1000, 8, ["p"],
                unit_start="0x1000", unit_end="0x1004",
            )
        ]
        with self.assertRaisesRegex(reverify_ledger.LedgerError, "complete function"):
            reverify_ledger.build_proofs(ledger, catalog(("a", 0x1000, 8)), {"p": {}})

    def proof(self) -> reverify_ledger.Proof:
        first = reverify_ledger.Claim(
            "a", "src/game/unit.c", "p", 0x1000, 0x1010, ("-Wa,-G0",), 0x1000, 8
        )
        second = reverify_ledger.Claim(
            "b", "src/game/unit.c", "p", 0x1000, 0x1010, ("-Wa,-G0",), 0x1008, 8
        )
        return reverify_ledger.Proof(
            "src/game/unit.c", "p", 0x1000, 0x1010, ("-Wa,-G0",), (second, first)
        )

    def test_command_uses_complete_unit_and_exact_object_flags(self) -> None:
        self.assertEqual(
            reverify_ledger.command(self.proof()),
            [
                sys.executable,
                "tools/match.py",
                "a",
                "--source",
                "src/game/unit.c",
                "--profile",
                "p",
                "--range-start",
                "0x00001000",
                "--range-end",
                "0x00001010",
                "--quiet",
                "--object-flag=-Wa,-G0",
            ],
        )

    def test_source_change_invalidates_proof_id(self) -> None:
        before = reverify_ledger.proof_id(self.proof(), "dependencies")
        (self.root / "src/game/unit.c").write_text("void a(void) { int changed; }\n")
        after = reverify_ledger.proof_id(self.proof(), "dependencies")
        self.assertNotEqual(before, after)

    @patch("reverify_ledger.subprocess.run")
    def test_match_with_dangerous_warning_is_unsafe(self, run: object) -> None:
        run.return_value = subprocess.CompletedProcess(
            [], 0, "p: MATCH\n", "warning: implicit declaration of function 'callee'\n"
        )
        proof = self.proof()
        record = reverify_ledger.run_proof(
            proof, reverify_ledger.proof_id(proof, "dependencies"), "dependencies", 1000
        )
        self.assertEqual(record["status"], "unsafe")
        self.assertEqual(record["dangerous_diagnostics"], ["implicit function declaration"])

    @patch("reverify_ledger.subprocess.run")
    def test_nonmatching_profile_is_failure(self, run: object) -> None:
        run.return_value = subprocess.CompletedProcess([], 1, "p: MISMATCH\n", "")
        proof = self.proof()
        record = reverify_ledger.run_proof(
            proof, reverify_ledger.proof_id(proof, "dependencies"), "dependencies", 1000
        )
        self.assertEqual(record["status"], "fail")

    @patch("reverify_ledger.subprocess.run")
    def test_source_changed_during_compile_is_stale(self, run: object) -> None:
        identifier = reverify_ledger.proof_id(self.proof(), "dependencies")

        def change_source(*args: object, **kwargs: object) -> subprocess.CompletedProcess[str]:
            (self.root / "src/game/unit.c").write_text("void a(void) { int changed; }\n")
            return subprocess.CompletedProcess([], 0, "p: MATCH\n", "")

        run.side_effect = change_source
        record = reverify_ledger.run_proof(
            self.proof(), identifier, "dependencies", 1000
        )
        self.assertEqual(record["status"], "stale")
        self.assertFalse(record["source_stable_during_proof"])

    def test_resume_repairs_only_a_torn_final_record(self) -> None:
        report = self.root / "proofs.jsonl"
        complete = {"proof_id": "good", "status": "pass"}
        encoded = json.dumps(complete) + "\n"
        report.write_bytes(encoded.encode() + b'{"proof_id":"torn"')
        records = reverify_ledger.read_resume(report)
        self.assertEqual(records, {"good": complete})
        self.assertEqual(report.read_text(), encoded)

    def test_resume_completes_missing_final_newline(self) -> None:
        report = self.root / "proofs.jsonl"
        complete = {"proof_id": "good", "status": "pass"}
        report.write_text(json.dumps(complete))
        records = reverify_ledger.read_resume(report)
        self.assertEqual(records, {"good": complete})
        self.assertTrue(report.read_bytes().endswith(b"\n"))

    def test_sharding_is_stable_and_exclusive(self) -> None:
        proof = self.proof()
        assigned = [index for index in range(7) if reverify_ledger.shard_for(proof, 7) == index]
        self.assertEqual(len(assigned), 1)
        self.assertEqual(assigned, [reverify_ledger.shard_for(proof, 7)])

    def test_resume_pass_must_contain_machine_proof_fields(self) -> None:
        proof = self.proof()
        identifier = reverify_ledger.proof_id(proof, "dependencies")
        record = {
            "schema": reverify_ledger.SCHEMA,
            "type": "proof",
            "proof_id": identifier,
            "dependency_fingerprint": "dependencies",
            "unit": proof.unit_identity(),
            "command": reverify_ledger.command(proof),
            "status": "pass",
            "returncode": 0,
            "dangerous_diagnostics": [],
            "source_stable_during_proof": True,
        }
        self.assertTrue(
            reverify_ledger.resume_record_valid(
                record, proof, identifier, "dependencies"
            )
        )
        del record["command"]
        self.assertFalse(
            reverify_ledger.resume_record_valid(
                record, proof, identifier, "dependencies"
            )
        )


if __name__ == "__main__":
    unittest.main()
