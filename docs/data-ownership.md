# Source-owned small data

The build can place a reconstructed source's complete `.sdata` or `.sbss`
contribution between the corresponding retail assembly fragments. This supports
honest source recovery when the historical compiler's small-data classification
depends on a definition in the same translation unit. It does not establish
original source ownership or boundaries by itself.

`config/data_ownership.json` records explicit claims. The first two
verified providers are func_00114010 (D_001EC8AC and D_001EC8B0) and
func_00114E88 (D_001EC8B8); existing camera globals retain their verified placement.
Before adding a claim, establish the symbol's definition, size, used-source
relationship and complete source range; record original-unit uncertainty explicitly. Do not add unused neighboring globals
or padding merely to obtain a convenient aligned span. Shared definitions or
conflicting existing ownership must be resolved before promotion.

Each entry provides `symbol`, `source`, `section` (`sdata` or `sbss`), `address`,
and `size`. Addresses use the normal `0x...` form. Every named definition in the
owner's claimed ELF section must have an entry. Multiple entries for one source
section produce one input contribution, not one contribution per symbol.

## Verification order

1. The coordinator stages reviewed source, ownership claims, and explicit gaps
   in the non-text portion of `config/splat.us.yaml` under the promotion lock.
   For zero-initialized storage use an explicit source subsegment, for example
   `{ type: .sbss, vram: 0x001ED4C0, name: game/func_001606A0 }`.
   Splat does not support a dictionary containing only `vram`. Typed source
   intervals must name exactly the provider in the ownership claims.
   Preserve all pre-transaction versions for rollback. Text regeneration leaves
   these data subsegments intact.
2. `python3 tools/data_ownership.py --check` validates paths, schema, addresses,
   section bounds, overlap and explicit gaps. This check is also part of split
   and public checks. It does not claim that source text or an old object is
   correct.
3. The builder compiles every input afresh, including configured assembly
   fragments that Splat may omit immediately after a gap.
4. `rewrite_linker` reads the actual ELF objects. It checks defined symbol sizes,
   unique providers, consistent section origins and complete section extents.
   Claims must enumerate all definitions in the owned section. The complete
   contribution must fill an explicit gap; fragment sizes must agree with their
   configured intervals. Unmodeled subsections and COMMON/scommon contributions
   are rejected rather than placed by assumption.
5. The builder places contributions in the final script it actually passes to
   GNU ld. Linker assertions check the start and end of every moved input. The
   separate `.cod_sdata` and `.cod_sbss` outputs honor each input ELF section
   alignment; text and ordinary BSS retain `SUBALIGN(8)`. The authentic
   alignment tail in the final raw `.sbss`
   fragment is accounted for separately from the bounds of owned symbols.
6. The usual full image, jump-table, branch-label, baseline, progress, source
   audit and repository gates remain required. The builder additionally checks
   the linked ELF's actual PT_LOAD address, file size and memory size. A matching
   file image alone does not prove the zero-fill extent.

The coordinator must restore ownership configuration and gaps as well as staged
sources if a proposed promotion fails. The generic candidate manifest currently
records function reconstruction; it does not automatically stage ownership
claims. Keep that distinction explicit in promotion scripts.

## The repaired wiring

The initial implementation modified `build/current/chulip.us.ld` during split.
Splat actually writes `build/chulip.us.ld`; the builder read that other file and
then overwrote the first. Placement therefore never reached the actual link.
Split now performs static validation, and the builder performs compiled-object
validation and placement immediately before writing its final script.

Real-link tests also exposed a separate zero-fill bug: assigning a plain end
address to `.` inside the BSS output section treated it as a section offset.
The current build used to end zero-filled memory at `0x004D242C`, despite the
retail end being `0x002E53AC`. `ABSOLUTE` fixes the assignment, and a PT_LOAD
layout check prevents file-only verification from hiding that error again.
The loaded 970,772 file bytes remained identical; this repair concerns the
memory extent recorded by the rebuilt ELF.

## Reproduce

```sh
python3 tools/data_ownership.py --check
python3 -m unittest discover -s tests -p 'test_data_ownership*.py'
make verify baseline public-check
```

