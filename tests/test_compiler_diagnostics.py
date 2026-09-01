#!/usr/bin/env python3

import sys
import unittest
from contextlib import redirect_stderr
from io import StringIO
from pathlib import Path
from subprocess import CompletedProcess
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))

from compiler_diagnostics import dangerous_diagnostics
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
