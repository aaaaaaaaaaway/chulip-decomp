from pathlib import Path
import json
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import build


class FreshCompilationTests(unittest.TestCase):
    def test_historical_path_compiles_once_and_does_not_use_fallback(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(build, 'ROOT', Path(directory)), \
                 patch.object(build, 'compile_historical_object', return_value=True) as historical, \
                 patch.object(build, 'run_compiler') as fallback, \
                 patch.object(build, 'assemble') as assembler:
                entries = [{'function': 'func_a', 'build_profile': 'p', 'object_flags': ['-Wa,-G0']}]
                obj = build.compile_source('src/a.c', entries, {'p': {}})
                historical.assert_called_once_with({}, Path(directory) / 'src/a.c', obj, ['-Wa,-G0'])
                fallback.assert_not_called()
                assembler.assert_not_called()

    def test_missing_historical_path_uses_checked_compiler_and_assembler(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(build, 'ROOT', Path(directory)), \
                 patch.object(build, 'compile_historical_object', return_value=False), \
                 patch.object(build, 'profile_command', return_value=['cc1']) as command, \
                 patch.object(build, 'run_compiler') as compiler, \
                 patch.object(build, 'assemble') as assembler:
                obj = build.compile_source('src/a.c', [{'function': 'a', 'build_profile': 'p'}], {'p': {}})
                compiler.assert_called_once_with(['cc1'])
                generated = Path(directory) / 'build/compiled/src/a.s'
                command.assert_called_once_with({}, Path(directory) / 'src/a.c', generated)
                assembler.assert_called_once_with(generated, obj)

    def test_failed_worker_cannot_link_a_stale_object(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'config').mkdir()
            (root / 'build/src').mkdir(parents=True)
            (root / 'build/src/a.o').write_bytes(b'stale object')
            (root / 'build/chulip.us.ld').write_text('build/src/a.o(.text*)')
            (root / 'config/toolchains.json').write_text(json.dumps({'profiles': {'p': {}}}))
            (root / 'config/reconstructed.json').write_text(json.dumps([
                {'function': 'func_a', 'source': 'src/a.c', 'build_profile': 'p'}]))
            (root / 'config/functions.json').write_text(json.dumps({'functions': []}))
            (root / 'config/data_ownership.json').write_text(json.dumps({'schema': 1, 'owned': []}))
            with patch.object(build, 'ROOT', root), \
                 patch.object(sys, 'argv', ['build.py', '--jobs', '2']), \
                 patch.object(build, 'compile_source', side_effect=RuntimeError('compiler failed')), \
                 patch.object(build, 'run') as linker:
                with self.assertRaisesRegex(RuntimeError, 'compiler failed'):
                    build.main()
                linker.assert_not_called()


if __name__ == '__main__':
    unittest.main()
