# Matching workflow review, 2026-09-09

The starting verified ledger was 1,234 functions / 163,760 text bytes. The
existing full-image build was independently rerun and reproduced all 970,772
bytes with SHA-256
`77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.

## Improvements applied

The candidate queue used to accept the last assembly listing for a symbol.
Splat leaves partial diagnostic listings under `asm/matchings/` after source
units change. One such listing replaced the complete 224-byte `func_00196D24`
with its first instruction, hiding its branches and SIMD operations. The
reader now retains the longest available body. Zero-branch aliases are counted,
and `jr $31` is recognized as a return just like `jr $ra`. A regression test
covers the full-body versus stale-fragment case.

Replaying unfinished candidates recovered 25 functions / 3,804 bytes through
the ordinary importer, whole-image rebuild, independent baseline, tests, and
repository audit. This is recovered prior source work, not 25 newly solved
functions. All actually replayed exact compiler profiles remain recorded;
old profile claims that no longer reproduce were not promoted.

`func_00196CE8` also passed isolated replay, but the complete-image gate rejected
its integration at `0x00196D24`: object padding replaced the next function's
first instruction with zero. The transaction rolled back. Its full source-unit
boundary remains unresolved and it contributes no progress.

Exact opcode-family lookup found the pending-ID drain at `func_0017E668` as a
sibling of the already matched `func_0011E9E0` and `func_00139F30`. Transferring
the readable loop with the target's count, ID array, and callee produced an
isolated exact match under SN build 1.36 / G8. Its integration status is always
the live match ledger, not this discovery note.

## Research and the existing Kaze tools

Sources checked on 2026-09-09:

- [m2c](https://github.com/matt-kempster/m2c) documents `mipsee-gcc-c` for
  little-endian EABI64 and supports cross-function type inference. The existing
  Kaze checkout at commit `94098d4de68c2fcc13fb8cf1096a1520eb171abe` already
  supports that target, so no additional installation was necessary. It was
  exercised on Chulip packets locally. SIMD instructions and some EABI argument
  registers still produced explicit errors; these drafts are analysis only.
- [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) recommends
  targeted source variations near register-allocation completion. Its scores
  can ignore stack differences by default, and random rewrites need semantic
  review. Chulip already has an adapter through the authoritative compiler;
  use its existing integration rather than a second compiler driver.
- [objdiff](https://github.com/encounter/objdiff) provides interactive object
  comparison. It is a possible optional UI, not a replacement for relocated
  whole-range byte checks. No objdiff installation was needed for this pass.
- [Crash Wrath of Cortex's PS2 pipeline](https://github.com/denzi-gh/crashwoc-decomp-ps2/blob/main/docs/pipeline.md)
  independently uses compiler-specific game/runtime profiles and complete-image
  validation. Its compiler versions are not evidence for Chulip.
- [GNU's R5900 short-loop discussion](https://sourceware.org/pipermail/binutils/2018-November/105488.html)
  explains the hardware erratum and assembler workaround. It does not identify
  the historical assembler needed for Chulip's six-instruction padding. No
  matching replacement was established, and no padding was inserted by hand.

Kaze's current `docs/NOTES.md` reinforces compiler-option discrimination with
nontrivial functions and explicit assembler behavior. Its PS1 flags, assembler
patches, and source boundaries do not transfer as PS2 evidence. The historical
speed27 handoff named in memory was absent from this checkout; it was not used
as current evidence.

## Remaining measured frontiers

- `func_0011B020`: 2,928-byte particle routine, 18 differing words under
  `ee-gcc2.95.3-136-O2-G8-ps2as-g`, no extra object flags. The mismatch is confined
  to final packet/sprite register allocation and store scheduling. Bounded
  searches of 168 store orders, 80 expression/access shapes, 502 dependency-safe
  schedules, and 60 local/scope variants did not improve that score. An unsigned
  float conversion variant required unsupported `fptoui` and was excluded.
  These are failed searches, not proof that readable C cannot match it.
- `func_00108B10`: new readable parameter/vector publisher draft tested across
  the configured profile matrix and 40 indexing/declaration variants. Unmatched.
- `func_001599B0`: new structured object/animation reset draft. Loop induction
  and register allocation differ; the draft remains uncounted.

Ignored experiment scripts, candidate sources, and logs are under
`work/astra-20260909/` and the corresponding normal campaign packets. Resume
from those results and current leases instead of repeating these searches.

## Runtime division family follow-up

The pending-ID drain subsequently passed the complete promotion transaction.
The checkpoint is **1,260 functions / 167,656 text bytes**, a gain of 26
functions / 3,896 bytes over the starting ledger.

The next useful family comes from
[GCC 2.95.3 libgcc2.c](https://github.com/gcc-mirror/gcc/blob/releases/gcc-2.95.3/gcc/libgcc2.c)
and its
[longlong.h](https://github.com/gcc-mirror/gcc/blob/releases/gcc-2.95.3/gcc/longlong.h).
The original algorithm was retained with ordinary typed C arithmetic; its MIPS
assembly macro was not copied into the candidates. The leading-bit lookup table
is referenced at each retail symbol address.

| Function | Operation | Target / candidate bytes | Differing words |
| --- | --- | ---: | ---: |
| `func_001A16A0` | signed division | 1,772 / 1,772 | 3 |
| `func_001A1E80` | signed remainder | 1,640 / 1,640 | 3 |
| `func_001A24E8` | unsigned division | 1,488 / 1,488 | 3 |
| `func_001A2AB8` | unsigned remainder | 1,344 / 1,344 | 3 |

All four were measured with `ee-gcc2.9-991111-01-O2`, no extra object flags.
They remain uncounted. Together they cover 6,244 bytes and have the same
remaining multiplication issue. In the signed-division candidate at +0x648,
retail is `multu; mfhi; mflo`; the C candidate is a low-word multiply with a
GPR destination followed by `multu; mfhi`.

A single widening product followed by high/low extraction produced eight extra
instructions. Separate low-word multiplication followed by a high-product
expression reduced that to the three-word substitution above. Sixteen
signedness/order/local variants established this improvement; sixteen union,
array, and bitfield views did not remove the pack/extract overhead. The upstream
MIPS macro explains the retail sequence through HI/LO assembly constraints;
it is evidence of source shape, not permission to bridge the remaining words
with assembly. Compiler backend investigation or another lawful expression is
still needed.

Ignored authoritative follow-up inputs:
`work/astra-20260909/libgcc-frontier.json` records each candidate hash, exact
size, profile, and distance; the corresponding packet stores its C source and
diff. The downloaded upstream files are fingerprinted as follows:

- `libgcc2.c`: `83e33577971c17f33c4b4c66780c860319cb8828ac611cfb0cd14bb0320eaea9`
- `longlong.h`: `ef207d96698d0f66a3a8ba7823d986cce48aa0f46460a2ae6df5d3d4524f0495`

## Compiler backend and queue follow-up

The public [SSXModding EE MIPS machine description](https://github.com/SSXModding/ps2-ee-toolchain/blob/master/ee/gcc/config/mips/mips.md)
contains the R5900 patterns named by the installed Sony compiler. This is
supporting historical evidence; its exact correspondence to the installed
binary has not been authenticated. `xmulsi3_highpart_r5900` clobbers the low
result, while `mulsidi3_64bit_r5900` represents the widening result through the
accumulator. This explains why the tested C expressions either emit two
multiplies or pack a full-width product. No compiler changes were made.
The downloaded `mips.md` SHA-256 is
`177caa696e7de5e58515d1500abce727f8783454b4522fd3e5cd3e0630b99acf`;
its companion `mips.c` is
`1cc5a1350be8bb84c1dd4057ad74b5da893359afb20ae6628c2c35f17e2befd5`.

The queue also counted hardware-control routines such as `func_00188278`
and `func_00188460` as easy ordinary leaves despite their retail `sync`.
It now displays hardware-control instruction counts and assigns those
routines the same extra attempt cost as declared handwritten code. This
changes priority only: it neither reclassifies functions nor excludes them
from the denominator. The queue regression and full public checks passed
(114 tests).

Further bounded source searches remain uncounted:

- `func_00149C88`: 2,960-byte scene state machine, 15 differing words with
  SN 1.36 / G8 / PS2 assembler. The differences are seven setup words and
  four two-word branches into a shared transition. All 420 dependency-safe
  setup orders, 54 initializer/declaration variants, and 24 shared-tail
  variants failed to improve it. The original candidate is `h9_j.c` in its
  campaign packet; use `astra-diff.txt` to resume.
- `func_00151E68`: new sorted-pair insertion draft, correct 624-byte size
  and 80 differing words with SN 1.36 / G8 / GNU assembler. A cached next
  index avoids an alias-induced reload. The best result from 48 bounded
  local/loop/array shapes is `astra_shape_best.c` in its packet.
- `func_001520D8`: new 312-byte unlink draft for the same index-list family,
  correct size and 48 differing words after 64 global-lifetime, comparison,
  load-order and array-shape variants. Kaze's existing m2c successfully
  cross-checked this routine's control flow with the new type context.

The follow-up scripts and logs are under `work/astra-20260909/`. No further
functions have passed the exact promotion gate during this follow-up.

## Object-list family: nine new exact functions

A subsequent family pass integrated **nine newly solved functions / 1,440
bytes**, reaching **1,269 functions / 169,096 text bytes**. Every batch passed
isolated replay, the complete 970,772-byte image check, independent baseline,
114 tests, progress checks, and repository audit. The loaded-image hash remains
`77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.

| Function | Bytes | Recovered behavior |
| --- | ---: | --- |
| `func_001723A0` | 160 | Mark active entries and report whether any changed |
| `func_00172440` | 164 | Clear active-entry flags |
| `func_00171FD8` | 84 | Clear a supplied flag mask across the list |
| `func_00171478` | 172 | Invoke a snapshot operation on matching kinds |
| `func_00171528` | 172 | Invoke the sibling operation on matching kinds |
| `func_00173208` | 120 | Set or clear a supplied mask across the list |
| `func_001722B0` | 240 | Activate entries according to interaction flags |
| `func_00173280` | 192 | Search a cyclic entry range |
| `func_00171C88` | 136 | Clear associations and reverse owner fields |

