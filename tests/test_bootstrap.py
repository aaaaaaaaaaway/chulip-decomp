import json
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import bootstrap


class BootstrapCoverageTest(unittest.TestCase):
    def test_every_profile_tool_is_covered_by_an_archive(self):
        config = json.loads((ROOT / "config/toolchains.json").read_text())
        specs = bootstrap.archive_specs(config)
        required = {path for spec in specs.values() for path in spec["required"]}
        for name, profile in config["profiles"].items():
            compiler = ROOT / profile["compiler"]
            self.assertIn(compiler, required, name)
            self.assertTrue(profile.get("archive_url"), name)
            self.assertTrue(profile.get("archive_sha256"), name)
            if "assembler" in profile:
                assembler = ROOT / profile["assembler"]
                self.assertIn(assembler, required, name)

    def test_linux32_runtime_is_fully_pinned(self):
        runtime = bootstrap.configuration()["runtime"]
        self.assertEqual(
            set(key for key in runtime if key.startswith("libc6_i386_")),
            {
                "libc6_i386_archive",
                "libc6_i386_archive_url",
                "libc6_i386_archive_sha256",
            },
        )


if __name__ == "__main__":
    unittest.main()
