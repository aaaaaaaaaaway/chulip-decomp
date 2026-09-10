"""Exact-only objdiff report accounting and invalid-ledger checks."""
import copy
import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location("objdiff_report", Path(__file__).resolve().parents[1] / "tools/objdiff_report.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class ReportTests(unittest.TestCase):
    def setUp(self):
        self.catalog = {"text_start": "0x1000", "text_end": "0x1100", "functions": [
            {"name": "a", "address": "0x1000", "size": 16, "handwritten": False},
            {"name": "b", "address": "0x1020", "size": 32, "handwritten": True},
            {"name": "c", "address": "0x1040", "size": 8, "handwritten": False},
        ]}
        # Shared source path deliberately models co-compiled ledger members.
        self.ledger = [{"function": f["name"], "address": f["address"], "size": f["size"], "source": "src/shared.c"}
                       for f in self.catalog["functions"] if f["name"] != "b"]
        self.reconstructed = [dict(f, isolated_match=True, whole_program_match=True) for f in self.ledger]
        self.reconstructed.append({"function": "b", "isolated_match": True, "whole_program_match": False})

    def test_all_functions_and_only_dual_verified_credit(self):
        r = module.build_report(self.catalog, self.ledger, self.reconstructed)
        m = r["measures"]
        self.assertEqual((m["total_functions"], m["total_code"], m["matched_functions"], m["matched_code"]), (3, "56", 2, "24"))
        self.assertEqual([u["functions"][0]["fuzzy_match_percent"] for u in r["units"]], [100.0, 0.0, 100.0])
        self.assertEqual(r["categories"][1]["measures"]["total_code"], "32")
        self.assertEqual(len(r["units"]), 3)
        self.assertEqual(r["units"][1]["functions"][0]["metadata"]["virtual_address"], "4128")
        self.assertEqual(r["units"][1]["functions"][0]["address"], "0")

    def test_invalid_ledgers_rejected(self):
        for mutate in (lambda c, l, r: l.append(copy.deepcopy(l[0])),
                       lambda c, l, r: l[0].update(size=12),
                       lambda c, l, r: r[0].update(whole_program_match=False),
                       lambda c, l, r: c["functions"][1].update(address="0x1008")):
            c, l, r = copy.deepcopy((self.catalog, self.ledger, self.reconstructed))
            mutate(c, l, r)
            with self.assertRaises(ValueError):
                module.build_report(c, l, r)


if __name__ == "__main__":
    unittest.main()
