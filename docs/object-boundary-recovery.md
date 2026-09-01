# Recovering authentic source-object boundaries

Chulip's retail ELF is stripped. It has no symbol table, relocation sections,
`.mdebug`, `.pdr`, line table, or compiler file descriptors. Its `.reginfo` is
the one merged output record and cannot identify input objects. Exact original
filenames therefore cannot be read directly from this executable.

This does not make source-object recovery arbitrary. It changes the work into
a constraint problem. `tools/object_boundary_scan.py` reports the constraints
that are reproducible from the local retail executable and ledgers.

## Evidence classes

Use these classes in descending order. Do not promote a weaker class merely
because it produces a convenient source layout.

1. **Direct provenance:** an original link map, unstripped ELF metadata, or an
   exact archive member whose debug record names its source file.
2. **Mandatory split:** two adjacent complete ranges cannot be produced by one
   compiler, assembler, and flag configuration. They cannot share one source
   compilation.
3. **Artifact anchor:** a relocation-masked or byte-identical range occurs in a
   named library object from the same SDK generation. The transferred object
   edges are accepted only when the complete member, including padding and
   owned data, agrees.
4. **Ordering constraint:** linker-preserved order of `.text`, `.rodata`,
   `.data`, and small-data contributions, or ownership of a compiler-generated
   jump table or literal pool, rules layouts in or out.
5. **Compatibility only:** adjacent functions compile successfully from one C
   file. This proves that the grouping is possible. It does not prove that the
   retail build used it.

Call-graph clustering, naming similarity, subsystem proximity, and an
eight-byte-aligned address are useful search hints only.

## Findings reproduced today

### Mandatory boundaries

Three source boundaries are mandatory within the recovered configuration set:

| Boundary | Left range | Right range |
| --- | --- | --- |
| `0x001017F0` | `0x001016A0-0x001017F0` | `0x001017F0-0x00101CC4` |
| `0x00130208` | `0x001300D8-0x00130208` | `0x00130208-0x0013024C` |
| `0x0014E550` | `0x0014E500-0x0014E550` | `0x0014E550-0x0014E64C` |

At each edge, the left range matches the historical `Ps2EeAs` route and the
right range matches the standard historical assembler. Neither assembler
route reproduces both sides.

The recorded matrix covers all seven project profiles with both `-Wa,-G0` and
`-Wa,-G8`, fourteen configurations in total. Every configuration has a byte
mismatch on at least one side. Some left-side `G8` attempts cannot link their
`.lit4` at the isolated verifier's temporary layout, but the camera side
byte-mismatches each of those configurations, so none remains a possible
shared configuration. The two ranges therefore require a source-compilation
boundary at `0x001017F0` within the recovered toolchain universe.

The complete matrix is in `config/object-boundary-evidence.json`.

### Current splits that are not proven

The same test rejects four tempting claims. Both sides of the current splits at
`0x00103C10`, `0x00103CF8`, `0x0010BF10`, and `0x00110000` match a shared
`Ps2EeAs` configuration. Those edges may still be authentic, but compiler
incompatibility cannot establish them. They remain compatibility observations.

### SDK generation anchors

The retail load image contains these version records:

| Retail marker | Interpretation |
| --- | --- |
| `PsIIlibgraph2400` | libgraph 2.4.0 |
| `PsIIlibdma  2400` | libdma 2.4.0 |
| `PsIIlibcdvd 2420` | libcdvd 2.4.2 |
| `PsIIlibkernl2430` | libkernl 2.4.3 |

These are precise archive-search keys. They do not by themselves assign a text
range to an archive member.

### Syscall-table artifact anchor

The range `0x00198380-0x00198C20` is 138 consecutive sixteen-byte syscall
trampolines, 2,208 bytes total. Every body has the form `addiu v1, zero, n`,
`syscall 0`, `jr ra`, `nop`. Its complete immediate sequence is identical to
the same 138-entry EE syscall table independently recovered in another PS2
retail executable, from syscall 0 through `InitTLB`.

This is strong evidence for the identity and outer extent of the table. It is
not yet a claim that all 138 stubs were one final linker input object. SDK
artifact comparison must resolve whether that table was assembled as one file,
partially linked, or drawn from several archive members.

### Cross-section order

The baseline currently identifies 94 jump tables owned by 85 functions. Their
lowest `.rodata` addresses are monotonic in `.text` order, with zero reversals.
That is consistent with ordinary GNU linker input order and supports using
cross-section order as a constraint. Monotonic order alone does not reveal an
edge.

### Newlib multiprecision band

`0x00196E04-0x00197F28` follows the classic newlib multiprecision sequence.
The already reconstructed `func_00197868` is `cmp`; the following large bodies
have the expected `diff`, `ulp`, `b2d`, `d2b`, and `ratio` shapes. This is a
source-family anchor, not a set of accepted object edges. Historical newlib
archive membership and full-member signatures are still required.

## Next measurements

1. Compare the four identified Sony library versions against lawful local
   reference archives. Mask relocation fields, then require complete archive
   member text, padding, data, compiler markers, and debug source names to
   agree.
2. Build a function-to-local-data ownership graph from jump tables, literal
   pools, and static strings. Use identical input ordering across `.text` and
   data sections to reject impossible segmentations.
3. Extend configuration-exclusion matrices around every exact multi-function
   range. Record layout errors separately from byte mismatches.
4. Recover both neighbors before accepting an outer edge. A complete combined
   match proves compatibility; a configuration contradiction or exact artifact
   establishes provenance.

## Reproduce

```sh
python3 tools/object_boundary_scan.py
python3 tools/object_boundary_scan.py --json build/object-boundaries.json
python3 tools/object_boundary_scan.py --verify-matrices
```

The JSON output is suitable for a future constraint solver. Generated reports
belong under `build/` and are not committed. Matrix replay requires the pinned
historical compilers installed by `tools/bootstrap.py`.

## Method references

- The MIPS ABI describes `.mdebug` as compiler symbol-table information. Its
  absence here is why filename extraction is unavailable:
  <https://refspecs.linuxfoundation.org/elf/mipsabi.pdf>.
- GNU ld documents input-section placement and wildcard ordering:
  <https://sourceware.org/binutils/docs/ld/Input-Section-Basics.html> and
  <https://sourceware.org/binutils/docs/ld/Input-Section-Wildcards.html>.
- GNU ar documents archive member ordering:
  <https://sourceware.org/binutils/docs/binutils/ar-cmdline.html>.
- PS2SDK provides the open-source library organization and API names used for
  identification, but not proof of Sony archive membership:
  <https://github.com/ps2dev/ps2sdk>.
- The independent 138-entry syscall comparison and its SDK-artifact limits are
  recorded by the God Hand decomp project:
  <https://github.com/LucasPicoli/god-hand-decomp/blob/main/config/retail_authored_asm.txt>.
