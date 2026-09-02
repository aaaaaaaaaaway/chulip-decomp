from __future__ import annotations

import fcntl
import json
import os
import signal
import subprocess
import sys
import tempfile
import unittest
from contextlib import ExitStack
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import batch_verify
import campaign
import candidate_queue


class CampaignTests(unittest.TestCase):
    def environment(self, root: Path) -> ExitStack:
        stack = ExitStack()
        work = root / "work/campaign"
        stack.enter_context(
            patch.multiple(
                campaign,
                ROOT=root,
                WORK=work,
                PACKETS=work / "packets",
                CLAIMS=work / "claims",
                VERIFIED=work / "verified",
                STATE=work / "state.json",
                ATTEMPTS=work / "attempts.jsonl",
                LOCK=work / ".lock",
                PROMOTE_LOCK=work / ".promote.lock",
                CATALOG=root / "config/functions.json",
                RECONSTRUCTED=root / "config/reconstructed.json",
                MATCHED=root / "config/matched.json",
                TOOLCHAINS=root / "config/toolchains.json",
            )
        )
        stack.enter_context(patch.object(candidate_queue, "ROOT", root))
        stack.enter_context(patch.object(batch_verify, "ROOT", root))
        return stack

    def seed(self, root: Path) -> None:
        (root / "config").mkdir(parents=True)
        (root / "config/functions.json").write_text(
            json.dumps(
                {
                    "functions": [
                        {"name": "func_a", "address": "0x1000", "size": 8},
                        {"name": "func_b", "address": "0x1008", "size": 12},
                    ]
                }
            )
        )
        (root / "config/reconstructed.json").write_text("[]\n")
        (root / "config/matched.json").write_text("[]\n")
        (root / "config/toolchains.json").write_text(
            json.dumps({"profiles": {"profile-a": {}, "profile-b": {}}})
        )

    def test_promotion_lock_excludes_a_second_worker_until_released(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.seed(root)
            with self.environment(root):
                with campaign.promote_transaction_lock():
                    held = campaign.PROMOTE_LOCK.open("a+")
                    try:
                        with self.assertRaises(BlockingIOError):
                            fcntl.flock(held, fcntl.LOCK_EX | fcntl.LOCK_NB)
                    finally:
                        held.close()
                freed = campaign.PROMOTE_LOCK.open("a+")
                try:
                    fcntl.flock(freed, fcntl.LOCK_EX | fcntl.LOCK_NB)
                finally:
                    freed.close()

    def test_termination_signal_unwinds_promotion_cleanup(self):
        installed = signal.getsignal(signal.SIGTERM)
        removed: list[str] = []
        with self.assertRaises(campaign.PromotionInterrupted):
            with campaign.cleanup_on_termination():
                try:
                    os.kill(os.getpid(), signal.SIGTERM)
                    for _ in range(10000):
                        pass
                finally:
                    removed.append("candidate")
        self.assertEqual(removed, ["candidate"])
        self.assertIs(signal.getsignal(signal.SIGTERM), installed)

    def test_claims_are_owned_and_expired_claims_can_be_reclaimed(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.seed(root)
            with self.environment(root):
                claimed = campaign.acquire("func_a", "alice", 1)
                self.assertEqual(claimed["owner"], "alice")
                with self.assertRaises(SystemExit):
                    campaign.acquire("func_a", "bob", 1)
                path = campaign.claim_path("func_a")
                stale = json.loads(path.read_text())
                stale["expires_at"] = "2000-01-01T00:00:00Z"
                campaign.atomic_json(path, stale)
                reclaimed = campaign.acquire("func_a", "bob", 1)
                self.assertEqual(reclaimed["owner"], "bob")
                campaign.release("func_a", "bob")
                self.assertFalse(path.exists())

    def test_rank_excludes_reconstructed_and_active_claims(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.seed(root)
            (root / "config/reconstructed.json").write_text(
                json.dumps([{"function": "func_a"}])
            )
            with self.environment(root), patch.object(
                candidate_queue, "assembly_functions", return_value={}
            ):
                self.assertEqual(
                    [row["function"] for row in campaign.ranked_targets()], ["func_b"]
                )
                campaign.atomic_json(
                    campaign.CLAIMS / "func_b.json",
                    {
                        "function": "func_b",
                        "owner": "worker",
                        "expires_at": "2999-01-01T00:00:00Z",
                    },
                )
                self.assertEqual(campaign.ranked_targets(), [])

    def test_candidate_metadata_rejects_unsafe_destination_and_flags(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.seed(root)
            source = root / "work/campaign/packets/func_a/candidates/one.c"
            source.parent.mkdir(parents=True)
            source.write_text("void func_a(void) {}\n")
            with self.environment(root):
                spec = campaign.candidate_spec(source)
                self.assertEqual(spec["destination"], "src/game/func_a.c")
                Path(str(source) + ".json").write_text(
                    json.dumps({"destination": "../escape.c"})
                )
                with self.assertRaises(SystemExit):
                    campaign.candidate_spec(source)
                Path(str(source) + ".json").write_text(
                    json.dumps({"object_flags": ["-fno-real-code"]})
                )
                with self.assertRaises(SystemExit):
                    campaign.candidate_spec(source)

    def test_harvest_is_content_addressed_and_records_exact_profiles(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.seed(root)
            source = root / "work/campaign/packets/func_a/candidates/one.c"
            source.parent.mkdir(parents=True)
            source.write_text("void func_a(void) {}\n")
            proof = subprocess.CompletedProcess(
                ["match"], 0, "profile-a: MATCH\nverified 1 / 1 requested profiles\n", ""
            )
            with self.environment(root), patch.object(
                campaign, "audit_c_source", return_value=[]
            ), patch.object(campaign.subprocess, "run", return_value=proof) as run:
                first = campaign.verify_source(source)
                second = campaign.verify_source(source)
                self.assertEqual(first, second)
                self.assertEqual(first["matched_profiles"], ["profile-a", "profile-b"])
                self.assertEqual(run.call_count, 2)
                self.assertEqual(len(list(campaign.VERIFIED.glob("*.json"))), 1)
                source.write_text("void func_a(void) { int changed = 1; }\n")
                campaign.verify_source(source)
                self.assertEqual(run.call_count, 4)

    def test_promotion_manifest_preserves_exact_proof_inputs(self):
        record = {
            "function": "func_a",
            "matched_profiles": ["profile-b", "profile-a"],
            "spec": {
                "build_profile": "profile-b",
                "object_flags": ["-Wa,-G8"],
                "range_start": "0x1000",
                "range_end": "0x1010",
                "rodata_start": "0x2000",
            },
        }
        manifest = campaign.promotion_manifest(record, "src/game/func_a.c")
        self.assertEqual(manifest["build_profile"], "profile-b")
        self.assertEqual(manifest["verified_profiles"], ["profile-b", "profile-a"])
        self.assertEqual(manifest["unit_start"], "0x1000")
        self.assertEqual(manifest["rodata_start"], "0x2000")
        self.assertEqual(manifest["object_flags"], ["-Wa,-G8"])

    def test_ambiguous_match_requires_reviewed_build_profile(self):
        record = {
            "function": "func_a",
            "matched_profiles": ["profile-a", "profile-b"],
            "spec": {
                "build_profile": None,
                "object_flags": [],
                "range_start": None,
                "range_end": None,
            },
        }
        with self.assertRaises(SystemExit):
            campaign.promotion_manifest(record, "src/game/func_a.c")


if __name__ == "__main__":
    unittest.main()
