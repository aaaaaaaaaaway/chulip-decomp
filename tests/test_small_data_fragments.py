from __future__ import annotations

import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import data_ownership as own
import small_data_fragments as small


class SmallFragmentTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="chulip-byte-frag-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for name in ("config", "original", "src/game", "asm/data/cod", "include"):
            (self.root / name).mkdir(parents=True)
        self.image = bytes.fromhex("10203040aa012345566778899aabbccd")
        (self.root / "original/SLUS_207.42.rom").write_bytes(self.image)
        (self.root / "src/game/owner.c").write_text("/* fixture provider */\n")
        self.claim = dict(symbol="D_00100004", source="src/game/owner.c", section="sdata", address="0x100004", size=1)
        self.document = {"options": {"symbol_addrs_path": ["config/symbols.txt"]}, "segments": [{"start": 0, "vram": 0x100000, "subsegments": [[0,"sdata","cod/pre"],[4],[5,"sdata","cod/tail"],[8,"sdata","cod/post"],[16,"sbss","cod/bss"],[20]]}]}
        (self.root / "config/data_ownership.json").write_text(json.dumps({"schema":1,"owned":[self.claim]}))
        (self.root / "config/elf.json").write_text(json.dumps({"load_segment":{"vram":"0x100000"},"sections":[{"name":".sdata","vram":"0x100000","size":16},{"name":".sbss","vram":"0x100010","size":4}]}))
        (self.root / "config/symbols.txt").write_text("D_00100005 = 0x100005; // type:u8 size:0x3\n")
        self.write_config()
        self.output = self.root / "asm/data/cod/tail.sdata.s"
        self.output.write_text('.section .sdata,"wa"\n/* old empty output */\n')

    def write_config(self):
        (self.root / "config/splat.us.yaml").write_text(json.dumps(self.document))

    def test_render_exact_one_two_three_bytes_and_labels(self):
        for start, data in [(0x100005,b'\x01'),(0x100006,b'\x23\x45'),(0x100005,b'\x01\x23\x45'),(0x100008,b'\x56\x67\x78')]:
            frag = own.Fragment("sdata",start,start+len(data),"build/asm/data/cod/raw.sdata.o")
            rendered = small.render(frag,data,[small.Label(f"D_{start:08X}",start,len(data),"u8")])
            self.assertEqual(rendered.count(".byte "),len(data))
            self.assertIn(".balign 1",rendered)
            self.assertIn("nonmatching ",rendered)
            self.assertNotIn(".word",rendered)

    def test_repair_preserves_interior_alias_and_ignores_aligned_fragments(self):
        (self.root / "config/symbols.txt").write_text("Tail = 0x100005; // type:u8 size:3\nInterior = 0x100006; // type:u8 size:1\n")
        pre = self.root / "asm/data/cod/pre.sdata.s"
        pre.write_text("untouched aligned fragment\n")
        self.assertEqual(small.repair(self.root,self.image),[self.output])
        content = self.output.read_text()
        self.assertIn("dlabel Tail",content)
        self.assertIn("dlabel Interior",content)
        self.assertEqual(content.count(".byte "),3)
        self.assertEqual(pre.read_text(),"untouched aligned fragment\n")
        self.assertEqual(small.repair(self.root,self.image),[self.output])
        self.assertEqual(self.output.read_text(),content)

    def test_payload_mismatch_fails_before_write(self):
        before = self.output.read_bytes()
        with self.assertRaisesRegex(small.FragmentError,"authenticated image"):
            small.repair(self.root,b'bad')
        self.assertEqual(self.output.read_bytes(),before)

    def test_active_symbol_collision_rejected(self):
        (self.root / "asm/data/cod/pre.sdata.s").write_text("dlabel D_00100005\n")
        with self.assertRaisesRegex(small.FragmentError,"another active provider"):
            small.repair(self.root,self.image)

    def test_configured_collision_and_oversized_symbol_rejected(self):
        for source,reason in [("Duplicate = 0x100005;\nDuplicate = 0x100006;\n","duplicate"),("D_00100005 = 0x100005; // size:4\n","outside fragment")]:
            (self.root / "config/symbols.txt").write_text(source)
            before = self.output.read_bytes()
            with self.assertRaisesRegex(small.FragmentError,reason):
                small.repair(self.root,self.image)
            self.assertEqual(self.output.read_bytes(),before)

    def test_disallowed_or_incomplete_fragment_rejected(self):
        for section,size in [("sbss",3),("data",3),("text",3),("sdata",4),("sdata",0)]:
            with self.assertRaises(small.FragmentError):
                small.render(own.Fragment(section,0x100005,0x100005+size,"x"),bytes(size),[small.Label("X",0x100005)])
        with self.assertRaises(small.FragmentError):
            small.render(own.Fragment("sdata",0x100005,0x100008,"x"),b'xx',[small.Label("X",0x100005)])

    def test_long_unaligned_fragment_requires_explicit_split(self):
        del self.document["segments"][0]["subsegments"][3]
        self.write_config()
        with self.assertRaisesRegex(small.FragmentError,"1..3-byte edge"):
            small.repair(self.root,self.image)

    @unittest.skipUnless(all(shutil.which("mipsel-linux-gnu-"+tool) for tool in ("as","ld","objcopy")),"MIPS binutils required")
    def test_real_assembly_and_link_preserve_owner_and_tail_without_padding(self):
        # Minimal fixture macros have the same label/size behavior as macro.inc.
        (self.root / "include/macro.inc").write_text('''.macro nonmatching name, size=1
.globl \\name\\().NON_MATCHING
.type \\name\\().NON_MATCHING,@object
.size \\name\\().NON_MATCHING,\\size
\\name\\().NON_MATCHING:
.endm
.macro dlabel name
.globl \\name
.type \\name,@object
\\name:
.endm
''')
        small.repair(self.root,self.image)
        paths=[]
        for name,data in [("pre",self.image[:4]),("owner",self.image[4:5]),("tail",None),("post",self.image[8:])]:
            asm = self.output if name=="tail" else self.root/f'{name}.s'
            if data is not None:
                asm.write_text('.section .sdata,"wa"\n.balign 1\n.byte '+','.join(str(x) for x in data)+'\n')
            obj=self.root/f'{name}.o'
            subprocess.run(["mipsel-linux-gnu-as","-EL","-march=r5900","-mabi=eabi","-no-pad-sections","-I",str(self.root/"include"),"-o",str(obj),str(asm)],check=True,capture_output=True)
            paths.append(obj)
        info=own.read_object(paths[2]);sec=next(s for s in info.sections if s.name==".sdata")
        self.assertEqual((sec.size,sec.alignment),(3,1))
        self.assertTrue(any(s.name=="D_00100005.NON_MATCHING" for s in info.symbols))
        script=self.root/"link.ld";script.write_text('SECTIONS { .sdata 0x100000 : { '+ ' '.join(str(p)+'(.sdata)' for p in paths)+' } /DISCARD/ : { *(.text) *(.data) *(.bss) *(.reginfo) *(.MIPS.abiflags) } }')
        elf=self.root/'linked.elf';binary=self.root/'linked.bin'
        subprocess.run(["mipsel-linux-gnu-ld","-EL","-T",str(script),"-o",str(elf),*[str(p) for p in paths]],check=True,capture_output=True)
        subprocess.run(["mipsel-linux-gnu-objcopy","-O","binary","-j",".sdata",str(elf),str(binary)],check=True,capture_output=True)
        self.assertEqual(binary.read_bytes(),self.image)


if __name__ == "__main__":
    unittest.main()