All use SN 1.36 / G8. Most use GNU assembly with `-Wa,-G0`;
`func_00173208` uses default GNU G8, and `func_001722B0` uses the PS2 assembler
without an extra flag. Exact options remain in `config/reconstructed.json`.
The separate source files do not claim authenticated original object boundaries.

The transferable source pattern is a 192-byte entry stride, a count at +16 in
`D_002D8840`, and an integer-held base address `D_001ED6C0`. Ordinary indexed C
with that base reproduces repeated alias-sensitive reloads. For the association
cleanup, an integer local link ID followed by a structure-indexed links field
resolved a redundant move and then two address-operand differences. No assembly,
volatile accesses, or artificial padding were introduced to solve this family.

The next routine, `func_001715D8`, preserves an entry in a snapshot pool. Its
520-byte candidate has ten differing words under SN 1.36 / G8 / PS2 assembler:
four register choices before the token lookup and six in the compiler-generated
structure-copy loop. Explicit do/while searches and the halfword state-store
access shape reduced the first draft from 113 differing words to ten. Sixteen
loop/address/store combinations established this result; 24 token/copy shapes,
a builtin memcpy form, and a raw halfword token-store form did not improve it.
The best source is its packet's `astra_shapes_best.c`; `astra-best-diff.txt`
records the remaining differences. It is uncounted.

`func_00173340` remains uncounted at 20 differing words / 100 candidate bytes
against 104 retail bytes. Thirty-two conditional-result shapes and sixteen
return-node shapes did not solve it. Resume from its packet's
`astra_shape_best.c`, rather than repeating those searches.

## Parallel workers and measured build acceleration

After the user explicitly requested parallelization, three independent workers
started on the snapshot, restore, and remaining object-function families.
They write isolated packet candidates; one coordinator reviews results and
batches promotion. Near-matches remain uncounted.

The full builder previously invoked the compiler twice for each source: once
for an unused assembly listing, then again through the historical object path.
It also compiled all units serially. The builder now calls the historical path
once per unit and compiles independent units concurrently (up to four jobs by
default, configurable with `--jobs`). The fallback still uses the checked
compiler followed by GNU assembly. Linking, data and jump-table checks, and
full-image verification occur only after all worker jobs succeed. No object
cache or skipped source replay was introduced.

On the unchanged 1,269-function checkout, a fresh full build took **81.94 s
before and 21.20 s after**, a **3.87x speedup**. Both reproduced all 970,772 bytes
and the expected image hash. These are local wall-clock observations while
matching workers were also active, not a prediction of overall completion time.
Logs: `work/astra-20260909/build-before-speedup.log` and
`build-after-speedup.log`.

The candidate-search helper had the same duplicate compilation. Removing it
reduced average fresh candidate latency in four before/after pairs per profile:

| Probe | Previous average | New average | Reduction |
| --- | ---: | ---: | ---: |
| SN 1.36 / GNU, 160-byte function | 96.39 ms | 66.27 ms | 31% |
| SN 1.36 / PS2 assembler, 240-byte function | 70.35 ms | 39.29 ms | 44% |
| Sony 2.9, 8-byte function | 9.60 ms | 7.02 ms | 27% |

Every comparison verified the candidate bytes against retail. Raw observations
are in `work/astra-20260909/candidate-speedup.json`. The independent promotion
verifier retains its existing compiler replay and diagnostic artifacts.
Three new regression checks prove the historical/fallback paths and that a
failed worker cannot link a stale object; all 117 public tests pass.

## Complete soft-float family

The two archive-proven runtime objects now match in full from readable C and
passed the complete promotion transaction. The integration adds **11 functions /
3,984 text bytes**, retaining the 19 functions already matched inside these
ranges. The 30 function records now refer to `src/game/libgcc_dp_bit.c` and
`src/game/libgcc_fp_bit.c`. Complete object sizes are 3,316 and 3,040 bytes;
those totals include previously matched code and are not the progress gain.

