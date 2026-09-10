"""Exercise small-data ownership through locally authored MIPS ELF links.

No retail instructions/data or historical compilers are required. Real-link
cases skip when GNU MIPS binutils are unavailable, as on Python-only public CI.
"""
from __future__ import annotations
import json
from pathlib import Path
import struct
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

# The parent search also allows this review copy to run before moving to tests/.
REPO = next(parent for parent in Path(__file__).resolve().parents if (parent / "tools/build.py").is_file())
sys.path.insert(0, str(REPO / "tools"))
import build as builder
import data_ownership as helper

MIPS_TOOLS = (
    "mipsel-linux-gnu-as", "mipsel-linux-gnu-ld", "mipsel-linux-gnu-nm",
    "mipsel-linux-gnu-readelf", "mipsel-linux-gnu-objcopy",
)

@unittest.skipUnless(all(shutil.which(tool) for tool in MIPS_TOOLS), "GNU MIPS binutils are not installed")
class LinkBoundary(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix="ownership-link-")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        for path in ["config", "src/game", "build/src/game", "asm/data", "build/asm/data", "build/current"]:
            (self.root / path).mkdir(parents=True, exist_ok=True)
        self.claims = [
            dict(symbol="D_00100018", source="src/game/owner.c", section="sdata", address="0x00100018", size=4),
            dict(symbol="D_0010001C", source="src/game/owner.c", section="sdata", address="0x0010001C", size=4),
            dict(symbol="D_001ED088", source="src/game/owner.c", section="sbss", address="0x001ED088", size=4),
            dict(symbol="D_001ED08C", source="src/game/owner.c", section="sbss", address="0x001ED08C", size=4),
        ]
        self.save_claims()
        self.metadata = {
            "load_segment": {"vram": "0x100000", "file_offset": "0x1000", "file_size": "0x28", "memory_size": "0xED0A8"},
            "sections": [
                {"name": ".sdata", "vram": "0x100008", "size": "0x20"},
                {"name": ".sbss", "vram": "0x1ED080", "size": "0x20"},
                {"name": ".bss", "vram": "0x1ED0A0", "size": "0x8"},
            ],
        }
        (self.root / "config/elf.json").write_text(json.dumps(self.metadata))
        (self.root / "config/splat.us.yaml").write_text("""segments:
  - start: 0
    vram: 0x100000
    subsegments:
      - [0x8]
      - [0x10, sdata, sdata_before]
      - [0x18]
      - [0x20, sdata, sdata_after]
      - {vram: 0x1ED080, type: sbss, name: sbss_before}
      - {vram: 0x1ED088, type: .sbss, name: game/owner}
      - {vram: 0x1ED090, type: sbss, name: sbss_after}
""")
        (self.root / "src/game/owner.c").write_text("unsigned int D_00100018 = 0x11223344, D_0010001C = 0x55667788;\nunsigned int D_001ED088, D_001ED08C;\nvoid _start(void) {}\n")
        (self.root / "src/game/camera.c").write_text("unsigned int camera_first = 0xCA000001, camera_second = 0xCA000002;\n")
        self.owner = self.assemble("src/game/owner", '.text\n.globl _start\n_start:\n.word 0\n' + self.data("sdata", ["D_00100018", "D_0010001C"], [0x11223344, 0x55667788]) + self.data("sbss", ["D_001ED088", "D_001ED08C"], [0, 0]) + ".bss\n.balign 8\n.space 8\n")
        self.camera = self.assemble("src/game/camera", self.data("sdata", ["camera_first", "camera_second"], [0xCA000001, 0xCA000002]))
        self.fragments = []
        for name, family, values in [("sdata_before", "sdata", [0xB0000001, 0xB0000002]), ("sdata_after", "sdata", [0xA0000001, 0xA0000002]), ("sbss_before", "sbss", [0, 0]), ("sbss_after", "sbss", [0, 0, 0, 0])]:
            self.fragments.append(self.assemble(f"asm/data/{name}.{family}", self.data(family, [f"{name}_{i}" for i in range(len(values))], values)))
        self.objects = [self.owner, self.camera] + self.fragments
        self.script = """SECTIONS
{
    __romPos = 0;
    cod_ROM_START = __romPos;
    cod_VRAM = ADDR(.cod);
    .cod 0x00100000 : AT(cod_ROM_START) SUBALIGN(8)
    {
        build/src/game/owner.o(.text*);
        build/src/game/camera.o(.text*);
        . = ALIGN(8);
        cod_SDATA_START = .;
        build/src/game/camera.o(.sdata*);
        build/src/game/owner.o(.sdata*);
        build/asm/data/sdata_before.sdata.o(.sdata*);
        build/asm/data/sdata_after.sdata.o(.sdata*);
        cod_SDATA_END = .;
        cod_SDATA_SIZE = ABSOLUTE(cod_SDATA_END - cod_SDATA_START);
    }
    cod_bss_VRAM = ADDR(.cod_bss);
    .cod_bss (NOLOAD) : SUBALIGN(8)
    {
        cod_SBSS_START = .;
        build/src/game/owner.o(.sbss COMMON .scommon);
        build/asm/data/sbss_before.sbss.o(.sbss COMMON .scommon);
        build/asm/data/sbss_after.sbss.o(.sbss COMMON .scommon);
        cod_SBSS_END = .;
        cod_SBSS_SIZE = ABSOLUTE(cod_SBSS_END - cod_SBSS_START);
        cod_BSS_START = .;
        build/src/game/owner.o(.bss COMMON .scommon);
        cod_BSS_END = .;
        cod_BSS_SIZE = ABSOLUTE(cod_BSS_END - cod_BSS_START);
    }
    __romPos += SIZEOF(.cod);
    __romPos = ALIGN(__romPos, 16);
    cod_ROM_END = __romPos;
    cod_VRAM_END = .;
    /DISCARD/ : { *(.reginfo .MIPS.abiflags .pdr .mdebug* .comment .data .bss) }
}
"""
        self.expected_payload = struct.pack("<10I", 0, 0, 0xCA000001, 0xCA000002, 0xB0000001, 0xB0000002, 0x11223344, 0x55667788, 0xA0000001, 0xA0000002)
        self.link_calls = 0

    def save_claims(self):
        (self.root / "config/data_ownership.json").write_text(json.dumps({"schema": 1, "owned": self.claims}))

    @staticmethod
    def data(family, names, values):
        kind = "nobits" if family == "sbss" else "progbits"
        text = f'.section .{family},"aw",@{kind}\n.balign 8\n'
        for name, value in zip(names, values):
            text += f'.globl {name}\n.type {name},@object\n{name}:\n'
            text += '.space 4\n' if family == "sbss" else f'.word 0x{value:08X}\n'
            text += f'.size {name},4\n'
        return text

    def assemble(self, relative, text):
        obj = self.root / "build" / (relative + ".o")
        obj.parent.mkdir(parents=True, exist_ok=True)
        asm = obj.with_suffix(".s")
        asm.write_text(text)
        subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r5900", "-mabi=eabi", "-no-pad-sections", "-o", str(obj), str(asm)], check=True, capture_output=True)
        if relative.startswith("asm/"):
            (self.root / (relative + ".s")).write_text(text)
        return obj

    def link(self, script):
        self.link_calls += 1
        output = self.root / "build/current"
        linker = output / "consumed.ld"
        linker.write_text(script)
        elf = output / "fixture.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "-EL", "-m", "elf32ltsmip", "-e", "_start", "-T", str(linker), "-o", str(elf)], cwd=self.root, check=True, capture_output=True)
        return elf

    def assert_layout(self, elf):
        nm = subprocess.check_output(["mipsel-linux-gnu-nm", "-n", str(elf)], text=True)
        addresses = {line.split()[2]: int(line.split()[0], 16) for line in nm.splitlines() if len(line.split()) == 3}
        for claim in self.claims:
            self.assertEqual(addresses[claim["symbol"]], int(claim["address"], 0))
        self.assertEqual(addresses["camera_first"], 0x100008)
        self.assertEqual(addresses["camera_second"], 0x10000C)
        self.assertEqual(addresses["cod_SBSS_START"], 0x1ED080)
        self.assertEqual(addresses["cod_SBSS_END"], 0x1ED0A0)
        self.assertEqual(addresses["cod_bss_VRAM"], 0x1ED080)
        self.assertEqual(addresses["cod_BSS_START"], 0x1ED0A0)
        self.assertEqual(addresses["cod_BSS_END"], 0x1ED0A8)
        self.assertEqual(addresses["__romPos"], 0x30)
        self.assertEqual(addresses["cod_ROM_END"], 0x30)
        # The file image alone cannot detect an inflated zero-fill segment.
        blob = elf.read_bytes()
        header = struct.unpack_from("<16sHHIIIIIHHHHHH", blob)
        program_headers = [
            struct.unpack_from("<IIIIIIII", blob, header[5] + index * header[9])
            for index in range(header[10])
        ]
        loads = [item for item in program_headers if item[0] == 1]
        self.assertEqual(len(loads), 1)
        self.assertEqual((loads[0][2], loads[0][4], loads[0][5]), (0x100000, 0x28, 0xED0A8))
        binary = elf.with_suffix(".cod.bin")
        subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".cod", "-j", ".cod_sdata", str(elf), str(binary)], check=True)
        self.assertEqual(binary.read_bytes(), self.expected_payload)
        sections = subprocess.check_output(["mipsel-linux-gnu-readelf", "-SW", str(elf)], text=True)
        self.assertRegex(sections, r"\.cod_sbss\s+NOBITS\s+001ed080")

    def split_script(self, script):
        script = script.replace(".cod_bss (NOLOAD) :", ".cod_bss 0x001ED080 (NOLOAD) :")
        script = builder.extend_bss_to_memory_end(script, 0x1ED0A8)
        return builder.split_small_data_outputs(script, self.metadata)

    def test_owned_middle_blocks_reach_real_link(self):
        result = helper.rewrite_linker(self.split_script(self.script), self.objects, root=self.root)
        self.assert_layout(self.link(result))

    def test_omitted_trailing_fragments_are_required_and_restored(self):
        script = "\n".join(line for line in self.script.split("\n") if "sdata_after" not in line and "sbss_after" not in line)
        required = helper.required_fragment_objects(root=self.root)
        self.assertEqual(set(required), set(self.fragments))
        self.assert_layout(self.link(helper.rewrite_linker(self.split_script(script), self.objects, root=self.root)))

    def test_empty_claims_leave_camera_and_script_identical(self):
        self.claims = []
        self.save_claims()
        # Even missing unrelated objects must not trigger ownership validation.
        self.assertEqual(helper.rewrite_linker(self.script, [], root=self.root), self.script)
        elf = self.link(self.split_script(self.script))
        nm = subprocess.check_output(["mipsel-linux-gnu-nm", "-n", str(elf)], text=True)
        self.assertRegex(nm, r"00100008 [A-Za-z] camera_first")

    def rejected_before_link(self, expected):
        with self.assertRaisesRegex(helper.OwnershipError, expected):
            result = helper.rewrite_linker(self.split_script(self.script), self.objects, root=self.root)
            self.link(result)
        self.assertEqual(self.link_calls, 0)

    def test_claim_overlap_rejected_before_link(self):
        self.claims[0]["size"] = 8
        self.save_claims()
        self.rejected_before_link("overlapping claims")

    def test_missing_symbol_claim_rejected_before_link(self):
        self.claims.pop(1)
        self.save_claims()
        self.rejected_before_link("enumerate all")

    def test_size_mismatch_rejected_before_link(self):
        self.claims[0]["size"] = 2
        self.save_claims()
        self.rejected_before_link("claimed size")

    def test_duplicate_elf_provider_rejected_before_link(self):
        duplicate = self.assemble("src/game/duplicate", self.data("sdata", ["D_00100018", "other"], [1, 2]))
        self.objects.append(duplicate)
        self.rejected_before_link("duplicate|ambiguous")

    def test_incomplete_gap_rejected_before_link(self):
        original = (self.root / "config/splat.us.yaml").read_text()
        (self.root / "config/splat.us.yaml").write_text(original.replace("[0x20, sdata", "[0x28, sdata"))
        self.rejected_before_link("exactly fill|bounds")

    def test_builder_consumes_rewritten_script_after_fresh_objects(self):
        self.assert_layout(self.run_builder())

    def test_builder_compiles_and_restores_omitted_trailing_fragments(self):
        self.script = "\n".join(
            line for line in self.script.split("\n")
            if "sdata_after" not in line and "sbss_after" not in line
        )
        self.assert_layout(self.run_builder())

    def test_builder_preserves_native_four_byte_owner_alignment(self):
        # Shift both owner sections four bytes earlier. Their ELF alignment is
        # four; the original combined SUBALIGN(8) outputs misplaced these.
        replacements = {
            "D_00100018": "D_00100014", "D_0010001C": "D_00100018",
            "D_001ED088": "D_001ED084", "D_001ED08C": "D_001ED088",
        }
        for claim in self.claims:
            claim["symbol"] = replacements[claim["symbol"]]
            claim["address"] = hex(int(claim["symbol"][2:], 16))
        self.save_claims()
        original = (self.root / "config/splat.us.yaml").read_text()
        original = original.replace("[0x18]", "[0x14]").replace("[0x20, sdata", "[0x1C, sdata")
        original = original.replace("{vram: 0x1ED088, type: .sbss, name: game/owner}", "{vram: 0x1ED084, type: .sbss, name: game/owner}")
        original = original.replace("{vram: 0x1ED090, type", "{vram: 0x1ED08C, type")
        (self.root / "config/splat.us.yaml").write_text(original)
        owner_text = '.text\n.globl _start\n_start:\n.word 0\n'
        owner_text += self.data("sdata", ["D_00100014", "D_00100018"], [0x11223344, 0x55667788])
        owner_text += self.data("sbss", ["D_001ED084", "D_001ED088"], [0, 0])
        owner_text = owner_text.replace(".balign 8", ".balign 4")
        self.assemble("src/game/owner", owner_text + ".bss\n.balign 8\n.space 8\n")
        (self.root / "src/game/owner.c").write_text(
            "unsigned int D_00100014 = 0x11223344, D_00100018 = 0x55667788;\n"
            "unsigned int D_001ED084, D_001ED088;\nvoid _start(void) {}\n"
        )
        for name, family, values in [
            ("sdata_before", "sdata", [0xB0000001]),
            ("sdata_after", "sdata", [0xA0000001, 0xA0000002, 0xA0000003]),
            ("sbss_before", "sbss", [0]),
            ("sbss_after", "sbss", [0, 0, 0, 0, 0]),
        ]:
            source = self.data(family, [f"{name}_{i}" for i in range(len(values))], values)
            self.assemble(f"asm/data/{name}.{family}", source.replace(".balign 8", ".balign 4"))
        self.expected_payload = struct.pack(
            "<10I", 0, 0, 0xCA000001, 0xCA000002, 0xB0000001,
            0x11223344, 0x55667788, 0xA0000001, 0xA0000002, 0xA0000003,
        )
        self.assert_layout(self.run_builder())

    def test_builder_rejects_missing_claim_before_invoking_linker(self):
        self.claims.pop(1)
        self.save_claims()
        self.run_builder(expected_error="enumerate all")

    def run_builder(self, expected_error=None):
        # A stale output file must not be the source of correct placement.
        (self.root / "build/chulip.us.ld").write_text(self.script)
        (self.root / "build/current/chulip.us.ld").write_text("STALE OUTPUT MUST BE REPLACED\n")
        for name in ["config/linker_aliases.ld", "build/undefined_funcs_auto.txt", "build/undefined_syms_auto.txt"]:
            (self.root / name).write_text("")
        records = [{"function": "_start", "source": "src/game/owner.c", "build_profile": "fixture"}, {"function": "camera", "source": "src/game/camera.c", "build_profile": "fixture"}]
        (self.root / "config/reconstructed.json").write_text(json.dumps(records))
        (self.root / "config/functions.json").write_text(json.dumps({"functions": [{"name": "_start", "address": "0x100000", "size": 4}, {"name": "camera", "address": "0x100004", "size": 0}]}))
        (self.root / "config/toolchains.json").write_text(json.dumps({"profiles": {"fixture": {}}}))
        class Linked(Exception): pass
        linked_path = None
        original_rewrite = helper.rewrite_linker
        original_required = helper.required_fragment_objects
        compiled = set()
        def rooted_rewrite(*args, **kwargs):
            kwargs["root"] = self.root
            self.assertTrue(set(kwargs.get("objects", args[1] if len(args) > 1 else [])).issubset(compiled), "ownership was validated before fresh objects")
            return original_rewrite(*args, **kwargs)
        def rooted_required(*_args, **_kwargs):
            return original_required(root=self.root)
        def compile_fixture(source, *_args):
            result = self.root / "build" / Path(source).with_suffix(".o")
            compiled.add(result)
            return result
        def assemble_fixture(source):
            result = self.root / "build/asm" / source.relative_to(self.root / "asm").with_suffix(".o")
            compiled.add(result)
            return result
        def run_at_link(command):
            nonlocal linked_path
            self.assertEqual(str(command[0]), "mipsel-linux-gnu-ld")
            self.link_calls += 1
            subprocess.run(command, cwd=self.root, check=True, capture_output=True)
            linked_path = Path(command[command.index("-o") + 1])
            raise Linked()
        def derived(_objects, _inputs, output): output.write_text("")
        # Root adaptation is for isolated fixture paths, not a replacement for
        # rewrite itself. No patch invokes rewrite on behalf of the builder.
        patches = [mock.patch.object(builder, "ROOT", self.root), mock.patch.object(builder, "run", run_at_link), mock.patch.object(builder, "compile_source", compile_fixture), mock.patch.object(builder, "assemble_source", assemble_fixture), mock.patch.object(builder, "source_owned_section_origin", lambda *_args: (None, [])), mock.patch.object(builder, "has_rodata", lambda *_args: False), mock.patch.object(builder, "derived_symbols", derived), mock.patch.object(helper, "rewrite_linker", rooted_rewrite), mock.patch.object(helper, "required_fragment_objects", rooted_required), mock.patch.object(sys, "argv", ["build.py", "--jobs", "1"])]
        if hasattr(builder, "rewrite_linker"):
            patches.append(mock.patch.object(builder, "rewrite_linker", rooted_rewrite))
        if hasattr(builder, "required_fragment_objects"):
            patches.append(mock.patch.object(builder, "required_fragment_objects", rooted_required))
        from contextlib import ExitStack
        with ExitStack() as stack:
            for patch in patches: stack.enter_context(patch)
            if expected_error:
                with self.assertRaises((helper.OwnershipError, SystemExit)) as raised:
                    builder.main()
                self.assertRegex(str(raised.exception), expected_error)
            else:
                with self.assertRaises(Linked): builder.main()
        self.assertEqual(self.link_calls, 0 if expected_error else 1)
        return linked_path

if __name__ == "__main__":
    unittest.main()
