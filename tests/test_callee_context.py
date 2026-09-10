from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import callee_context


class CalleeContextTests(unittest.TestCase):
    def test_missing_float_argument_is_flagged_from_matched_definition(self):
        known = callee_context.signatures(
            "void func_0015E138(int id, float first, float second) { }", "{")
        draft = callee_context.signatures(
            "extern void func_0015E138(int id, float scale);\n"
            "void caller(void) { func_0015E138(1, 0.5f); }", ";")
        rows = callee_context.conflicts(draft, known)
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]["reason"], "parameter count")
        self.assertEqual(rows[0]["matched_shape"], ("other", "float", "float"))

    def test_explicit_void_differs_from_unspecified_and_variadic_arguments(self):
        draft = callee_context.signatures(
            "extern void func_00100000();\n"
            "extern void func_00100010(void);\n"
            "extern void func_00100020(int first, ...);", ";")
        self.assertEqual(draft, {"func_00100010": ()})

    def test_float_pointers_and_callback_commas_do_not_create_float_arguments(self):
        shape = callee_context.parameter_shape(
            "void (*callback)(int, int), float *vector, float value")
        self.assertEqual(shape, ("pointer", "pointer", "float"))
        rows = callee_context.conflicts(
            {"func_00100000": shape},
            {"func_00100000": ("pointer", "float", "pointer")})
        self.assertEqual(rows[0]["reason"], "floating-point argument positions")

    def test_comments_strings_and_returned_calls_are_not_declarations(self):
        source = ('/* void func_00100000(int fake); */\n'
                  'const char *message = "void func_00100010(float fake);";\n'
                  'int caller(void) { return func_00100020(1); }')
        self.assertEqual(callee_context.signatures(source, ";"), {})

    def test_recursive_call_in_condition_cannot_replace_function_definition(self):
        source = ("int func_00100000(int index) {\n"
                  " if (func_00100000(index - 1)) { return 1; }\n"
                  " return 0;\n}\n"
                  "void func_00100010(float value) { }\n")
        self.assertEqual(callee_context.signatures(source, "{"),
                         {"func_00100000": ("other",), "func_00100010": ("float",)})


if __name__ == "__main__":
    unittest.main()