The decisive evidence was the historical R5900 build recipe rather than another
local permutation. The public source tree
[`b595ded606227e93b8c4a447446c1d2ac093827d`](https://github.com/SSXModding/ps2-ee-toolchain/tree/b595ded606227e93b8c4a447446c1d2ac093827d)
contains both the target-specific
[`fp-bit.c`](https://github.com/SSXModding/ps2-ee-toolchain/blob/b595ded606227e93b8c4a447446c1d2ac093827d/ee/gcc/config/fp-bit.c)
and the
[`t-r5900` recipe](https://github.com/SSXModding/ps2-ee-toolchain/blob/b595ded606227e93b8c4a447446c1d2ac093827d/ee/gcc/config/mips/t-r5900).
Unlike the previously tested stock source, it implements `NO_DENORMALS` in
unpacking. The recipe selects that macro for both units and selects
`FLOAT_BIT_ORDER_MISMATCH` for little-endian targets. Making these historical
conditions explicit, together with `US_SOFTWARE_GOFAST` and the float unit's
`FLOAT`, produces both complete objects using the unchanged Sony 2.9 O2 profile.

Downloaded source SHA-256:

- `fp-bit.c`: `c44e6a9dcd898b2689c62ed2be770a445dd30d15afe78d4010429552e07d2190`
- `t-r5900`: `5da7447792ca73c73c8b615da64875af9a03e3dfd8295d90cc1eee7672b1b211`

The C retains upstream licensing and exposes the macro-expanded algorithm.
Existing NaN storage remains referenced through `D_002DE5F0` and `D_002DE608`;
this did not change BSS ownership. Reproduction, source preparation, manifests,
and source hashes are in `work/parallel_sdk/family-review.md`, `build_units.py`,
and `units.json`. The full transaction log is
`work/astra-20260909/sdk-units-promotion.log`. Neither archive objects nor
handwritten instructions are build inputs for these reconstructed units.

## Shared object and state-machine patterns

Parallel family work subsequently passed full promotion for 16 object routines
beyond the earlier nine-function batch, adding 5,088 text bytes. The reusable
192-byte record layout, integer base, count, radius checks, angle wrapping,
and known callee declarations solved several neighboring members on their first
C draft. Exact per-function profiles and complete natural alignment ranges
remain in the reconstruction ledger; these neighbors are not asserted to form
one original translation unit.

Two signature corrections had disproportionate value: declaring the discarded
results of `func_00158960` and `func_00158868` as `int` solved `func_001711A0`
and the entire 520-byte `func_001715D8`. The former callee has a matched C
implementation with explicit returns; the latter's retail paths explicitly
write `v0`. Even an unused result affects the historical allocator. This is
not a rule to change every `void` declaration: replaying supported return
corrections across 20 large candidates produced no further exact matches by
itself, and some historical callers match with differing declarations.

Searching `work/lanes/claude_jt3/NOTES.md` and its manifest recovered three
sidecarless exact candidates: `func_0013A120` (1,404 bytes), `func_00144FD8`
(1,116), and `func_00148CE0` (676). All **3,196 bytes** passed the full gate.
This is prior source recovery, not three newly solved functions. The same notes
already documented discarded-return register allocation and union-member
access for alias-sensitive global pointers. Those findings should have been
consulted before the earlier syntax searches; the campaign preflight now links
this recovery process explicitly.

The union access pattern also improved `func_00149C88` from 15 to 7 differing
words by reproducing its shared-tail branches without volatile accesses.
All 420 setup orders under the corrected alias model and 16 type/alignment
variants left seven setup words unresolved. It remains uncounted. Source and
diff: its packet's `parallel_protoaudit_union_int.c` and
`parallel-protoaudit-union-diff.txt`.

After these batches the verified checkpoint is **1,299 / 2,189 functions** and
**181,364 / 663,704 text bytes**: **+65 functions / +17,604 bytes** from the
starting ledger. The complete 970,772-byte image retains the expected hash;
all 117 tests and repository gates passed. Logs are the `parallel-*-promotion.log`
files under `work/astra-20260909/`. The live ledgers remain authoritative after
this checkpoint.

The new `tools/family_queue.py` lists pending functions by shared global and
links their already matched source examples. Coverage is all 2,189 catalog
functions. Clusters overlap, and byte counts represent investigation scope,
not predicted gains. For comparison, the local Kaze README's completed metric
is 648 game functions / 344,020 game text bytes, with remaining PsyQ/SDK code
assembled from disassembly. Chulip's current denominator includes runtime code;
these completion scopes and hardware/compiler targets differ.

## Giant-script context audit

The next pass produced ABI-clean, still-unmatched drafts for the 16,712-byte
`func_0016C5E8` and 14,444-byte `func_00168D78`. Both needed a consistent
byte-stream view at `func_001735A8`; its retail code reads byte input and returns
a pointer. The second giant additionally omitted the first float argument to
`func_0015E138` and `func_001272A8`: retail explicitly supplies the full value
in `f12` and half the value in `f13`. It also omitted the index passed to
`func_00138DF0`. These are semantic repairs, not matched-function progress.
The first giant omitted float arguments to `func_001584D8`/`func_00158558`
and a target ID passed to `func_00158698`.

`tools/callee_context.py` now compares candidate parameter counts and explicit
floating-point positions with matched callee definitions. It found these
conflicts but intentionally does not rewrite C. Extra arguments can be real:
retail passes three to `func_001788F8` although the current matched definition
uses only one. The matched `func_001280C0` wrapper also forwards live floating
arguments despite its empty prototype. Inspect both sides of each call; a
local definition alone is not the entire historical ABI context. Five focused
regression tests cover missing float arguments, explicit void versus unspecified
lists, callback/pointer arguments, false declarations in comments or calls, and
recursive calls inside conditions. All **122 public tests** and repository
checks passed after this addition.

The current giant drafts still have many local allocation/control-flow
mismatches. Raw positional differences are especially misleading when an
instruction insertion shifts a large switch. Sequence-aligned word comparisons
under `work/astra-giant/` are diagnostic only; the promotion authority continues
to require equality at every original byte address. Five profile comparisons
and supported return-declaration variants did not solve the second giant.
Its current semantic draft is `astra_giant_call_context.c` in the normal packet.
Definitions of shared small data remain a separate integration requirement.

## Broader manifest recovery

Following references from 13 other lane notes to 14 manifests, including
`work/claude/*.jsonl`, found 16 explicitly recorded old exact functions still
absent from the live ledger. The ten largest were freshly replayed under their
recorded profiles and full ranges. Seven source-only candidates passed complete
promotion: `func_00110810`, `func_00118600`, `func_00115B20`, `func_00181700`,
`func_00181858`, `func_00161FE0`, and `func_001620B8`, totaling **3,056 bytes**.
The new verified checkpoint is **1,306 functions / 184,420 text bytes**,
**+72 functions / +20,660 bytes** from the starting ledger. These seven are
recovered prior work. Full image, independent baseline, 122 tests and all
repository gates passed (`work/astra-20260909/manifest-recovery-promotion.log`).

Three further exact isolated sources require data ownership and remain uncounted:
`func_001014E0`, `func_001163B8`, and `func_001172F0`. Their definitions overlap
existing camera ownership or each other; simply introducing new data definitions
would not constitute a valid promotion. Metadata and the six smaller manifest
records are under `work/parallel_manifest_recovery/`. This is a concrete reason
to complete the existing small-data placement work before promoting those
sources, not permission to group functions by convenience.

The six smaller records were then rechecked. Five additional sources passed
full promotion (`func_0017AB40`, `func_0017F768`, `func_00113FB0`, `func_00152670`,
`func_0011FC30`), adding 444 bytes. The sixth, `func_00196CE8`, remains excluded
for the previously demonstrated neighboring-function overwrite. The manifest
inventory is now closed: 12 promoted / 3,500 bytes, three data-owner candidates /
564 bytes and one boundary-blocked candidate / 60 bytes. Latest verified
checkpoint: **1,311 / 2,189 functions, 184,864 / 663,704 text bytes**,
**+77 functions / +21,104 bytes** since this run began. The final recovery log
is `work/astra-20260909/manifest-recovery-final-promotion.log`; every gate passed.

## Global-data placement and memory-layout gate

The existing small-data placement work is now connected to the actual build,
with compiled ELF ownership checks and real-link tests. Split performs static
validation; the builder restores omitted raw fragments, compiles all objects,
then validates and places each complete owned contribution once in its final
consumed linker script. No new ownership claims have been introduced. See
[data ownership](data-ownership.md) for the source-evidence requirements and
promotion/rollback procedure.

The integration tests exposed an independent BSS-end bug that file-image
comparison could not detect. The previously linked ELF extended zero-filled
memory to `0x004D242C` instead of `0x002E53AC`. A plain constant assigned to `.`
inside an output section is section-relative; `ABSOLUTE` fixes the assignment.
Every full build now validates the actual PT_LOAD address, file size and memory
size against the target metadata, as well as comparing all loaded file bytes.

The fresh build and independent baseline both reproduce all 970,772 file bytes
with the expected hash. The current linked ELF has one PT_LOAD at `0x00100000`,
file size `0xED014`, and memory size `0x1E53AC`, ending at `0x002E53AC`.
All 158 local tests pass. A Python-only run without site packages or binutils
also passes, with 31 real-tool tests skipped. Logs:
`work/astra-20260909/ownership-final-verification.log`,
`ownership-public-check.log`, and `ownership-python-only-tests.log`.

A subsequent real-candidate pilot audit found ten exact-code small-data sources,
but none is directly promotable yet: their 1/2/4-byte data alignment conflicts
with the existing combined output section's eight-byte subalignment. This is a
linker-model limitation to investigate, not evidence for inventing larger
source blocks. `func_0012CE60` additionally emits a wrong adjacent data byte;
`func_001014E0` conflicts with the camera provider. The detailed evidence is in
`work/parallel_ownership_audit/`. A prototype separating text and small-data
alignment domains is the next concrete pipeline task.


## Native small data and shared return contracts

The previous eight-byte small-data constraint is now removed. Separate SDATA
and SBSS output sections honor actual ELF input alignment, while text and normal
BSS preserve their existing placement. Four allocated outputs share one PT_LOAD;
42 jump-table INFO proofs remain outside it. The original SBSS alias and ROM-size
markers retain their meanings. A fresh whole build and independent extraction
verify all 970,772 retail bytes and the 0x002E53AC memory end.

Six formerly deferred exact sources have passed complete promotion: 00114010,
00114E88, 00130E68, 001332D8, 001606A0 and 001609E0. They add 4,068 function
bytes, with seven explicit small-data claims. The final source has its separately
verified four-byte natural text tail, which does not add function-byte credit.
No unused neighbor globals, fabricated padding or original-unit claims were
introduced. Single-source ownership remains explicitly provisional.

Actual Splat integration also caught an invalid SBSS gap syntax that isolated
fixtures had accepted. Splat requires a typed .sbss source subsegment, including
its source name; a dictionary containing only vram is invalid. The helper now
validates that explicit source interval against exactly the claimed provider.
48 ownership/link tests and the full 171-test repository suite pass. Public CI
installs pinned PyYAML for nonempty ownership metadata.

Three callee definitions were reconciled with retail callers without changing
any bytes: constant packet-count helpers 00113670 and 00114D70 return int rather
than EE 64-bit long, and 001614E0 is void rather than an artificial constant
return. Do not infer a unique source signature from a small constant return.

The new return audit ranks 69 conflicts across 634 pending source candidates by
unique affected caller bytes. It treats these totals as triage scope, not a
prediction of additional matches. Retail result consumption matters: giant1
uses 00158698's f0 result, and loader1667B0 uses 00151A00's pointer result. Both
previously matched wrappers had incomplete void declarations. Correct float/
pointer forwarding sources independently retain all 88/32 bytes. Conversely,
copying matched long into pending 00115F18 worsened its 17-word difference to
53 words; the small constant callee result did not prove that width. This audit
is diagnostic and deliberately does not rewrite declarations automatically.

The shared byte at 001EC8C0 remains a separate blocker for 001163B8/001172F0.
Eight bounded ownership/assembler probes found no exact separate-source pair
with one provider. Local-definition context changes GP-relative instruction
selection; natural linker alignment alone does not resolve that. No duplicate
provider or arbitrary merged unit was introduced.

Evidence: docs/data-ownership.md, work/parallel_ownership_pilots/REVIEW.md,
work/parallel_ownership_next/REVIEW.md, work/parallel_return_audit/README.md,
work/parallel_shared_byte/REVIEW.md, and work/astra-20260909/
{pilot-promotion-retry2,next-ownership-typed-sbss,native-public-check}.log.


## Packet fade expression, DMA pointer type, and explicit table forwarding

Two further functions passed the full promotion pipeline: 00115F18 (1184 bytes)
and001886B8 (472 bytes), bringing coverage to1319 functions /190588 text bytes.
All970772 loaded bytes and the independent baseline remain exact;173 tests pass.
The packet builder owns two used small-data globals at1EC8BC/1EC8C0, with a
complete8-byte emitted contribution, and its32-byte local coordinate table is
verified at1E6AF0. No neighboring global was introduced. Its original source
unit remains provisional, and the conflicting1163B8/1172F0 candidates remain
unpromoted. The packet-count helper115A78 also retains exact bytes with its
return corrected from EE long to int, as supported by the caller.

The packet function's17 differing FP register fields disappeared when its early
fade expression became one statement:
`scale = 1.0f - (float)(60 - D_001ED1E8) / 60.0f;`.
This preserves the arithmetic order while giving the compiler the correct
value lifetimes. The natural unsigned-long conversion also replaces a direct
address-named runtime call. The DMA setter's remaining16 words disappeared
when the ring-base field was typed as a pointer. Only actual hardware register
accesses use volatile; tables and saved environment remain extern. Its exact
profile is Sony ee-gcc2.9-991111-01-O2, with no additional flags.

Harvesting the exact packet source exposed a concrete verifier wiring bug:
campaign supplied rodata_start, but batch_verify dropped the argument and
omitted it from its per-batch cache key. It now forwards the origin and keeps
proofs at different origins distinct. Regression tests cover the campaign
command and a batch where one origin passes and another fails. A targeted
replay of the only additional unchanged pending explicit-rodata candidate,
00123658, verifies its table but remains38 words off; no extra match was claimed.

Giant1's preferred candidate is now parallel_narrow_coordinate_returns.c:
16720 bytes against16712 retail bytes, still MISS and carrying unverified
inherited data definitions. A narrow unsigned-short helper return plus the
exact readable numeric literal1574.8033447265625f recovers the144-byte coordinate
conversion block, while preserving the prior96-byte movement opening. The
41 recovered immediate float-load patterns now agree with retail's value/count
multiset. This does not prove the whole function or its source-owned data.

A bounded follow-up on149C88 tested equivalent initialization shapes, local
buffer grouping and discarded return declarations. None beats its seven-word
frontier; these negative probes are preserved to avoid repeating them.

Evidence: work/parallel_packet15f18/REVIEW.md, work/parallel_1886b8/README.md,
work/parallel_rodata_replay/, work/parallel_narrow_returns/README.md,
work/astra_scene_setup/README.md, tests/test_batch_verify.py and
work/astra-20260909/packet-dma-promotion.log.


## Packet cursor and unmatched-library return follow-up

The initial probes below left coverage at1319 functions /190588 text bytes;
none of these four drafts was an exact complete function. The subsequent
standard-library follow-up produced the additional promotion described below.

00180E18 retains304 bytes and improves from40 to24 differing words. A typed
qword/vertex cursor and explicit packet-count local preserve its operations
while improving allocation. An alternate27-word draft has an exact first100
and final48 bytes. A190-pair store-order experiment did not beat the cursor
draft; older/bundled-assembler profiles emit300 bytes and differ more. Source,
proof hashes and negative probes are in work/astra_180e18/.

00123658 retains1080 bytes and its exact32-byte table, improving from38 to36
words. Actual projection-helper instructions support three pointer parameters
and an integer VU clip result, so no missing float-argument or return contract
was inferred. Thirty-seven targeted source/profile probes leave the projection
and alpha register allocation, angle evaluation scheduling, and ADC conditional
selection unresolved. See work/parallel_123658/REVIEW.md.

The new00187E80 GS display-environment source is628 bytes against624 retail.
Modern PS2SDK display/dispfb bitfield widths do not reproduce retail's masks,
so substituting them would change behavior. No matching historical headers were
found in the installed compiler archives. The candidate remains unpromoted;
see work/parallel_187e80/frontier.json and its header-search evidence.

Giant1's improved source is parallel_giant_memset_context.c. A void declaration
for the unmatched memset routine had escaped the matched-callee-only audit.
Retail's epilogue returns the original destination in v0. Restoring that pointer
return makes the first104 bytes exact, while preserving the prior96-byte
movement and144-byte coordinate blocks. Whole-function size is still16720 vs
16712. Case1001 remains the earliest genuine length/control divergence; a
smaller shared-tail variant does not reproduce its116 retail bytes and was
rejected. A pure-pointer context model wrongly removes912 bytes of required
reload behavior. The inherited data audit also finds82 definitions, only six
referenced by this function; those definitions remain unverified and prevent
promotion. No globals were added or counted by this investigation.


The standard-library follow-up promoted001308F8, all216 bytes, solely by
correcting memset's return from void to void*. Retail returns the original
destination in v0; the discarded return still affects caller allocation.
Four bounded callers were tested:128FD0 improves its aligned-word comparison
but stays96/112 bytes, while125CD8 and15E878 change no bytes. The discovery
ranking includes obsolete drafts and overlaps between helpers; its byte totals
are not predictions of new coverage. See work/parallel_giant_blocks/
library_returns/README.md for direct epilogue evidence and all eight builds.

Final checkpoint:1320/2189 functions,190804/663704 matched function bytes.
All970772 loaded bytes, the independent baseline, and173 tests pass. Promotion
log:work/astra-20260909/library-return-promotion.log. The preferred giant1 draft
remains parallel_giant_memset_context.c, with its104/96/144-byte local checks
and unverified inherited data definitions explicitly recorded.


## Historical sqrt source and assembler-profile recovery

The next transaction promoted two complete functions, 884 bytes, reaching
1322/2189 functions and191688/663704 function bytes. The complete970772-byte
loaded image and independent baseline remain exact; all173 tests pass.
Evidence:work/astra-20260909/sqrt-initializer-promotion.log.

0018BC30 is the classic fdlibm double square root. Authenticated newlib commit
b0ba0ac21747fef4f150f2632aedf0f59e0ae03a (2000-02-21), e_sqrt.c, matches all772
bytes under Sony EE GCC2.9 O2. The Sun license and algorithm are retained.
The endian union word macros come from the same historical fdlibm.h; one/tiny
remain the same compile-time constants, expressed as macros to avoid emitting
unused static data. The final object contributes only text. This is a source
lineage result rather than a local permutation search. Provenance, hashes,
initial and final sources, section audit, and rechecks are in
work/parallel_18bc30/README.md and exact.json.

00128FD0's corrected memset declaration was already sufficient C. Explicit
Ps2EeAs profiles restore the mixed absolute/GP global-access expansions and
match all112 bytes; the earlier96-byte result used the bundled GNU assembler.
Both recorded Ps2EeAs profiles passed fresh harvest. All globals remain extern.

The follow-up00125CD8 produces296 bytes against292 with Ps2EeAs. Its first
mismatch is one extra loop-padding nop at+0x50; following instructions shift
by four bytes and branches relocate. This is the documented six-vs-seven
short-loop assembler frontier. No source padding was added.

The remaining standard-library return audit performed25 bounded builds across
seven functions/eight drafts without another match. Giant2's preferred source
is now parallel_library_returns_context.c (SHA256
31a1d2cf14778d9fe9601c847db6b1078fbc1fa7ae2a86b373256b7e471f3a76).
Its memset correction improves four instruction words, but the whole function
remains14400/14444 bytes and its inherited data definitions are unproved.
Work/parallel_libc_remaining/README.md preserves the negative results.

00151E68's table-representation and store-order probes also gave no improvement:
624 bytes,80 differing words. The matched initializer proves two0xC000-byte
tables with8-byte entries; the retail post-increment boundary behavior must be
preserved. The complete tail from00152068 matches. Remaining differences are
first-search index lifetime and empty-list stores, recorded in
work/parallel_151e68/REVIEW.md.


## fdlibm family transfer: seven complete routines integrated

The first three-function batch added float square root (312 bytes), float
cosine kernel (344 bytes), and double sine kernel (468 bytes). The next batch
added double cosine kernel (588 bytes), float arccosine (1,072 bytes), and float
argument reduction (992 bytes). Including double square root (772 bytes), this
family has contributed seven complete functions / 4,548 text bytes so far.
The checkpoint is 1,328 functions / 195,464 text bytes. Both transactions passed
independent source replays, all 970,772 loaded bytes, an independent baseline,
and all 173 tests. Logs: fdlibm-three-promotion.log and
fdlibm-next-promotion.log under work/astra-20260909.

These are the historical newlib algorithms at pinned commit
b0ba0ac21747fef4f150f2632aedf0f59e0ae03a, with original Sun notices preserved.
The float routines need Sony GCC 2.9 O2 with assembler -G0 except sqrtf, which
matches the default profile. Double sine/cosine use the default Sony profile.
Original algorithm constants replace the earlier reconstruction guesses.
Exact associated tables/pools are independently checked at their explicit
retail origins: sine 56 bytes at 0x1EB8B8, cosine 48 bytes at 0x1EB7E0, and
float range reduction 920 bytes at 0x1EB3E0. Mutable/small data is unchanged.

The float reduction tables are canonical two_over_pi[198] and npio2_hw[32].
They are source algorithm data, not a copy of target instructions. Constant
macros suppress unused scalar objects while retaining the original values;
any actual compiler-generated literal pool remains verified. Single-function
original-unit ownership stays provisional throughout these promotions.

The original SN assembler search obtained one genuinely different executable:
Ps2EeAs 1.9.6.516, SHA256
44bcd9aaa229d8a453730142792d542e56da14761e9677cffcd1a183f603836d.
Its archived Git blob and native version resource were checked. It still
emits seven-instruction short loops: 00125CD8 is 296/292 bytes and 0012C3F0
is 248/240 bytes. The original ProDG Build Tools manual exposes no threshold
option. No function was promoted from this experiment. Evidence and pinned
archive/manual references: work/parallel_shortloop_research/REVIEW.md.


## Completed fdlibm family pass

All ten routines in the initially identified 0x18B710..0x18E2B4 math cluster
passed full integration, totaling 11,156 text bytes. The final cluster batch
added double argument reduction (1,308 bytes), its double kernel (2,920 bytes),
and the float kernel (2,380 bytes). Original constant sections were also exact.
The double reductions require the actual compiler G0 profile as well as
assembler G0: preserving their original static scalar constants correctly
positions subsequent literal pools. These constants must not be mechanically
replaced with macros across every family member.

The adjacent helper/wrapper pass added another sixteen complete functions /
3,492 text bytes: double/float floor and scalbn, float sine kernel, double/float
fabs and copysign, float isnan, three trig entries, and three error wrappers.
The two float error wrappers use natural casts; the compiler-emitted fptodp
and dptofp names now resolve to the already-matched complete libgcc providers
00187140 and00186548. Their source signatures, conversion algorithms, and
retail wrapper relocation sites agree. Full-image verification includes these
aliases. No explicit helper calls replace the C conversions.

This complete pass recovered **26 math functions / 14,648 text bytes**, plus
1,890 independently verified original read-only bytes. Including the unrelated
112-byte initializer, this checkpoint advanced by **27 functions / 14,760
text bytes** from 1,320 /190,804. The authoritative ledger is now
**1,347 /2,189 functions and205,564 /663,704 source-matched function bytes**.
This is a gain of113 functions /41,804 bytes over the campaign's initial ledger.

All970,772 loaded bytes retain SHA256
77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876.
Independent baseline, all173 tests, and repository audit pass. The nine
small-data ownership claims are unchanged. Single-function original-unit
ownership remains provisional. The reduction and final helper transactions
are recorded in work/astra-20260909/fdlibm-reduction-promotion.log and
fdlibm-helpers-wrappers-promotion.log; machine checkpoint is
fdlibm-family-checkpoint.json in the same directory.

Family provenance and source/object hashes are retained under
work/parallel_fdlibm_inventory, work/parallel_fdlibm_helpers,
work/parallel_libm_wrappers, work/astra_libm_small, and the four original
work/parallel_18* math investigation directories. Each function went through
the ordinary campaign harvest and transactional merge; no local match or
analysis similarity was credited without the whole-image pipeline.

The parallel 2,148-byte state-restore investigation did not produce an exact
function. Its post-shift casts and real unsigned-byte callee parameter were
recovered, while the aggregate alignment and saved-pointer lifetimes remain
unresolved. Twenty-five additional bounded probes and source hashes are
preserved in work/parallel_1776e8/REVIEW.md and frontier.json. The initial
complete readable draft and nine earlier probes are in work/astra_1776e8.

## Allocator and indexed-list family follow-up

The next transaction added three complete functions / 1,344 text bytes:
newlib `_memalign_r` at 001916D8 (464 bytes), `_strtol_r` at 00192DC0
(568 bytes), and indexed-list removal at 001520D8 (312 bytes). The ledger
reached 1,350 / 2,189 functions and 206,908 / 663,704 text bytes. All loaded
bytes, the independent baseline, and all 175 tests passed. The transaction
log is work/astra-20260909/newlib-index-clean-promotion.log.

The allocator uses the existing pinned mallocr.c with its already-established
16-byte alignment and historical size-type configuration. Its original
integer-to-pointer address-rounding operation generates one compiler warning
on EE, where long is 64 bits and pointers are 32 bits. The diagnostic review
is bound to this exact warning, line, canonical source path, and SHA256
47847abda5d1adfb8c55ecafac766f456c3e2ee0569f022c088b753fa6586cdc.
Other paths, changed source contents, other warnings, and implicit conversions
remain rejected. The vendored source differs from the pinned upstream hash
only in its pre-existing portable malloc.h include. Regression coverage checks
the allowed case and these rejection cases. Rejected import attempts restored
the previous tree before the successful transaction.

The strtol reconstruction preserves the Berkeley notice and historical
64-bit long behavior. Including stddef.h before the vendored reentrancy header
avoids conflicting NULL definitions without changing generated instructions.
The existing strtol and atoi wrappers now carry the proven pointer parameter
types, and strtol's long return type, with their complete old byte ranges still
exact. These signature corrections add no function credit. Sony compiler G0,
as well as assembler G0, is needed for the strtol wrapper's absolute reentrancy
pointer reference. Assembler G0 alone does not undo compiler GPREL selection.

For indexed-list removal, placing predecessor traversal in the increment of
a natural for loop resolves the remaining register-lifetime differences.
The paired eight-byte entry tables agree with the already-matched initializer.
The retail existing-key precondition is preserved. No data definitions or
additional source-unit ownership claims were introduced.

The candidate queue now reports a conservative short-loop diagnostic: complete
straight six-instruction backward loops containing padding before the closing
branch. A live census found 55 such loops in 49 unmatched functions totaling
38,412 bytes. This lowers their immediate search priority; it changes neither
the completion denominator nor the required source language. It is not a full
blocker census: unpadded six-instruction loops can already match, while the
new 00158EB0 draft has three natural six-instruction loops that the available
SN assembler expands to seven. Its 1,216-byte C draft remains unmatched with
238 / 304 differing words. Evidence: work/parallel_158eb0/REVIEW.md and
work/astra-20260909/shortloop-live-inventory.json.

Original R5900 assembly sources reproduce another seven string routines /
1,728 bytes, and their historical Makefile selects .S implementations. This
establishes provenance, not readable-C completion. None was promoted. The
source/archive hashes and exact assembly evidence are preserved in
work/parallel_newlib_strings. A separate audit of 825 campaign attempts and
794 bounded report/evidence files found no untouched unmatched candidates
that could be recovered solely by the new fptodp/dptofp aliases; see
work/parallel_conversion_recovery. These negative results prevent repeating
unproductive family searches.

## Formatter and DMA snapshot breakthrough

The custom callback formatter 0019A178 is now fully integrated: 1,480 text
bytes and its naturally generated 292-byte switch table at 0x1EC1C0 are exact.
It preserves the retail eight-byte argument slots, float handling, width
parser, and unsupported-specifier behavior. Its final two differing words
were resolved by placing the buffer decrement in each hex-digit conversion
branch before assigning the unsigned-char result, followed by a common store.
This is ordinary C control flow; no instructions were patched or forced.
The formatter's signed division and remainder expressions exposed missing
central aliases for the already-identified 001A16A0 and 001A1E80 runtime
providers. Their aliases are verified in the loaded image but do not credit
those still-unmatched runtime implementations.

The DMA pair 00188C60 / 00188D50 also passed full integration, contributing
236 and 240 text bytes. The critical source model separates the stopped
control snapshot from the loop-carried snapshot and writes the stopped value
back after the loop. The outer running-bit guard ensures this value is
initialized on every path that reaches the write. Only hardware accesses use
volatile; local snapshots are ordinary values. A separate command snapshot
then changes direction, mode, and running bit. The same shape transfers to
the second routine's mode-two setting. Both objects emit only text.

These results correct the earlier assumption that this SDK stop-loop shape
could not come from natural C. The old compiler retains its unusual loop
structure when the actual snapshot lifetimes are represented. The target
loop is not the separate six-versus-seven assembler-padding issue.

All three routines passed transactional replay, exact loaded image and
independent baseline checks, all 175 tests, and repository audit. The ledger
reached 1,353 / 2,189 functions and 208,864 / 663,704 source-matched text bytes.
The log is work/astra-20260909/formatter-dma-promotion.log. Final source hashes,
object sections, and bounded negative experiments are preserved under
work/parallel_19a178, work/astra_formatter_tail, and work/parallel_dma_pair.

A bounded raw-word sibling census now complements the existing opcode and
shared-global tools: equal-size retail functions of at least 64 bytes with at
most three differing instruction words. Its initial snapshot found 22 pairs.
This is a search aid, not match evidence. It independently located the
command-six/seven RPC siblings and a further DMA pair. Other exact duplicates
contain VU or privileged cache instructions and receive no source credit.
The reproducible census is work/astra_family_pairs/inventory.py and its JSON
report. Candidate-source history still needs checking outside campaign harvest
records: an absent campaign attempt does not establish that a function was
never investigated.

## Twelve-function family batch integrated

The follow-up batch added twelve functions / 3,880 source-matched function
bytes. All twelve passed independent fresh replay and the complete integration
pipeline, with 175 tests, unchanged nine data-ownership claims, and the same
970,772-byte loaded-image SHA256. The ledger is now **1,365 / 2,189 functions
and 212,744 / 663,704 source-matched function bytes**. The transaction log is
work/astra-20260909/rpc-dma-gif-family-promotion.log.

Six more DMA functions contributed 1,272 bytes: 001888F0, 001889C8, 00188AB0,
00188B98, 00188E40, and 00188F08. Seven focused source experiments recovered
all six. The first five drafts matched immediately; the final two-word
status-query difference required a status snapshot distinct from the timeout
control snapshot. Together with the preceding pair, the newly recovered DMA
family totals eight functions / 1,748 bytes. Full contracts, hashes, object
sections, and initialization proofs are in work/parallel_dma_followup.

The module RPC family contributed three functions / 1,588 bytes: 0019F9E0,
0019FBE8, and 0019FFF0. Public PS2SDK loadfile protocol definitions establish
the real shared 512-byte packet, two reply words, and 252-byte pathname and
argument slots. These are retail-based readable reconstructions, not a claim
that modern PS2SDK is the original Sony source. Capturing the returned ID
before storing through the caller's potentially aliasing output pointer
resolved the initial three-word mismatch. The command-six/seven sibling and
the third pathname wrapper then matched on their first transferred drafts.
Constant 252-byte copies use natural builtin memcpy expansion; variable copies
call the known memcpy function. Existing packet and client globals remain
extern, with no emitted data. Pinned public source URLs, hashes, semantic
differences from modern code, and fresh proofs are in
work/parallel_remaining_family_inventory and work/parallel_module_rpc_next.

The GIF packet-builder family contributed three functions / 1,020 bytes:
00134A48, 0017B248, and 00184288. Fresh replay recovered an older unmerged
complete source for the first. The genuine sibling differences are a texture
argument and one upper UV coordinate; both transfers matched on their first
compile. Each 340-byte function emits four additional natural alignment bytes,
verified through the next catalog entry without overwriting it. These 12
alignment bytes are not function-byte credit or authentic-unit ownership
proof. No source padding or data definitions were added. Evidence is in
work/parallel_duplicate_families.

This entire follow-up pass, starting from the completed fdlibm checkpoint,
added **18 functions / 7,180 function bytes**. The campaign gain from its
initial 1,234 / 163,760 ledger is **131 functions / 48,984 function bytes**.
The machine checkpoint is
work/astra-20260909/sdk-family-transfer-checkpoint.json. Remaining work stays
under the full 2,189-function / 663,704-byte denominator; no partial routines,
authored assembly, or local similarities are credited as matching C.

## September 10: shared completion state and game records

Nine more complete functions passed the full transactional pipeline, adding
**3,524 source-matched function bytes**. The authoritative ledger is now
**1,374 / 2,189 functions and 216,268 / 663,704 function bytes**. All 175 tests,
independent baseline, full loaded-image and layout checks, progress checks,
and repository audit passed. The loaded-image SHA256 and nine small-data
ownership claims remain unchanged. The transaction log is
work/astra-20260910/recovery-callback-promotion.log.

The largest new function is the 960-byte file-I/O completion callback
0019BFD8. A complete readable reconstruction initially matched the first
836 bytes, including its unaligned fixed-size copy expansions, with the
remaining differences confined to completion handling. Declaring the actual
shared completion table volatile resolved all remaining differences. Its
100-byte compiler-generated switch table at 0x1EC2F0 also matches completely.
Local variables and copy loops remain ordinary nonvolatile C.

The qualifier is supported independently of the byte match: file-I/O setup
registers this callback as system command 0x80000011; SIF initialization
installs the dispatcher on DMA channel 5; the interrupt dispatcher invokes
that registered handler. Foreground requests insert semaphore IDs in the
32-entry table, the callback clears them asynchronously, and a status routine
scans pending completions. The callback's synchronous branch calls iSignalSema.
This establishes real interrupt-shared state. The original declaration is
still inferred, not authenticated proprietary source. No new data provider
or synchronization operation was introduced. Independent semantic and artifact
proofs are in work/astra_19bfd8/review; the final formatted source was freshly
harvested and independently replayed again by the importer.

The same declaration-only correction improves the existing 704-byte write
candidate 0019D028 from 50 to five differing words, and ioctl 0019D2E8 from
46 to 38. Both remain uncounted. The write frontier consists of two async-flag
predicate words and three alignment-prefix arithmetic words. The obvious
direct-mask replacement changes common-expression optimization across both
flag checks and makes the whole function worse. Bounded negative probes and
preferred hashes are preserved in work/parallel_io_completion_transfer.

The new game routine 00138468 contributes 640 bytes. Matched siblings establish
its 36-byte event-record layout and linked-index list. Three source experiments
recovered the complete allocator/replacement logic; explicit forward field
assignments resolve the final 12 differing stores. It preserves retail
low-byte callback arguments and the existing full-list precondition. The
adjacent 408-byte tick/dispatch draft 001382D0 remains 12 words away with an
assembler macro-delay warning; 00138798 remains 344 / 352 bytes. These are
recorded frontiers, not additional credit, in work/parallel_game_family_next.

Six older c13 packet, ID-routing, and timer sources were independently reviewed
and promoted: 001314D0, 001327E0, 00132958, 00132B10, 00139FA0, and 0013AA38.
Their catalog sizes sum to **1,856 function bytes**, and all **1,880 emitted
bytes** including natural alignment were verified. The earlier handoff's
1,816 / 1,840 aggregates were arithmetic errors; per-function proofs were
correct and the handoff README has been corrected. The importer and public
ledger use catalog-derived totals. No writable or read-only data is emitted.
Use work/parallel_old_packet_recovery/promotion-ready.json as the final reviewed
set rather than the earlier seven-function ready.json.

Two superficially exact old candidates remain deferred. 0013D288 reproduces
an impossible division trap through a discarded division, but the surviving
instructions do not establish the original discarded computation; that is
insufficient semantic evidence. 00132DC0 defines a small-data pointer already
owned by 00130E68; its neighboring 00132C20 also hits the known external-GP
reference issue. No duplicate provider or artificial source grouping was used.

DECI2 open 001A0C58 contributes the remaining 68 bytes. Its correct return and
callback types, four-word request, and uncached buffer alias match Sony O2.
The IOP-reset follow-up 001A0718 remains unmatched: explicit C scanning recovers
its 128-byte frame and both copy loops, but length arithmetic still differs.
Builtin strlen instead emits a real call and is not a solution. Review and
bounded experiment evidence are in work/parallel_rpc_remaining.

## File-I/O read and write integrated

The completion-state breakthrough transferred to full read and write requests:
0019CDB8 (624 bytes) and 0019D028 (704 bytes). Both passed the complete pipeline,
adding 1,328 function bytes and reaching **1,376 functions / 217,596 bytes**.
All 175 tests, baseline, loaded-image/layout checks, and repository audit passed.
The log is work/astra-20260910/io-read-write-promotion.log.

The new complete read reconstruction was two instructions away on its first
compile. Its first async predicate must preserve the low-half flag conversion
as `(short)flags & 0x8000`, followed later by the full-word mask. A sign test
produces the wrong instructions, while two plain masks cause cross-call
common-expression reuse and change register allocation. Both the retained
expression and a separate unsigned-short snapshot matched the read routine;
the simpler mask expression is used. This is ordinary flag arithmetic under
the historical compiler's integer-conversion behavior, not a forced register
or volatile local. All real shared completion-table accesses remain volatile.

That same expression reduced the write candidate to three arithmetic words.
A separate unsigned address temporary for buffer-address minus 16 recovers
the target's alignment-prefix calculation. The subtraction is defined modulo
32 bits and produces the same distance to the next 16-byte boundary; no
out-of-object C pointer arithmetic is needed. Three of eight bounded source
variants were exact, and the fully unsigned form was independently reviewed
and retained. See work/astra_write_prefix/results.json and the final source,
hash, section, and semantic proofs in work/parallel_io_read.

The earlier five-word write and two-word read frontiers are superseded by
these full promotions. Neither source emits writable or read-only data.

## File-I/O open and seek integrated

Open 0019C778 (644 bytes) and seek 0019CB80 (568 bytes) now pass the full
integration pipeline too. Together they add 1,212 function bytes, bringing the
ledger to **1,378 / 2,189 functions and 218,808 / 663,704 function bytes**.
All 175 tests, exact loaded image and memory extent, independent baseline,
progress generation, and repository audit passed. The transaction log is
work/astra-20260910/io-open-seek-promotion.log.

The seek transfer preserves the same local request-packet pointer through the
async semaphore table updates. Replacing repeated direct global-field access
with this existing pointer restores its live range and the retail frame size,
leaving four words. Initializing the return buffer pointer before its size
then resolves those words. The actual packet, volatile completion table,
signed-short flag mask, and behavior remain those already established by the
read/write siblings. No new storage is introduced.

For open, reusing the consumed RPC status local as the final descriptor index
restores the full 644-byte size and saved-register allocation, reducing the
older 50-word mismatch to five. Capturing the completed result before updating
the descriptor resolves two more words. Capturing the actual unlock semaphore
ID before those shared descriptor writes resolves the final three. These are
ordinary value snapshots and lifetimes that follow the observed load/store
ordering, not forced liveness or placeholder operations. The EE variadic mode
argument uses the independently established compiler builtin convention and
its real saved argument slots. Final hashes and independent semantic, ABI,
section, and byte proofs are in work/parallel_io_read; bounded root probes
remain in work/astra_open and work/astra_lseek.

The same transaction corrects the existing 44-byte lock helper 0019C3E8 to
accept the request argument already passed by its matched callers and declare
WaitSema's actual integer return. Its argument remains unused, as in retail,
and its complete bytes are unchanged. This signature repair earns no new
function or byte credit.

The callback plus open, seek, read, and write form a completed five-function
file-I/O family pass totaling **3,500 source-matched bytes**, with the callback's
100-byte switch table independently exact. Ioctl 0019D2E8 remains a bounded
844-byte frontier with a fully exact 664-byte suffix. Its initial dispatch
constant lifetime is still unresolved; the new async-flag pattern does not
apply to that routine. Nine bounded dispatch/context variants are recorded
in work/parallel_io_read without additional credit.

The September 10 pass adds **13 functions / 6,064 function bytes** from the
1,365 / 212,744 checkpoint. Campaign gains are now **144 functions / 55,048
function bytes** over the original 1,234 / 163,760 ledger. The full denominator
and source-quality rules remain unchanged. Current machine checkpoint:
work/astra-20260910/io-family-checkpoint.json.

## Further family transfers and work-packet context

The next bounded pass promoted **seven functions / 2,808 function bytes**,
reaching **1,385 / 2,189 functions and 221,616 / 663,704 function bytes**.
Campaign gains are **151 functions / 57,856 bytes** from 1,234 / 163,760.
All 184 tests, full loaded-image and memory-extent checks, independent baseline,
progress checks, and repository audit passed. The denominator is unchanged.
The checkpoint is work/astra-20260910/family-transfer-checkpoint.json.

File-I/O seek64 0019ED00 (568 bytes) matched its first compile after transferring
the verified seek packet and semaphore model and widening the offset/result.
Callback setter 0019C428 (144 bytes) uses the real persistent hook pointer and
stores the argument before publishing the typed handler. Its lock declaration
agrees with the existing integer-returning provider. Neither emits data.

A separate compiler witness overturned an overly broad delay-loop exclusion:
`for (delay = 0x100000; delay != -1; --delay) {}` naturally emits all 36 bytes
of the observed initialization and seven-instruction countdown loop under
Sony 2.9 O2. There is no source assembly, volatile local, or padding. The
complete file-I/O initializer 0019C4E8 (456 bytes) then matched on its first
compile using this actual retry loop. Independent review verified both command
registrations, descriptor reset, semaphore use, uncached result copy, and all
return paths. This does not solve the distinct six-instruction assembler
padding frontier. Evidence: work/parallel_cluster_shortlist/delay-proof.json
and work/parallel_io_bind/initializer-review/README.md. All three file-I/O
functions passed work/astra-20260910/extended-io-promotion.log, adding 1,168
bytes. The eight-function file-I/O family now accounts for 4,668 matched bytes.

Three members of the D_001FA200 visual-effect family add 1,512 function bytes:
dispatcher 00119BB8 (476), fading sprites 00119FA0 (504), and orbiting sprites
0011A3D8 (532). The shared sixteen-byte slot and sprite packet layouts transfer
from already matched source. Reusing the actual output parameter as the
advancing packet cursor resolves the dispatcher; its complete 32-byte emitted
switch table and four-byte text alignment are independently exact. Computing
the real per-iteration period in an ascending loop resolves the fading sprite
routine. The orbit routine retains both float operations in one sequenced
comma expression; the verified SN debug profile then avoids an extra assembler
FPU scheduling nop without changing either calculation or introducing a dummy
operation. Formatting and the actual unused third argument retain every byte.
Its four-byte natural text alignment is included in verification, not function
credit. Evidence: work/parallel_effect_family/README.md and exact.json; full
transaction: work/astra-20260910/effect-family-promotion.log.

Work packets now include matched sources that reference the target's globals,
with line-numbered source hits, function names, and compiler profiles. This
complements opcode similarity: an interrupt callback can provide relevant
declarations despite having very different instructions from a foreground
request. The NCMD gate example immediately exposes the existing callback's
semaphore qualifier. These are review pointers, not automatically inferred
types or translation-unit ownership. A regression test excludes unreviewed
source files, handles stale ledger paths, and groups shared source units.
The existing Kaze tools and [m2c's source-context workflow](https://github.com/matt-kempster/m2c)
support this emphasis on recovering declarations before exploring source shapes.

## One-byte provider and raw fragment preservation

Standalone 001271F0 adds 128 function bytes plus its separately verified,
directly used one-byte state provider D_001EC8D4. Signed/unsigned and
definition/extern experiments establish the relevant compiler context; no
neighboring function or global is grouped into this source. Its original
wider translation-unit boundary remains provisional. Existing setter 00127270
retains all 56 bytes after its declaration is made consistently signed, earning
no additional function credit.

Three failed promotion attempts correctly rolled back before exposing the
splitter defect: pinned spimdisasm converts data to whole words, omitting a
separate three-byte raw fragment. An unaligned larger fragment also changes
word grouping and cannot satisfy native placement. The new narrow split helper
preserves only explicitly configured one-to-three-byte raw sdata fragments as
byte assembly from configure.py's authenticated image. The D_001EC8D5..D8 tail
remains raw, with NON_MATCHING markers and alignment one; the aligned remainder
begins at D8. No padding or extra source ownership is claimed. Eight tests cover
labels, collisions, unsupported spans, payload disagreement, and a real MIPS
link with no gaps. The subsequent complete promotion passed every gate:
work/astra-20260910/signed-state-promotion.log. There are now ten small-data
symbol claims. See docs/data-ownership.md and work/parallel_raw_fragments/README.md.

Uncredited frontiers remain explicit. The 1,160-byte animation decoder
00153E88 is reconstructed but not near a byte match. Two further effect
siblings remain unmatched. Directory-open 0019DF60 has six differing words;
RPC bind 0019F518 has three. NCMD/SCMD gate candidates demonstrate further delay
transfers but are not promoted in this pass: the NCMD volatile-state inference
has an existing matching completion declaration and interrupt-style service
calls, but its proposed retail registration chain was disproved. The separate
0x80000012 registration does not point to that completion routine. SCMD lacks
even the same interrupt-side evidence. Their exact candidate bytes alone do
not settle that semantic review. Complete evidence and corrections are under
work/parallel_cluster_shortlist.

## Libpad, remaining effects, and actual return contracts

The following pass promoted **13 functions / 3,428 function bytes**, reaching
**1,398 / 2,189 functions and 225,044 / 663,704 function bytes**. Campaign gains
are **164 functions / 61,284 bytes** from the original checkpoint. All 185
tests, full loaded image and memory extent, independent baseline, progress,
and repository gates passed. Transaction log:
work/astra-20260910/pad-effect-rpc-promotion.log. Machine checkpoint:
work/astra-20260910/pad-effect-rpc-checkpoint.json.

Ten libpad functions contribute 1,804 bytes. Public protocol descriptions and
retail access patterns establish the older 128-byte DMA record with four
actuator records and four combination records, and the 28-byte per-slot state
with four slots per port. This differs from the modern SDK layout. Two info
queries matched their first compile; the same structure then transferred to
the DMA-record selector, frame/read/state/request helpers and mode query.
Natural if/else record selection and an early-return state check resolve the
remaining branch shapes without volatile qualifiers or forced locals. The
initializer uses two actual countdown delays and compiler G0 for its external
scalar flags; assembler-only G0 did not match. Its version checks and actual
mode forwarding are retained. The existing 156-byte port initializer now
accepts that unused mode argument without changing any bytes or receiving
extra credit. All ten new objects emit only their complete text ranges.
Evidence: work/parallel_runtime_cluster_next/README.md, exact.json and
initializer-exact.json. The public SDK is protocol evidence, not a claim to
have recovered the proprietary original source.

Two further visual-effect functions add 1,172 bytes. Table-driven sprites
0011A820 (612 bytes, plus four independently verified native alignment bytes)
match when the actual modulo expressions remain in their sprite fields.
The line effect 0011A5F0 (560 bytes) initially differed by two setup words.
Correcting its helper 00158908 from a false void declaration to the existing
definition's actual integer return resolves both. A controlled reversal of
only this return declaration restores the two differences; replacing signed
coordinate shifts with multiplication by sixteen is byte-identical. The final
sources retain the readable arithmetic and actual helper argument contracts.
Evidence: work/parallel_effect_family_next/README.md and exact.json.

RPC execution 0019BC78 adds 452 bytes. It invokes the actual registered server
callback, prepares its completion packet and up to two DMA descriptors, and
retains both command retries and the real DMA retry countdown. Encoding DMA
addresses as unsigned 32-bit words resolves descriptor allocation and ordering;
these are actual hardware packet addresses and are not dereferenced through
their integer representation. The final five header words resolve after
correcting the interrupt-enable helper's return contract. Independent retail
inspection shows 001A0828 explicitly returns the previous enable flag at both
exits and 001A0870 returns the normalized old bit in its return delay slot.
Both declarations are now int in this source. No qualifier or scheduling
operation was introduced. Full source, zero-data section and return-contract
proofs are in work/parallel_rpc_exec and work/astra_rpc_exec_contract.

Packets now complement shared-global context with direct matched-callee
references, including provider paths, profiles and line-numbered source hits.
This avoids silently retaining obsolete prototypes from older candidates.
A regression test verifies that the actual provider is shown rather than an
unreviewed caller declaration. The tool does not infer contracts for indirect
or unmatched callees. work/astra-20260910/callee-context-effect.json demonstrates
that the previously missed integer-returning helper is exposed directly.

Bounded unsuccessful work remains available without credit: event tick
001382D0 still has 12 differing words and an assembler macro-delay warning;
the IEEE rounding helper 00199F80 retains its source-lifetime/register
frontier; effect siblings 00119D98 and 0011A198 remain unmatched. A directly
adjacent RPC queue contract check did not solve its separate size difference.
Their negative experiments are preserved under work/astra_record_tick_next,
work/astra_float_round, work/parallel_effect_family_next and
work/parallel_rpc_exec. These failures do not erase the completed family gains
or change the full denominator.

### September 10: fresh point-effect and SDK family transfer

The next complete transaction adds ten functions and 4,064 function bytes,
reaching 1,408 / 2,189 functions and 229,108 / 663,704 function bytes. All
970,772 loaded-image bytes remain identical to retail, including the existing
PT_LOAD memory extent. The independent baseline, 185 tests, data ownership,
generated progress and repository audit pass. Evidence is recorded in
work/astra-20260910/fresh-effect-sdk-checkpoint.json and its promotion log.

Four new effect functions account for 2,496 bytes. The recovered 48-byte Point
record contains a naturally aligned vector, color channels and radius. Five
start/end pairs yield the constructor/renderer family's 496-byte records;
single pairs yield two neighboring renderers' 112-byte records. Actual GIF
register-before-data initialization resolves their shared setup schedule.
The two 688-byte functions and their three already-matched middle functions
compile together to 1,552 text bytes and 144 read-only bytes. This grouping
has concrete section evidence: the standalone constructor's 128-byte section
would overlap the renderer table at offset 120; together the real local arrays
and switch table naturally occupy the exact 144-byte section. Nothing is
cropped or filled by source padding. The three previous providers are retired
once, and original translation-unit boundaries remain provisional. The two
standalone renderers contribute 564 and 556 function bytes, with four native
alignment bytes each verified separately. See work/parallel_game_family_fresh
and work/parallel_game_family_pair for source and section proofs.

The renderer callers expose a useful contract correction: transform helper
0011FA48 receives a full 32-bit owner and truncates it before its lookup call.
Its previously inferred unsigned-short public parameter would change caller
loads. Correcting only the existing helper definition to int preserves every
one of its 140 bytes. Callback removal uses its existing generic function
pointer interface with an explicit cast; no incompatible declarations remain
in the new unit. This adds no separate match credit.

Libpad reuse produces another 556 bytes across port close, direct actuator
control and button-mask retrieval. The actual command-buffer DMA lifecycle
supports the fields and return contract, and unsigned 64-bit intermediates
preserve the mask's shifts without signed overflow. Fresh SIF family work adds
344-byte get-other-data and 308-byte send-command functions. Reordering four
real packet/descriptor stores resolves the sender's last three differences;
the range predicate uses unsigned arithmetic before subtraction. Neither
family introduces qualifiers, fake operations or emitted data. Evidence is
in work/parallel_libpad_ports, work/parallel_rpc_family and
work/astra_sendcommand.

The complete 360-byte decimal formatter and its 48-byte literal pool match
with native double arithmetic and a local for the actual computed digits.
This keeps the format pointer out of the preceding calculation's lifetime.
Retail first converts the scaled value to an unsigned integer, then passes
its raw bits to 00199F80, whose exponent check returns zero for ordinary
scaled inputs. The apparent retained formatting bug is preserved. Its helper
is still uncredited: the new integer-input draft matches its first 136 bytes
but has a four-byte return-scheduling difference and an unresolved shift edge
case outside the observed caller range. See work/astra_decimal_scale and
work/parallel_199f80_integer.

Other bounded negatives are retained without restarting the same search:
0019AF20 has 19 differing words in pool setup, libpad open/alignment still have
allocation differences, and correcting the two remaining old false-void IRQ
declarations did not improve 00199B80 or 0019BA28. These results are recorded
in the respective lane READMEs and work/parallel_irq_contract_transfer.

Before publishing this checkpoint, existing wrapper00158A00 was corrected
to declare and forward its real third matrix-output pointer to00133628.
The callee consumes that argument and the particle-family callers explicitly
supply it; the previous two-argument draft happened to preserve physical a2.
All60 bytes remain identical under the existing profile, and the complete
transaction passed full-image, baseline and185-test gates again. This
semantic correction adds no function credit. Evidence is in
work/parallel_game_family_particles/helper_proof.json and
work/astra-20260910/matrix-contract-promotion.log.

### September 10: emitter, polygon and GS family checkpoint

Three further full transactions add 13 functions and 6,308 function bytes,
reaching 1,421 / 2,189 functions and 235,416 / 663,704 function bytes. All
970,772 image bytes and the PT_LOAD memory extent remain exact. Independent
baseline, 185 tests and all public gates pass. The source hashes and transaction
logs are recorded in work/astra-20260910/particles-polygon-sdk-checkpoint.json.

The largest gains come from three complete emitter functions: 00106AE8 adds
708 bytes, 00106E48 adds 1,404, and 00107BD8 adds 1,360. Established external
pointer-array declarations preserve real reload behavior without qualifiers.
The recovered 6,464-byte and 2,928-byte emitter layouts share 64-byte particles.
Signed random-pair expressions, texture-frame locals, saved screen-y and shared
fade calculations transfer directly. The second initialization loop in
00107BD8 actually overwrites velocities in the first pool; the source preserves
and comments on that behavior. No source-owned data is added.

The geometry chain adds 684-byte 001251E8 and 468-byte 00120118. A natural local
interpolation divisor, separate from the loop-bound parameter, recovers the
first function's register and stack lifetimes. The polygon emitter keeps real
scaled radii before trigonometric calls, constructs actual tag fields in a
local, and derives its vertex pointer after advancing the packet. Its integer
degree division and separate single-precision operations match retail exactly.
The two full ranges include eight verified native alignment bytes, which are
excluded from function-byte credit. Proofs are in work/astra_point_geometry
and work/astra_polygon.

SDK family transfer contributes another 1,684 bytes: three pressure-mode
wrappers, two RPC handlers, command initialization, GS reset and vertical-blank
field retrieval. Ordinary 32-entry initialization loops and explicit 32-bit
uncached receive addresses match the SIF initializer. The GS routines use
genuine volatile 64-bit hardware accesses and the actual unsigned-64 return
and parameter contract of GsPutIMR. No ordinary software state gains speculative
volatility. The lane READMEs retain primary SDK references and retail-specific
behavior differences.

The 2,280-byte 001081E0 candidate is deliberately held despite exact bytes.
Its proposed scratch vector only receives two initial zero stores, with no
later reads or pointer escape. The neighboring emitter's real position vector
does not establish this local object's provenance. A complete stack-access
census and exact artifact are preserved in work/parallel_game_family_random;
the source is excluded from its ready list and receives zero credit. Three
DMA routines likewise remain uncredited because their volatile-access schedule
does not match under the checked historical profiles. The RPC client remains
two stores away after bounded ordering and actual pointer-type probes.


## Chain, wave-board and scalar matrix family checkpoint

The next verified checkpoint is **1,432 / 2,189 functions and 242,756 / 663,704
function bytes**. This pass adds eleven functions and 7,340 bytes; the campaign
has added 198 functions and 78,996 bytes from its original ledger. All five
promotion transactions passed the full 970,772-byte image, independent baseline,
185 tests, progress/scope checks and repository audit. The loaded-image SHA-256
remains unchanged. Proof: work/astra-20260910/chain-wave-matrix-checkpoint.json.

The game-family lane contributes 5,868 bytes across five functions. Chain
initialization/rendering (0010DD30/0010E290) share a 48-byte header and eight
0x660-byte effect records; the allocator's 0x3330 bytes prove this arrangement.
Both complete reconstructions matched on their first compile. The 1,208-byte
00110D70 respawning sprite renderer also matched on its first reconstruction,
using the existing 0x1320 emitter and 48-byte particle layout. Its real Sprite
object has a retail-uninitialized depth field, preserved and documented; every
other local object has direct dataflow.

The larger breakthrough is the 2,296-byte 001114F8 wave renderer plus its
468-byte 00111DF0 normal builder. Their 0x990-byte Board contains two 10x10
float grids and a naturally aligned 10x10 vector grid. The renderer preserves
the actual eight-neighbor spring accumulation and emits two quads per accepted
cell. Normal generation calls the existing cross/normalize primitives and
scales the resulting vectors by 496. The helper matched on its first complete
compile; the renderer needed the established debug assembler profile's two
native FPU hazard nops and the real scalar-local declaration order. The normal
builder writes 9x9 entries while rendering reads boundary endpoints inside the
10x10 allocation; no invented initialization hides that retail behavior.

This evidence also removes the old constructor's opaque 401-word region in
favor of the real grid and natural alignment. Its caller now uses a consistent
parameter order and actual position/color arrays. Separate float/integer EABI
register banks had allowed incompatible declarations to emit identical calls.
All 336 bytes of the existing constructor/control unit and 116 caller bytes
remain exact under their original configurations. These source corrections
receive no additional function or byte credit.

The scalar math lane found three ordinary C builders within a mostly VU region:
camera inverse, normalized light directions and projection/screen transform,
628 bytes total. Actual local vectors/matrices explain the frames and all
primitive arguments were checked against retail. Existing VU callees retain
their original status. Three SDK routines add 844 bytes: media-mode command,
memory-card initialization/version checks and callback-thread initialization.
Their public protocol families provide useful context while retail determines
actual error behavior, delay endpoints and kernel call contracts.

The projected polygon 001202F0 is saved at 624 emitted bytes with 17 differing
instructions, down from its first 608-byte draft. Positive clipping conditions
and the actual angle-calculation position account for that improvement. Its
remaining division/store and tag-register scheduling remains uncredited;
bounded probes are appended in work/astra_projected_polygon/results.jsonl.
The uncredited scalar shadow builder and CDVD callback worker likewise retain
negative source-shape evidence to prevent repeated searches.


## Particle motion, heap source context and TTY checkpoint

The verified ledger is now **1,441 / 2,189 functions and 247,120 / 663,704
function bytes**. This pass adds nine functions and 4,364 function bytes;
cumulative gains are 207 functions and 83,360 bytes. Four complete promotion
transactions passed all gates, including 185 tests, independent baseline and
the unchanged 970,772-byte loaded image. There are eleven reviewed small-data
claims after adding one actual four-byte initialized object. Proof is retained
in work/astra-20260910/particles-heap-tty-checkpoint.json.

The particle lanes add 3,620 bytes. Four burst/bounce functions (001151B0,
001152F8, 00115490, 00115658) share proved 48-byte and 32-byte records and the
actual packed-color emitter/vector contracts. Preserving the counter store
before its genuine alpha division resolves the burst update. The original
float angle expression and a real PRNG sample retained across trig calls solve
the bouncing initializer. The 912-byte 0010F258 spark initializer transfers the
known 0xC30 emitter with 64 particles and 24-byte integer source records.
The 1,140-byte bone renderer 0010CA70 resolves its final nine words with a real
branch-local alpha value initialized to 64 and then reduced by its decay
fraction. A shared alpha across branches was worse; no extra operations or
qualifiers were used. Full native text, including actual alignment where
emitted, was independently compared.

The 284-byte heap-gap clearer 00151CD8 was initially eleven words away under
GNU assembly with a provisional incomplete-array arena declaration. Restoring
the real scalar arena pointer and using the native assembler reproduces its
absolute load. The remaining list-head access becomes the actual GP load when
its real initialized scalar D_001ECBD0 is supplied in the C source. The entire
four-byte .sdata contribution is FFFFFFFF, independently matching retail and
the empty-list sentinel semantics in existing initialization/removal code.
It has one reviewed provider and fills an exact Splat gap; the neighboring
tail sentinel remains in assembly. All 288 emitted text bytes and four data
bytes match. This explains a source/assembler context difference without an
invented array extent or relabeled section; the full original TU boundary
remains provisional. Evidence: work/astra_heap_clear/README.md.

The 208-byte DECI2 TTY reader uses count-only volatility. Actual retail passes
the real handler and TTY object through DECI2 registration operation 1 and
syscall 0x7C. That registered handler increments the same availability count
on input; the reader waits on it and decrements it on consumption. The pinned
[primary PS2SDK queue implementation](https://github.com/ps2dev/ps2sdk/blob/d1a988c22595f4623e42cfe1c1e23aafb7965dc8/ee/kernel/src/tty.c#L68-L92)
independently documents the user-thread/handler producer-consumer context.
Only that field is qualified. Whole-TTY qualifier experiments and the remaining
handler/init drafts are explicitly excluded. The complete audit, actual
registration addresses and immutable references are in
work/parallel_tty_family/README.md.

Fresh endpoint-emitter analysis adds its 252-byte setup 0010AA50. The actual
cached header and strand pointers remove redundant initial reloads while the
vector-copy calls retain their real shared-pointer reads. Its original
PRNG-result-times-ten delay is preserved, not changed to modulo ten. The
existing 60-byte caller now describes both input offsets as float vectors and
uses a compatible declaration; all its bytes remain exact with no additional
credit. The 1,872-byte renderer 0010AB90 is a saved uncredited draft. Its
hardware sqrt fallback targets the verified double wrapper, unlike the normal
single-precision helper. A proper double-call compiler probe does not produce
the retail sequence. No wrong library alias or fabricated prototype was added
to hide this unresolved source/ABI context.

The projected renderer 001205F8 remains three register instructions away after
bounded root coordinate/packet/callback-declaration probes; its entire switch
table still matches. The spark renderer and allocator search also remain
uncredited. All negative sources and measurements are retained for subsequent
work instead of repeating the same probes.


## Spatial sound, jitter sprites and environment layout

Two spatial sound siblings, 00179470 and00179660, matched on their first complete
reconstructions (864 bytes). Their shared44-byte sound descriptor, camera transform,
normalization, three-point attenuation and existing truthful sqrtf fallback transfer
directly; the sole command difference is the extra integer argument. There is no
new library alias. The jitter sprite renderer001065B0 also matched on its first
complete reconstruction (1008 bytes); its76-byte control uses the actual0/1/default
switch and emits four natural alignment bytes. All actual sprite/vector objects are
consumed, and the persistent age increment and clip-dependent fade behavior remain.

These four functions passed the full transactional import at1445/2189 functions
and249068/663704 function bytes. Local evidence: work/parallel_spatial_audio_next/
and work/parallel_game_family_jitter/, with full gate output in
work/astra-20260910/jitter-spatial-promotion.log.

The one-element pointer declarations in the emitter sources explicitly represent
one four-byte pointer slot. This is a C storage representation supported by actual
allocator stores, subsequent pointer loads and neighboring separate globals; it is
not evidence of the original array spelling or of a larger object/TU. Scalar and
incomplete-array diagnostic forms are retained with their different compiler
aliasing/load results. No additional storage, definitions or qualifiers are added.

The1,196-byte environment initializer001217A8 now verifies all1,200 emitted bytes.
Its actual0x6300 allocation gives40 six-vector trails,200 two-vector particles,
26x23 height/velocity/normal grids, and five seven-vector columns. Independent
00123A90 normal reconstruction confirms both grid strides and the25x22 interior
bounds; direct shared fields give its full448-byte match. The leading16 bytes are
integer RGBA from14D778, confirmed in the consuming renderer. Actual overwritten
randomized fields and calls remain in the initializer. No new data provider or
volatile declaration was introduced. The related123658 renderer does not improve
with the same bounded storage representation, so its prior frontier stays uncredited.

The96-byte effect-record initializer00133990 also resolves completely (1204 bytes
plus4 natural alignment). Its actual pointer slot is independently established by
allocation, destruction and the separate following global. Real chained coordinate
assignments restore the final three paired store orders. The268-byte sixteen-ring
initializer0010B338 matched on its first reconstruction using its independently
allocated256-byte record, actual16-byte vector copies and signed RNG expressions.

Larger related renderers remain uncredited. The121C80 review finds an unsupported
legacy stack vector with no consumer, plus the unresolved double-wrapper sqrt
fallback; typed layout transfer does not solve it. In134570, retail initializes
four stack color words but never reads or passes them; its actual packet uses
literal colors. An invented unused C object is not accepted to fill those bytes.
114810 and10B488 retain complete ordinary-C drafts with measured schedule/register
mismatches. These source and dataflow holds are preserved for new evidence, rather
than counted because portions of the code or nominal sizes agree.


## Ellipse, camera geometry and card-menu family transfer

The ellipse interpolation/renderer pair0010C2F0 and0010C570 matched on their first
complete reconstructions:1084 function bytes and four natural alignment bytes.
The actual96-byte emitter produces two aligned48-byte endpoints, whose position,
color and size fields are consumed by interpolation. Four vector differences are
part of the real vector loop; all RGBA differences and XYZ drawing values are used.
The final ellipse helper call uses the existing integer/float/stack argument contract.
Full promotion passed at1451 functions and253264 function bytes.

Camera projection/clip/viewport builder001010B8 preserves the actual four-pointer,
nine-float interface and every floating-point evaluation order. Its628 function
bytes plus4 native alignment use the independently documented debug-statement
Ps2EeAs division-hazard profile. Two real viewport coefficient locals restore the
final assembler hazard boundary without any source padding. The352-byte listener
update00101330 uses the existing extracted-bit convention and a real four-short
event packet, independently consumed in full by138468. All real matrix/vector and
short-array objects are used; no dead scratch is introduced.

The1,176-byte card-menu controller001505C0 also matched on its first complete C
reconstruction under the established GNU-assembler G8 profile. Its entire104-byte
read-only section contains three generated switch tables and their natural internal
gap, all independently exact. Device/status/button contracts, signed error cases,
simultaneous button handling and the state3 reset-without-early-exit asymmetry remain.

Fresh layered-grid renderer00125618 is saved at1600 emitted bytes with40 differing
words. The remaining UV calculations hoist a row multiplication differently from
retail. A real four-byte initialized frame counter is independently exact in the
ignored object, but no public ownership or match is claimed. Independent bounded
menu-transition0017AC08 arithmetic/reset probes did not improve its eight-word
register frontier. Both complete drafts and negative results remain available.
