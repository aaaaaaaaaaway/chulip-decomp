import json
import hashlib
import sys
import tarfile
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

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
        self.assertTrue(runtime["libc6_i386_archive_url"].startswith("https://"))
        self.assertTrue(runtime["linux32_loader_sha256"])
        self.assertTrue(runtime["linux32_libc_sha256"])

    def test_installed_artifact_must_equal_pinned_archive(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            target = root / "tools/compilers/example"
            installed = target / "bin/compiler"
            installed.parent.mkdir(parents=True)
            installed.write_bytes(b"pinned compiler")
            archive = root / "tools/compilers/downloads/example.tar.gz"
            archive.parent.mkdir(parents=True)
            with tarfile.open(archive, "w:gz") as bundle:
                bundle.add(installed, arcname="bin/compiler")
            spec = {
                "sha256": hashlib.sha256(archive.read_bytes()).hexdigest(),
                "target": target,
                "required": {installed},
            }
            old_root = bootstrap.ROOT
            bootstrap.ROOT = root
            try:
                bootstrap.verify_archive_install(archive, spec)
                installed.write_bytes(b"modified compiler")
                with self.assertRaisesRegex(SystemExit, "differs from pinned archive"):
                    bootstrap.verify_archive_install(archive, spec)
            finally:
                bootstrap.ROOT = old_root

    @patch("bootstrap.shutil.which", return_value=None)
    def test_missing_host_tools_are_fatal(self, _which):
        with self.assertRaisesRegex(SystemExit, "missing host tools"):
            bootstrap.check_host_tools()


if __name__ == "__main__":
    unittest.main()