The real-link tests assemble locally authored fixtures with GNU MIPS binutils;
no retail code or data is used. They verify actual linked bytes and addresses,
multiple symbols per owner, both small-data sections, retained camera globals,
omitted fragments, malformed claims, stale output scripts, and the actual ELF
memory end. Those tests skip cleanly when the tools are unavailable. Static
checks and imports work with Python alone when ownership is empty. Nonempty
YAML configuration uses PyYAML from the current environment or the existing
repository virtual environment; public CI installs the same pinned
[PyYAML 6.0.3](https://pypi.org/project/PyYAML/6.0.3/) as the local environment.
JSON fixtures need neither.

Local evidence is under `work/astra-20260909/ownership-*.log`. The previous user
work was preserved before integration under `work/astra-20260909/ownership-before/`.

## Current retail frontier

The first audit of ten exact-code candidates exposed an artificial placement
constraint: Splat combined small data with outputs using `SUBALIGN(8)`, although
these actual contributions align to 1, 2 or 4 bytes. The builder now separates
those alignment domains, preserving the original text placement and one
explicit PT_LOAD. All four allocated outputs belong to that segment; jump-table
INFO proofs remain outside it. Binary extraction includes both loaded output
sections. The existing `cod_bss_VRAM` alias still denotes the original SBSS
start, and ROM-size markers include both loaded sections. No source padding or
adjacent global claims are needed to overcome the former placement constraint.

One candidate additionally has a real byte mismatch: `func_0012CE60`'s trailing
compiler byte at `0x001EC905` is zero where retail is `0xFF`. Another duplicates
existing camera ownership. These remain excluded even if alignment support is
improved. The complete audit is in `work/parallel_ownership_audit/README.md` and
`assessment.json`. Original-unit and shared-symbol evidence still matters.

## First verified providers

The native-alignment path has promoted two 808-byte packet-building functions,
with complete initialized contributions of eight and four bytes. All three
globals are used, have unique C providers, and retain exact retail initializers.
The neighboring words remain assembled. Their original translation-unit outer
boundaries remain provisional; exact single-function ranges do not prove them.

Caller evidence also resolved ambiguous constant-count returns: func_00113670
and func_00114D70 return int, not the previously inferred EE 64-bit long. The
corrected definitions retain all 160 and 200 bytes. Both new callers match with
int declarations; changing their declarations to long inserts extra narrowing
instructions. Evidence: work/parallel_ownership_pilots/REVIEW.md and
work/astra-20260909/pilot-promotion-retry2.log.

## Subword raw fragments

The one-byte signed state provider D_001EC8D4 in func_001271F0 exposed a pinned
spimdisasm limitation: a separate one-to-three-byte data segment emits no
assembly bytes because its reader converts input to whole words. Starting a
larger word segment at an unaligned address also changes the generated word
grouping. The source provider itself is exactly one byte; expanding its claim
to cover neighboring bytes would not be justified.

The split configuration therefore retains D_001EC8D5..D8 as a three-byte raw
sdata fragment and starts the ordinary aligned remainder at D8. After Splat,
tools/small_data_fragments.py preserves only explicit one-to-three-byte raw
sdata fragments from configure.py's already authenticated image. It checks
the on-disk payload agrees, derives intervals from the existing ownership
layout, validates configured/interior labels, rejects active label collisions
and oversized spans, and retains NON_MATCHING markers. It emits byte directives
with alignment one and never supplies C progress or new ownership claims.

Eight tests include a real MIPS assembly/link fixture proving adjacent raw
bytes, a one-byte provider, and its three-byte tail retain their exact extents
without padding. The complete retail promotion also passes native ELF section
checks, all loaded bytes, and the PT_LOAD memory extent. Evidence is in
work/parallel_raw_fragments and work/astra-20260910/signed-state-promotion.log.
The signed declaration repair in the existing setter func_00127270 retains
all of its bytes and earns no new progress credit.

The halfword stream status D_001ECF88 in func_0017F470 uses the same rule:
the ordinary initialized `unsigned short` emits and owns exactly CF88..CF89.
Twenty retail halfword accesses and the explicit zero reset establish its type
and initial state. CF8A..CF8B form a separate two-byte raw fragment; the ordinary
aligned remainder starts at CF8C. Do not start a large raw segment at CF8A:
the fragment validator rejects it rather than changing the word grouping.
Both neighboring bytes remain unclaimed. The full 344-byte function, complete
two-byte object and loaded image pass independently; evidence is in
`work/astra_stream_review/exact.json` and `promotion.log`.
