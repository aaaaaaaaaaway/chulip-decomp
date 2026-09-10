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

    def test_unspecified_declaration_does_not_hide_empty_forwarding_call(self):
        source = ("extern int func_00100000();\n"
                  "int wrapper(int id) { return func_00100000(/* missing id */); }")
        known = {"func_00100000": ("other",)}
        self.assertEqual(callee_context.conflicts(callee_context.signatures(source, ";"), known), [])
        rows = callee_context.empty_call_conflicts(source, known)
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]["line"], 2)
        self.assertEqual(rows[0]["matched_shape"], ("other",))

    def test_nonempty_literals_forwarded_arguments_and_unknown_arity_are_ignored(self):
        source = ('void wrapper(int id) { func_00100000(id); func_00100000("text");'
                  "func_00100000('x'); func_00100010(); func_00100020(); }")
        self.assertEqual(callee_context.empty_call_conflicts(
            source, {"func_00100000": ("pointer",), "func_00100010": ()}), [])

    def test_definitions_local_declarations_comments_and_macro_bodies_are_ignored(self):
        source = ('void func_00100000() {}\n'
                  'void wrapper(void) {\n'
                  ' extern unsigned\n int func_00100000();\n'
                  ' /* func_00100000(); */\n'
                  ' const char *s = "func_00100000()";\n'
                  '#define EXAMPLE() \\\n func_00100000()\n'
                  '}\n')
        self.assertEqual(callee_context.empty_call_conflicts(
            source, {"func_00100000": ("other",)}), [])

    def test_nested_condition_assignment_and_return_calls_preserve_line_numbers(self):
        source = ('/* multi\n line */\nvoid wrapper(void) {\n'
                  ' if (func_00100000()) {\n'
                  ' value = func_00100000();\n'
                  ' return func_00100000();\n }\n}')
        rows = callee_context.empty_call_conflicts(source, {"func_00100000": ("other",)})
        self.assertEqual([r["line"] for r in rows], [4, 5, 6])


if __name__ == "__main__":
    unittest.main()
