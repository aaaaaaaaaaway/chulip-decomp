from contextlib import ExitStack
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import batch_verify
import campaign


class RodataProofTests(unittest.TestCase):
    def test_campaign_passes_explicit_table_origin_to_match(self):
        source = batch_verify.ROOT / 'src/game/fixture.c'
        spec = dict(function='func_a', object_flags=[], range_start=None,
                    range_end=None, rodata_start='0x2000', sdata_start=None,
                    sbss_start=None)
        command = campaign.match_command(source, spec, 'fixture')
        index = command.index('--rodata-start')
        self.assertEqual(command[index + 1], '0x2000')

    def test_batch_cannot_reuse_proof_at_another_rodata_origin(self):
        with tempfile.TemporaryDirectory() as directory, ExitStack() as stack:
            root = Path(directory)
            source = root / 'fixture.c'
            source.write_text('void func_a(void) {}\n')
            catalog = root / 'functions.json'
            catalog.write_text(json.dumps({'functions': [dict(name='func_a', address='0x1000', size=4)]}))
            profiles = root / 'profiles.json'
            profiles.write_text(json.dumps({'profiles': {'fixture': {}}}))
            manifest = root / 'candidates.jsonl'
            entries = [dict(function='func_a', source='fixture.c', profiles=['fixture'],
                            range_start='0x1000', range_end='0x1004', rodata_start=origin)
                       for origin in ['0x2000', '0x3000', '0x2000']]
            manifest.write_text(''.join(json.dumps(entry) + '\n' for entry in entries))
            stack.enter_context(patch.multiple(batch_verify, ROOT=root, FUNCTIONS=catalog, TOOLCHAINS=profiles))
            stack.enter_context(patch.object(sys, 'argv', ['batch_verify.py', str(manifest)]))
            calls = []
            def replay(command, **kwargs):
                origin = command[command.index('--rodata-start') + 1]
                calls.append(origin)
                ok = origin == '0x2000'
                return subprocess.CompletedProcess(command, 0 if ok else 1,
                                                   'fixture: ' + ('MATCH' if ok else 'MISMATCH'), '')
            stack.enter_context(patch.object(batch_verify.subprocess, 'run', side_effect=replay))
            self.assertEqual(batch_verify.main(), 1)
            self.assertEqual(calls, ['0x2000', '0x3000'])


if __name__ == '__main__':
    unittest.main()
