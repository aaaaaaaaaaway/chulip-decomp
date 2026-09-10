from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import candidate_queue


class AssemblyRankingTests(unittest.TestCase):
    def test_retail_short_loop_diagnostic_requires_full_padded_backward_window(self):
        def listing(operations):
            return '\n'.join(f'/* {i * 4:X} {0x1000 + i * 4:08X} 00000000 */ {op}'
                             for i, op in enumerate(operations))
        padded = listing(['sw $zero,0($v0)', 'addiu $a0,$a0,-1', 'nop', 'nop',
                          'bgez $a0,.L00001000', 'addiu $v0,$v0,-4'])
        entry = {'name': 'func_a', 'address': '0x1000', 'size': 24}
        result = candidate_queue.features(entry, padded)
        self.assertEqual(result['padded_six_instruction_loops'], 1)
        self.assertFalse(result['handwritten'])
        unpadded = listing(['sw $zero,0($v0)', 'addiu $a0,$a0,-1', 'addu $v1,$a0,$v0',
                            'sw $v1,4($v0)', 'bgez $a0,.L00001000', 'nop'])
        self.assertEqual(candidate_queue.padded_six_instruction_loops(unpadded), 0)
        self.assertGreater(result['score'], candidate_queue.features(entry, unpadded)['score'])
        self.assertEqual(candidate_queue.padded_six_instruction_loops(
            padded.replace('.L00001000', '.L00001020')), 0)
        self.assertEqual(candidate_queue.padded_six_instruction_loops(
            '\n'.join(padded.splitlines()[1:])), 0)
        seven = listing(['sw $zero,0($v0)', 'addiu $a0,$a0,-1', 'nop', 'nop', 'nop',
                         'bgez $a0,.L00001000', 'addiu $v0,$v0,-4'])
        self.assertEqual(candidate_queue.padded_six_instruction_loops(seven), 0)
        for first in ['jr $ra', 'beqz $s0,.L00001080']:
            exit_window = listing([first, 'nop', 'lw $v0,0($s0)', 'nop',
                                   'bnez $v0,.L00001000', 'addiu $v1,$v1,1'])
            self.assertEqual(candidate_queue.padded_six_instruction_loops(exit_window), 0)

    def test_hardware_control_is_visible_and_deprioritized_without_reclassification(self):
        entry = {'name': 'func_a', 'address': '0x1000', 'size': 484}
        ordinary = candidate_queue.features(entry, 'sd $2, 0($4)\njr $31\nnop')
        hardware = candidate_queue.features(entry, 'sd $2, 0($4)\nsync\njr $31\nnop')
        self.assertEqual(hardware['hardware_ops'], 1)
        self.assertGreater(hardware['score'], ordinary['score'])
        self.assertFalse(hardware['handwritten'])

    def test_numeric_return_is_not_a_switch_and_zero_branches_are_counted(self):
        entry = {'name': 'func_a', 'address': '0x1000', 'size': 16}
        features = candidate_queue.features(
            entry, 'beqz $2, .Lexit\nbnezl $3, .Lloop\njr $31\nnop')
        self.assertEqual(features['branches'], 2)
        self.assertFalse(features['jump_table'])
        switch = candidate_queue.features(entry, 'jr $2\nnop')
        self.assertTrue(switch['jump_table'])

    def test_stale_matching_fragment_cannot_hide_calls_or_ee_operations(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            full = root / 'asm/cod/text.s'
            fragment = root / 'asm/matchings/old_unit/func_a.s'
            full.parent.mkdir(parents=True)
            fragment.parent.mkdir(parents=True)
            full.write_text('glabel func_a\n  sltiu $v0, $a2, 16\n'
                            '  pcpyld $t1, $t0, $t0\n  jal func_b\n'
                            '  bnez $v0, .Lloop\nendlabel func_a\n')
            fragment.write_text('glabel func_a\n  sltiu $2, $6, 16\n'
                                'endlabel func_a\n')
            with patch.object(candidate_queue, 'ROOT', root):
                assembly = candidate_queue.assembly_functions()['func_a']
            features = candidate_queue.features(
                {'name': 'func_a', 'address': '0x1000', 'size': 16}, assembly)
            self.assertEqual(features['calls'], 1)
            self.assertEqual(features['ee_ops'], 1)
            self.assertEqual(features['branches'], 1)


if __name__ == '__main__':
    unittest.main()
