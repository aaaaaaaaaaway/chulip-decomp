#!/usr/bin/env python3

import sys
import unittest
from contextlib import redirect_stderr
from io import StringIO
from pathlib import Path
from subprocess import CompletedProcess
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from compiler_diagnostics import dangerous_diagnostics, unexpected_diagnostics
import match


class CompilerDiagnosticsTests(unittest.TestCase):
    def test_accepts_benign_warning(self) -> None:
        self.assertEqual(
            dangerous_diagnostics("warning: unused variable `value'"),
            [],
        )

    def test_finds_abi_dangerous_warnings(self) -> None:
        output = "\n".join(
            (
                "warning: return type defaults to `int'",
                "warning: implicit declaration of function `load_actor'",
                "warning: passing arg 2 of `draw' from incompatible pointer type",
                "warning: return with a value, in function returning void",
                "warning: `return' with a value, in function returning void",
                "warning: control reaches end of non-void function",
            )
        )
        self.assertEqual(
            dangerous_diagnostics(output),
            [
                "implicit int return type",
                "implicit function declaration",
                "incompatible argument type",
                "value returned from void function",
                "non-void function falls through",
            ],
        )

    def test_reports_each_reason_only_once(self) -> None:
        output = "\n".join(
            (
                "warning: assignment makes pointer from integer without a cast",
                "warning: assignment makes pointer from integer without a cast",
            )
        )
        self.assertEqual(
            dangerous_diagnostics(output),
            ["integer converted to pointer", "pointer/integer assignment"],
        )

    def test_benign_compiler_warnings_are_classified(self) -> None:
        output = "\n".join(
            (
                "f.c:1: warning: unused variable `value'",
                "f.c:2: warning: `helper' defined but not used",
                "f.c:3: warning: statement with no effect",
                "f.c:4: warning: `x' might be used uninitialized in this function",
            )
        )
        self.assertEqual(unexpected_diagnostics(output), [])

    def test_assembler_and_linker_lines_are_not_c_diagnostics(self) -> None:
        output = "\n".join(
            (
                "/usr/bin/mipsel-linux-gnu-ld.bfd: warning: missing LOAD segment",
                "Warning: Setting incorrect section type for .sbss",
                "ee-gcc2.95.3-136-O2: MATCH",
            )
        )
        self.assertEqual(unexpected_diagnostics(output), [])

    def test_unclassified_compiler_warning_is_reported_once(self) -> None:
        output = "\n".join(
            (
                "f.c:9: warning: cast increases required alignment of target type",
                "g.c:2: warning: cast increases required alignment of target type",
                "f.c:1: warning: unused variable `value'",
            )
        )
        self.assertEqual(
            unexpected_diagnostics(output),
            ["cast increases required alignment of target type"],
        )

    def test_dangerous_warning_is_also_unclassified(self) -> None:
        self.assertEqual(
            unexpected_diagnostics("f.c:3: warning: implicit declaration of function `go'"),
            ["implicit declaration of function `go'"],
        )

    @patch("match.subprocess.run")
    def test_compiler_runner_rejects_dangerous_warning(self, run: object) -> None:
        run.return_value = CompletedProcess(
            ["cc1"],
            0,
            "",
            "warning: implicit declaration of function `callee'\n",
        )
        with redirect_stderr(StringIO()):
            with self.assertRaisesRegex(
                SystemExit, "ABI-DANGEROUS COMPILER DIAGNOSTICS"
            ):
                match.run_compiler(["cc1"])

    @patch("match.subprocess.run")
    def test_compiler_runner_accepts_benign_warning(self, run: object) -> None:
        run.return_value = CompletedProcess(
            ["cc1"],
            0,
            "",
            "warning: unused variable `value'\n",
        )
        with redirect_stderr(StringIO()):
            match.run_compiler(["cc1"])

    @patch("match.subprocess.run")
    def test_generic_runner_does_not_classify_linker_warning(self, run: object) -> None:
        run.return_value = CompletedProcess(["ld"], 0, "", "warning: implicit declaration")
        match.run(["ld"])
        run.assert_called_once_with(["ld"], cwd=match.ROOT, check=True)


if __name__ == "__main__":
    unittest.main()
