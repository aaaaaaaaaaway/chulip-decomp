from __future__ import annotations

import json
import struct
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import data_ownership as own


@unittest.skipUnless(all(shutil.which("mipsel-linux-gnu-" + name) for name in ("as", "ld", "nm")), "MIPS binutils required")
class OwnershipTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="chulip-own-test-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "config").mkdir()
        (self.root / "src/game").mkdir(parents=True)
        (self.root / "src/game/owner.c").write_text("/* fixture source */\n")
        self.entries = [dict(symbol="D_001EC890", source="src/game/owner.c", section="sdata", address="0x001EC890", size=4),
                        dict(symbol="D_001EC894", source="src/game/owner.c", section="sdata", address="0x001EC894", size=4)]
        self.elf = {"load_segment": {"vram": "0x00100000"}, "sections": [
            {"name": ".sdata", "vram": "0x001EC880", "size": "0x20"},
            {"name": ".sbss", "vram": "0x001ED080", "size": "0x20"}]}
        self.splat = {"segments": [{"start": 0, "vram": 0x100000, "subsegments": [
            [0xEC880, "sdata", "cod/pre"], [0xEC890], [0xEC898, "sdata", "cod/post"],
            {"vram": 0x1ED080, "type": "sbss", "name": "cod/bpre"},
            {"vram": 0x1ED090, "type": "sbss", "name": "cod/bmiddle"}, {"vram": 0x1ED098, "type": "sbss", "name": "cod/bpost"}]}]}
        self.write_config()
        self.owner = self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4), ("D_001EC894", 4)]))
        self.pre = self.assemble("build/asm/data/cod/pre.sdata.o", '.section .sdata,"aw",@progbits\n.space 16\n')
        self.post = self.assemble("build/asm/data/cod/post.sdata.o", '.section .sdata,"aw",@progbits\n.space 8\n')
        self.objects = [self.owner, self.pre, self.post]
        self.linker = '''SECTIONS {
    .cod_sdata 0x001EC880 : {
        cod_SDATA_START = .;
        build/src/game/owner.o(.sdata*);
        build/asm/data/cod/pre.sdata.o(.sdata*);
        build/asm/data/cod/post.sdata.o(.sdata*);
        cod_SDATA_END = .;
    }
    .cod_sbss 0x001ED080 (NOLOAD) : {
        cod_SBSS_START = .;
        cod_SBSS_END = .;
    }
    /DISCARD/ : { *(.text) *(.reginfo) *(.MIPS.abiflags) }
}
'''

    def write_config(self):
        (self.root / "config/data_ownership.json").write_text(json.dumps({"schema": 1, "owned": self.entries}))
        (self.root / "config/elf.json").write_text(json.dumps(self.elf))
        (self.root / "config/splat.us.yaml").write_text(json.dumps(self.splat))

    def assemble(self, relative, source):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        asm = path.with_suffix(".s")
        asm.write_text(source)
        subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r5900", "-mabi=eabi", "-no-pad-sections", "-o", str(path), str(asm)], check=True, capture_output=True)
        return path

    def defs(self, section, items, tail=0):
        source = f'.section .{section},"aw",@' + ("nobits" if section == "sbss" else "progbits") + "\n.balign 8\n"
        for name, size in items:
            source += f".globl {name}\n.type {name},@object\n.size {name},{size}\n{name}:\n.space {size or 4}\n"
        return source + f".space {tail}\n"

    def rewrite(self, objects=None, linker=None):
        return own.rewrite_linker(self.linker if linker is None else linker, self.objects if objects is None else objects, self.root)

    def test_empty_claims_preserve_script_without_objects(self):
        self.entries = []
        self.write_config()
        (self.root / "config/elf.json").unlink()
        self.assertEqual(self.rewrite(objects=[]), self.linker)
        self.assertEqual(own.check(self.root), [])

    def test_static_check_needs_no_compiled_objects(self):
        for path in self.objects: path.unlink()
        self.assertEqual(own.check(self.root), [])
        self.assertEqual(set(own.required_fragment_objects(self.root)), {self.pre, self.post})

    def test_multiple_symbols_one_contribution_real_link(self):
        rendered = self.rewrite()
        selector = "build/src/game/owner.o(.sdata*);"
        self.assertEqual(rendered.count(selector), 1)
        self.assertLess(rendered.index("pre.sdata.o(.sdata"), rendered.index(selector))
        self.assertLess(rendered.index(selector), rendered.index("post.sdata.o(.sdata"))
        script = self.root / "final.ld"
        script.write_text(rendered)
        linked = self.root / "result.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "-EL", "-T", str(script), "-o", str(linked)], cwd=self.root, check=True, capture_output=True)
        listing = subprocess.run(["mipsel-linux-gnu-nm", "-n", str(linked)], check=True, capture_output=True, text=True).stdout
        self.assertIn("001ec890 D D_001EC890", listing)
        self.assertIn("001ec894 D D_001EC894", listing)

    def test_explicit_sdata_source_contribution_real_link(self):
        self.splat["segments"][0]["subsegments"][1] = dict(start=0xEC890, type=".sdata", name="game/owner")
        self.write_config()
        self.test_multiple_symbols_one_contribution_real_link()

    def test_explicit_source_interval_rejects_multiple_claim_providers(self):
        self.splat["segments"][0]["subsegments"][1] = dict(start=0xEC890, type=".sdata", name="game/owner")
        self.entries[1]["source"] = "src/game/other.c"
        (self.root / "src/game/other.c").write_text("/* fixture */\n")
        self.write_config()
        with self.assertRaisesRegex(own.OwnershipError, "exactly that provider"):
            self.rewrite()

    def test_wrong_runtime_position_triggers_link_assertion(self):
        script = self.root / "bad.ld"
        script.write_text(self.rewrite(linker=self.linker.replace(".cod_sdata 0x001EC880", ".cod_sdata 0x001EC878")))
        result = subprocess.run(["mipsel-linux-gnu-ld", "-EL", "-T", str(script), "-o", str(self.root / "bad.elf")], cwd=self.root, capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("placement", result.stderr)

    def test_wrong_fragment_extent_fails_before_link(self):
        self.assemble("build/asm/data/cod/pre.sdata.o", '.section .sdata,"aw",@progbits\n.space 8\n')
        with self.assertRaisesRegex(own.OwnershipError, "ELF fragment extent"):
            self.rewrite()

    def test_owner_and_fragment_subsections_rejected(self):
        extra = '.section .sdata.extra,"aw",@progbits\n.space 4\n'
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4), ("D_001EC894", 4)]) + extra)
        with self.assertRaisesRegex(own.OwnershipError, "subsections"):
            self.rewrite()
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4), ("D_001EC894", 4)]))
        self.assemble("build/asm/data/cod/pre.sdata.o", '.section .sdata,"aw",@progbits\n.space 16\n' + extra)
        with self.assertRaisesRegex(own.OwnershipError, "subsections"):
            self.rewrite()

    def test_common_and_scommon_rejected(self):
        for extra in ['.comm extra_common,4,4\n', '.section .scommon,"aw",@nobits\n.space 4\n']:
            obj = self.assemble("build/common.o", self.defs("sbss", [("D_001ED090", 4), ("D_001ED094", 4)]) + extra)
            with self.assertRaisesRegex(own.OwnershipError, "COMMON/.scommon"):
                own.input_section(own.read_object(obj), "sbss", str(obj))

    def test_native_sixteen_byte_alignment_rejects_eight_mod_sixteen_origin(self):
        # Shift the claimed block to an address congruent to 8 mod 16.
        for entry, address in zip(self.entries, [0x1EC888, 0x1EC88C]):
            entry.update(symbol=f"D_{address:08X}", address=hex(address))
        self.splat["segments"][0]["subsegments"][1][0] = 0xEC888
        self.splat["segments"][0]["subsegments"][2][0] = 0xEC890
        self.write_config()
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC888", 4), ("D_001EC88C", 4)]).replace(".balign 8", ".balign 16"))
        self.assemble("build/asm/data/cod/pre.sdata.o", '.section .sdata,"aw",@progbits\n.space 8\n')
        self.assemble("build/asm/data/cod/post.sdata.o", '.section .sdata,"aw",@progbits\n.space 16\n')
        with self.assertRaisesRegex(own.OwnershipError, "origin violates section/input alignment"):
            self.rewrite()


    def test_native_sixteen_byte_alignment_at_valid_origin(self):
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4), ("D_001EC894", 4)]).replace(".balign 8", ".balign 16"))
        self.test_multiple_symbols_one_contribution_real_link()

    def test_overlapping_complete_sections_with_disjoint_claims_rejected(self):
        # Each symbol claim is disjoint, but both source sections include the
        # same complete eight-byte gap through their leading/trailing storage.
        self.entries[1]["source"] = "src/game/other.c"
        (self.root / "src/game/other.c").write_text("/* fixture */\n")
        self.write_config()
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4)], tail=4))
        assembly = self.defs("sdata", [("D_001EC894", 4)]).replace(".balign 8\n", ".balign 8\n.space 4\n")
        other = self.assemble("build/src/game/other.o", assembly)
        with self.assertRaisesRegex(own.OwnershipError, "overlapping source sections"):
            self.rewrite(objects=self.objects + [other])

    def test_small_data_subalign_override_rejected(self):
        altered = self.linker.replace(".cod_sdata 0x001EC880 :", ".cod_sdata 0x001EC880 : SUBALIGN(8)")
        with self.assertRaisesRegex(own.OwnershipError, "preserve native input alignment"):
            self.rewrite(linker=altered)

    def test_misaligned_raw_fragment_rejected_before_link(self):
        self.assemble("build/asm/data/cod/post.sdata.o", '.section .sdata,"aw",@progbits\n.balign 16\n.space 8\n')
        with self.assertRaisesRegex(own.OwnershipError, "fragment violates native ELF alignment"):
            self.rewrite()

    def test_natural_sdata_byte_halfword_word_real_link(self):
        self.natural_small_objects("sdata", 0x001EC880)

    def test_natural_sbss_byte_halfword_word_real_link(self):
        self.natural_small_objects("sbss", 0x001ED080)

    def natural_small_objects(self, family, base):
        self.entries = []
        self.objects = []
        marks = [[base - 0x100000, family, "natural/pre"]]
        names = []
        kind = "nobits" if family == "sbss" else "progbits"
        for size, directive, value in [(1, ".byte", 0x11), (2, ".short", 0x3322), (4, ".word", 0x77665544)]:
            address = base + size
            name = f"D_{address:08X}"
            names.append(name)
            source = f"src/game/owner{size}.c"
            (self.root / source).write_text("/* Locally authored alignment fixture. */\n")
            self.entries.append(dict(symbol=name, source=source, section=family, address=address, size=size))
            if family == "sbss":
                marks.append(dict(vram=address, type=".sbss", name=f"game/owner{size}"))
            else:
                marks.append([address - 0x100000])
            payload = f".space {size}" if family == "sbss" else f"{directive} {value}"
            assembly = f'.section .{family},"aw",@{kind}\n.balign {size}\n.globl {name}\n.type {name},@object\n{name}:\n{payload}\n.size {name},{size}\n'
            self.objects.append(self.assemble(f"build/src/game/owner{size}.o", assembly))
        marks.append([base + 8 - 0x100000, family, "natural/post"])
        for entry in self.elf["sections"]:
            if entry["name"] == "." + family:
                entry["size"] = 16
        self.splat["segments"][0]["subsegments"] = marks
        self.write_config()
        for name, size in [("pre", 1), ("post", 8)]:
            assembly = f'.section .{family},"aw",@{kind}\n.balign 1\n.space {size}\n'
            self.objects.append(self.assemble(f"build/asm/data/natural/{name}.{family}.o", assembly))
        marker = family.upper()
        noload = " (NOLOAD)" if family == "sbss" else ""
        selectors = "".join(f"        {obj.relative_to(self.root).as_posix()}(.{family});\n" for obj in self.objects)
        linker = f"SECTIONS {{\n    .cod_{family} 0x{base:08X}{noload} : {{\n        cod_{marker}_START = .;\n{selectors}        cod_{marker}_END = .;\n    }}\n    /DISCARD/ : {{ *(.text .data .bss .reginfo .MIPS.abiflags) }}\n}}\n"
        rendered = self.rewrite(linker=linker)
        for size in (1, 2, 4):
            self.assertIn(f"ALIGN(ABSOLUTE(.), {size}) == 0x{base + size:08X}", rendered)
        script = self.root / "natural.ld"
        script.write_text(rendered)
        linked = self.root / "natural.elf"
        subprocess.run(["mipsel-linux-gnu-ld", "-EL", "-T", str(script), "-o", str(linked)], cwd=self.root, check=True, capture_output=True)
        listing = subprocess.check_output(["mipsel-linux-gnu-nm", "-n", str(linked)], text=True)
        for size, name in zip((1, 2, 4), names):
            self.assertRegex(listing, f"{base + size:08x} [DB] {name}")
        blob = linked.read_bytes()
        header = struct.unpack_from("<16sHHIIIIIHHHHHH", blob)
        sections = [struct.unpack_from("<10I", blob, header[6] + i * header[11]) for i in range(header[12])]
        strings = sections[header[13]]
        names_blob = blob[strings[4]:strings[4] + strings[5]]
        section = next(item for item in sections if names_blob[item[0]:].split(b"\0", 1)[0] == (".cod_" + family).encode())
        self.assertEqual((section[3], section[5]), (base, 16))
        self.assertEqual(section[1], 8 if family == "sbss" else 1)
        if family == "sdata":
            self.assertEqual(blob[section[4]:section[4] + section[5]], bytes(range(0, 0x78, 0x11)) + bytes(8))

    def test_last_owned_block_has_extent_assertion(self):
        self.elf["sections"][0]["size"] = "0x18"
        del self.splat["segments"][0]["subsegments"][2]
        self.write_config()
        rendered = self.rewrite()
        self.assertIn('ASSERT(ABSOLUTE(.) == 0x001EC898, "sdata extent: build/src/game/owner.o")', rendered)

    def test_actual_dict_sbss_source_and_selector(self):
        self.splat["segments"][0]["subsegments"][4] = dict(vram=0x1ED090, type=".sbss", name="game/owner")
        self.entries = [dict(symbol="D_001ED090", source="src/game/owner.c", section="sbss", address="0x001ED090", size=4),
                        dict(symbol="D_001ED094", source="src/game/owner.c", section="sbss", address="0x001ED094", size=4)]
        self.write_config()
        self.owner = self.assemble("build/src/game/owner.o", self.defs("sbss", [("D_001ED090", 4), ("D_001ED094", 4)]))
        pre = self.assemble("build/asm/data/cod/bpre.sbss.o", '.section .sbss,"aw",@nobits\n.space 16\n')
        post = self.assemble("build/asm/data/cod/bpost.sbss.o", '.section .sbss,"aw",@nobits\n.space 8\n')
        linker = self.linker.replace("        cod_SBSS_END", "        build/src/game/owner.o(.sbss COMMON .scommon);\n        build/asm/data/cod/bpre.sbss.o(.sbss COMMON .scommon);\n        cod_SBSS_END")
        result = self.rewrite(objects=[self.owner, pre, post], linker=linker)
        self.assertIn("bpost.sbss.o(.sbss COMMON .scommon)", result)
        self.assertEqual(result.count("owner.o(.sbss COMMON .scommon)"), 1)
        self.assertEqual(own.check(self.root), [])

    def test_elf_size_must_match_claim(self):
        self.entries[0]["size"] = 2
        self.write_config()
        with self.assertRaisesRegex(own.OwnershipError, "size disagrees"):
            self.rewrite()

    def test_unclaimed_definition_rejected(self):
        self.entries.pop()
        self.write_config()
        with self.assertRaisesRegex(own.OwnershipError, "enumerate"):
            self.rewrite()

    def test_inconsistent_section_origins_rejected(self):
        self.entries[1].update(symbol="D_001EC898", address="0x001EC898")
        self.splat["segments"][0]["subsegments"][2][0] = 0xEC8A0
        self.elf["sections"][0]["size"] = "0x28"
        self.write_config()
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4), ("D_001EC898", 4)]))
        with self.assertRaisesRegex(own.OwnershipError, "inconsistent section origins"):
            self.rewrite()

    def test_complete_section_must_fit_gap(self):
        self.assemble("build/src/game/owner.o", self.defs("sdata", [("D_001EC890", 4), ("D_001EC894", 4)], tail=8))
        with self.assertRaisesRegex(own.OwnershipError, "exactly fill"):
            self.rewrite()

    def test_duplicate_actual_symbol_provider_rejected(self):
        other = self.assemble("build/other.o", self.defs("sdata", [("D_001EC890", 4)]))
        with self.assertRaisesRegex(own.OwnershipError, "providers"):
            self.rewrite(objects=self.objects + [other])

    def test_overlapping_claims_rejected_statically(self):
        self.entries[0]["size"] = 8
        self.write_config()
        self.assertIn("overlapping", own.check(self.root)[0])

    def test_outside_retained_gap_rejected_statically(self):
        self.entries[0].update(symbol="D_001EC880", address="0x001EC880")
        self.write_config()
        self.assertIn("explicit Splat gap", own.check(self.root)[0])

    def test_missing_or_duplicate_input_is_rejected(self):
        with self.assertRaisesRegex(own.OwnershipError, "missing or duplicated assembled"):
            self.rewrite(objects=[self.owner, self.pre])
        doubled = self.linker.replace("        cod_SDATA_END", "        build/src/game/owner.o(.sdata*);\n        cod_SDATA_END")
        with self.assertRaisesRegex(own.OwnershipError, "occur once"):
            self.rewrite(linker=doubled)

    def test_symbol_name_address_disagreement_rejected(self):
        self.entries[0]["address"] = "0x001EC88C"
        self.write_config()
        self.assertIn("disagrees with its name", own.check(self.root)[0])

    def test_no_gap_is_inferred_from_zero_data(self):
        self.splat["segments"][0]["subsegments"][1] = [0xEC890, "sdata", "cod/still_owned_by_asm"]
        self.write_config()
        self.assertIn("explicit Splat gap", own.check(self.root)[0])


class StaticTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="chulip-own-static-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "config").mkdir()
        (self.root / "src").mkdir()
        (self.root / "src/owner.c").write_text("/* fixture */\n")
        self.config = {"schema": 1, "owned": []}
        self.write_config()

    def write_config(self):
        (self.root / "config/data_ownership.json").write_text(json.dumps(self.config))

    def test_empty_claims_without_site_packages(self):
        import sys
        result = subprocess.run([sys.executable, "-S", str(Path(own.__file__).resolve()), "--check", "--root", str(self.root)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(own.rewrite_linker("unchanged", [], self.root), "unchanged")

    def test_invalid_schema_fails_closed(self):
        self.config["schema"] = 2
        self.write_config()
        self.assertIn("schema", own.check(self.root)[0])

    def test_unsafe_source_fails_closed_without_yaml(self):
        self.config["owned"] = [dict(symbol="value", source="src/../escape.c", address=1, size=4)]
        self.write_config()
        self.assertIn("unsafe", own.check(self.root)[0])

    def test_nonempty_json_layout_without_site_packages(self):
        import sys
        self.config["owned"] = [dict(symbol="value", source="src/owner.c", address=0x1000, size=4)]
        self.write_config()
        (self.root / "config/elf.json").write_text(json.dumps({"load_segment": {"vram": 0}, "sections": [dict(name=".sdata", vram=0x1000, size=8), dict(name=".sbss", vram=0x2000, size=8)]}))
        (self.root / "config/splat.us.yaml").write_text(json.dumps({"segments": [dict(start=0, vram=0, subsegments=[[0x1000], dict(vram=0x2000, type="sbss", name="cod/raw")])]}))
        result = subprocess.run([sys.executable, "-S", str(Path(own.__file__).resolve()), "--check", "--root", str(self.root)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)

    def source_layout(self, entry):
        self.config["owned"] = [dict(symbol="value", source="src/owner.c", address=0x1000, size=4)]
        self.write_config()
        metadata = {
            "load_segment": {"vram": 0},
            "sections": [dict(name=".sdata", vram=0x1000, size=8), dict(name=".sbss", vram=0x2000, size=8)],
        }
        (self.root / "config/elf.json").write_text(json.dumps(metadata))
        splat = {"segments": [dict(start=0, vram=0, subsegments=[entry, dict(vram=0x2000, type="sbss", name="cod/raw")])]}
        (self.root / "config/splat.us.yaml").write_text(json.dumps(splat))

    def test_explicit_source_provider_validates_without_objects(self):
        self.source_layout(dict(vram=0x1000, type=".sdata", name="owner"))
        self.assertEqual(own.check(self.root), [])
        self.assertEqual(own.required_fragment_objects(self.root), [])

    def test_explicit_source_name_must_match_claim_provider(self):
        (self.root / "src/other.c").write_text("/* fixture */\n")
        self.source_layout(dict(vram=0x1000, type=".sdata", name="other"))
        self.assertIn("exactly that provider", own.check(self.root)[0])

    def test_explicit_source_path_and_section_are_checked(self):
        for entry, expected in [
            (dict(vram=0x1000, type=".sdata", name="../owner"), "source contribution name"),
            (dict(vram=0x1000, type=".sdata", name="/owner"), "source contribution name"),
            (dict(vram=0x1000, type=".sdata"), "source contribution name"),
            (dict(vram=0x1000, type=".sbss", name="owner"), "outside retail"),
        ]:
            with self.subTest(entry=entry):
                self.source_layout(entry)
                self.assertIn(expected, own.check(self.root)[0])

    def test_untyped_dict_gap_rejected_without_splat_dependency(self):
        for entry in [dict(vram=0x1000), dict(start=0x1000, type=None), dict(vram=0x1000, type="")]:
            with self.subTest(entry=entry):
                self.source_layout(entry)
                self.assertIn("requires an explicit type", own.check(self.root)[0])


if __name__ == "__main__":
    unittest.main()
