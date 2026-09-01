# Adversarial audit — Chulip matching decompilation

**Date:** 2026-09-01 · **Lane:** `work/lanes/claude_audit` · **Mode:** read-only
**Machine-readable findings:** `work/claude/audit-findings.json`
**Frozen inputs:** `work/lanes/claude_audit/snapshot/` — the live ledger moved from
793 entries / 49,124 bytes to 819 / 53,012 during the four minutes I was measuring it
(15:53 → 15:57). Every number below is against the frozen copy. Another session is
writing the tree; treat all figures as of that snapshot.

**Standard audited against** (`docs/knowledge-book.md` §1): readable C expressing the
recovered behaviour; isolated byte match; compiler, flags, assembler behaviour and unit
boundary supported by local evidence; complete-image rebuild reproducing 970,772 bytes.

---

## Verdict in one paragraph

Gate 2 (isolated byte match) and gate 4 (whole-image rebuild) are solid — the tooling
around them is genuinely good, and the padding/range bookkeeping is clean. Gate 3
(compiler, flags, unit boundary supported by local evidence) is **not met for most of
the ledger**, and the project's own metric for it measures the wrong thing. Gate 1
(readable C) is met for roughly half of the machine-recovered work and not for the rest.
The honest reading of "819 functions matched" is: 819 functions whose bytes are right,
of which about 160 have been co-compiled with a neighbour, none have a proven object
boundary, and about 630 carry a compiler attribution that no test discriminated.

Nothing here is fraud. Everything here is the same failure the previous project hit,
caught at 819 functions instead of 2,000. The good news is that the fix for the largest
finding has already been prototyped inside this repo and not yet landed.

---

## Ranked findings

Ranked by **cost if discovered at 90% completion rather than now**, not by severity.

| # | Finding | Severity | Functions | Bytes | Cost if deferred |
|---|---|---|---:|---:|---|
| F2 | Adjacent functions carry configurations that cannot both be true | critical | 284 | 18,672 | Highest — cascading rewrites |
| F1 | 658 of 819 matched functions are one-function islands | critical | 658 | 46,780 | Very high — gates F2 |
| F4 | Fabricated data declarations contradicted by the repo's own data | high | 116 | 7,344 | Very high — makes F1/F2 expensive |
| F3 | Compiler/flag attribution recorded but never established | critical | ~631 | ~40,800 | High — invalidates the evidence model |
| F5 | Machine-shaped source that matches but isn't readable | high | 265 | 16,736 | Moderate — linear, no cascade |
| F6 | 94.5% of the image is still blob-supplied | high | — | 917,760 | Moderate — known-unknown, not rework |
| F9 | Published metrics overstate the evidence | medium | 819 | 53,012 | Free now, a retraction later |
| F7 | Symbol aliases | low | 2 | 32 | Trivial now; guard has been removed |
| F8 | Padding and unit-range claims | **clean** | 0 | 120 | n/a — false alarm |

---

## F2 — Configurations that cannot both be true (worst deferred cost)

**109 adjacency edges** inside gap-tolerant matched runs join two functions with
different recorded build configurations. A run is gap-tolerant when consecutive matched
functions are separated by 0 or 4 zero bytes — and `work/lanes/claude_units2/NOTES.md`
independently establishes that 965 of the 968 inter-function gaps in the whole image are
exactly four zero bytes of assembler alignment. These are not object boundaries; they
are functions inside one object being told they were built differently.

| Collision | Edges |
|---|---:|
| `-G8` vs `-G8 -Wa,-G4` | 52 |
| **Sony `ee-gcc2.9-991111-01` vs SN `ee-gcc2.95.3-136`** | **20** |
| `-G8` vs `-G8 -Wa,-G0` | 15 |
| `-Wa,-G0` vs `-Wa,-G4` | 5 |
| `-G8` vs `-mno-split-addresses` | 4 |
| ps2as / `-mcpu=4000` combinations | 13 |

The 20 SN↔Sony edges are the sharpest. Two different vendors' compilers, touching across
a zero or four-byte gap:

```
0x0018FFC0 func_0018FFC0  Sony | gap 0 | 0x00190000 func_00190000  SN
0x00190000 func_00190000  SN   | gap 0 | 0x00190030 func_00190030  Sony
0x001924C0 func_001924C0  SN   | gap 0 | 0x001924C8 func_001924C8  Sony
0x00192568 func_00192568  SN   | gap 0 | 0x00192598 func_00192598  Sony
```

`func_00190000` alternating between vendors on both sides is not an object interleave.
It is an undetermined attribution (see F3) presented as a compiler finding.

**The fix is already prototyped and not landed.** `work/claude/units2.jsonl` holds 323
functions merged into 119 multi-function units, every range re-verified. I checked it
against the ledger: **all 323 are still recorded as one-function islands, and exactly 90
of them change configuration once compiled together** — matching the lane's own claim.
Eight per-function configurations collapse to four per-unit ones; `-Wa,-G0` (15→0),
`-Wa,-mcpu=4000` (2→0) and ps2as+`-Wa,-G4` (4→0) disappear entirely.

**Remediation:** treat a configuration collision on a zero/alignment edge as a defect.
Merge the run, keep the one configuration that reproduces the whole range, rewrite the
losing side. Add a gate to `merge_candidates.py` refusing a new island whose immediate
neighbour carries an incompatible configuration. **284 functions today.**

**Why deferring is the expensive option:** each collision is a latent source rewrite, and
rewrites cascade — unifying one declaration changes codegen for every function in the
run. At ~2,000 matched functions expect ~700 collisions and ~250 forced rewrites arriving
as a wall rather than a queue. That is precisely the previous project's failure.

---

## F1 — Island objects

- **658 of 819** matched functions (80.3%), **46,780 bytes**, are compiled alone in their
  own source file with their own configuration.
- 714 source files for 819 functions. Histogram: 658 files with 1 function, 38 with 2,
  8 with 3, 6 with 4, 2 with 5, one with 10, one with 17.
- `config/splat.us.yaml` carries **713 C subsegments and 377 asm subsegments** — 1,090
  text objects where retail plausibly had one to two hundred.
- **10 distinct build configurations** across 819 functions.
- **602 of 819** matched functions already sit in gap-tolerant runs of two or more, so the
  merge queue exists today. Largest run: **32 consecutive matched functions at 0x001613E8**,
  still 32 separate objects.

**"In proven units" does not mean what it says.** `tools/progress.py:55`:

```python
in_units = sum(count for count in sources.values() if count > 1)
```

A "proven unit" is a source file containing more than one function. No entry in
`config/reconstructed.json` carries positive boundary evidence, and the project's own
`work/lanes/unit_boundary_frontier/REPORT.md` says so plainly: *"No proposed edge received
definitive positive boundary evidence."* So the 161/819 figure is co-compilation, not
proof. That report is careful, well-argued work — the metric built on top of it is not.

---

## F4 — Fabricated data declarations, contradicted by this repository

The `struct S8 { int a; char pad[4]; }` + `-Wa,-G4` device forces absolute addressing by
telling the assembler an object is eight bytes. It produces the right bytes. It is also
provably false about the data, and the proof is inside this repo.

- **93 declaration sites** declare an 8-byte object where the project's own disassembled
  blob records a different size. Blob sizes for those: 4 bytes ×71, 2 ×8, 16 ×5, 1 ×4,
  64 ×3, 12 ×1, 3 ×1.
- Side by side:
  - `asm/data/cod/sbss.sbss.s:33` — `nonmatching D_001ED090, 0x4`
  - `src/game/func_00105EE8.c` — `extern struct S8_int D_001ED090;`
- **88 of those declarations physically overlap another declared symbol.** The worst:
  `D_001ED2D2` is declared as an 8-byte struct in `func_001272D0.c` while `D_001ED2D3`
  is declared **one byte later**. `func_0014FFC8.c` declares `D_001ED438` and `D_001ED43C`
  as 8-byte structs four bytes apart. `unit_00127160.c` declares four 8-byte structs at
  2-byte spacing.
- **68 addresses are modelled with mutually exclusive sizes in different files.** Of 450
  distinct extern-declared address symbols, 114 have more than one declaration spelling:
  68 size-class conflicts, 40 same-class type differences, 6 sign/qualifier only.
  `D_001ED098` is `int` in `func_00105E90.c` and `struct S8_int` in `func_00105EE8.c` —
  and those two functions are **56 bytes apart in the same contiguous run**.

**Nothing in the pipeline can catch this.** These symbols live in `.sbss`/`.bss`, placed
NOLOAD at `0x001ED080`. Not one byte of them appears in the 970,772-byte image, so the
full-image gate is structurally incapable of contradicting a false size.

**The section geometry argues against the model.** `config/elf.json` shows `.sbss` at
`0x001ED080` size `0x97C`, `.sdata` at `0x001EC880`, GP at `0x001F4870`. Every one of
these symbols is inside GP range and was placed in *small* BSS by the retail toolchain —
i.e. retail considered them small, which is exactly what the 8-byte model denies. The
likelier explanation for retail's absolute form is a referencing TU whose declaration
carried no size (an incomplete or unsized extern emits no `.extern sym, N`, so the
assembler treats it as large). That hypothesis has a clean spelling and has not been
tried at scale.

**Remediation:** find the real reason and re-spell. Add a checker rejecting any extern
whose declared size disagrees with the blob or overlaps a neighbour. **116 functions.**

**Why this is third-most expensive to defer:** it is the mechanism that makes F1 and F2
costly. Consolidating a run forces one spelling per address, and 68 addresses have no
consistent one today. At 90% the same defect covers ~300 functions *and* 2,000 functions
have been written against a data model known to be false.

---

## F3 — Compiler and flag attribution is recorded, not established

`verified_profiles` records which profiles were **tested**, not which ones **match
uniquely**. I sampled 70 functions at random (seed 101) from the 743 entries listing
exactly one profile, and re-ran each against three other historical profiles:

- **54 of 70 (77%)** also byte-match under at least one other historical compiler.
- **71% of sampled bytes** are non-discriminating.
- Alternates that also match: `ee-gcc2.95.3-136-O2` (`-G0`) ×42,
  **`ee-gcc2.95.2-273a-O2-G8` — a different compiler generation — ×31**, `273a-O2` ×19.
- Not just stubs: `func_0010BF20` (548 B), `func_00112FD0` (316 B), `func_00135BD8` (120 B).

Extrapolated: **~631 functions and ~40,800 bytes carry a compiler attribution that no
test discriminated.** Gate 3 is unmet for most of the ledger.

Corroborating problems in the same category:

- **93 functions above the 0x00185400 SDK frontier** are recorded with the SN 2.95.3
  profile, although `docs/knowledge-book.md` §3 asserts that region was built by Sony EE
  GNU C. Median size 40 bytes — almost certainly undetermined, not evidence of interleave.
- **The project already knows the flags are undetermined.** `claude_units2/NOTES.md`:
  *"`-Wa,-G4` is usually not determined by the bytes. Several functions recorded with
  `-Wa,-G4` also match with no object flag at all; under the `-ps2as` profile the
  assembler `-G` value made no difference to any unit in this lane."* That finding has
  not propagated into the ledger, which still records 116 functions at `-Wa,-G4`.
- **Two flags no retail build would use.** `-Wa,-mcpu=4000` (2 functions) tells the
  assembler to target an R4000 on an R5900 title. `-mno-split-addresses` (9 functions) is
  a per-function addressing override. Both vanish on consolidation.
- **The Sony profile is a hybrid.** `ee-gcc2.9-991111-01-O2` pairs Sony's `cc1` with the
  **SN 2.95.3 bundled assembler** (`config/toolchains.json`), contradicting the knowledge
  book's own rule that the era-correct bundled assembler is required. 80 functions rest
  on it.

**Remediation:** run the full profile × object-flag grid over the whole ledger and record
the true match set. Where more than one matches, mark the attribution undetermined and
stop citing that function as compiler evidence. Rename the field to `tested_profiles`.

---

## F5 — Machine-shaped source

A full census (not a sample) of the 232 files carrying automated-recovery markers:

| Bucket | Files | Share |
|---|---:|---:|
| CLEAN | 75 | 32.3% |
| COSMETIC (legible, fabricated types) | 112 | 48.3% |
| **OPAQUE (machine transliteration)** | **45** | **19.4%** |

Under a strict reading of §1 — counting `struct S8_*` threshold padding and scalars
subscripted `[0]` as failures, which they are — **OPAQUE rises to ~102 files (44%)**.
Tree-wide hard transliteration is ~48 of 716 sources (6.7%); the flagging heuristics
caught 40 of the 43 tree-wide hits, so the queue is well-identified but under-inclusive.

The ledger under-reports this. `provenance_note` self-declares **214 functions / 6,760
bytes** as symbolic reconstruction; marker analysis finds **265 functions / 16,736 bytes**
— roughly double.

Representative lines that no rename fixes:

```c
func_00172570.c:  return ((unsigned short *)(((arg0 & 255) * 22) + D_001ED790.a))[8];
func_001613E8.c:  ((int *)((arg1 << 2) + arg0))[0] = ((arg2 | (arg3 << 16)) | 1811939328);
func_001613E8.c:  return 1811939328;
func_0010E6D8.c:  ((int *)((arg0 * 1584) + D_001ED158.a))[0] = arg1;
func_0010E6D8.c:  return 1584;
unit_0010A1D8.c:  ((int *)D_001ED0F8.a)[3] = -((int *)D_001ED0F8.a)[3];
func_0010D490.c:  *(float *)(D_001ED144[0] + index * 0x660 + 0x40) = x;
```

`func_00172570.c` stacks three lies to reproduce one `lhu`: a scalar wearing a
`struct S8_int` hat, cast to `unsigned short *`, indexed `[8]` on a stride-22 record.
`return <stride>;` in `func_0010E6D8.c`, `func_00110000.c` and `func_00133E48.c` is a
live register promoted to a return value.

**The biggest single loss is a coherent subsystem.** 28 files across
`func_001612xx`–`func_001618xx` and `unit_001614xx`–`unit_001617xx` are the GS/GIF packet
builder, decompiled into unnamed decimals — `1811939328` is `0x6C000000`, `805306368` is
`0x30000000`, `268435456` is `0x10000000`. Named tag constants and a packet struct would
make the whole subsystem legible at once; nothing else will.

Caveat that cuts the other way: 60 of the 75 CLEAN files are one-line setters like
`D_001ED098 = arg0;`. They pass because there is no behaviour in them to get wrong. And
the control set is not clean either — `func_001863A8.c`, never flagged, is a
`goto zero / goto classified / goto saturate / goto convert` chain reproducing the branch
layout verbatim.

**Lowest cascade risk of the critical findings** — each rewrite is local and
independently re-verifiable. But it scales linearly and the ledger's own provenance note
hides half of it.

---

## F6 — Data ownership

**94.54% of the 970,772-byte loaded image comes from disassembled blobs.**

| Section | Bytes | Share of image | From C |
|---|---:|---:|---|
| `.text` | 667,648 | 68.8% | 53,012 (7.94% of the section) |
| `.data` | 274,484 | 28.3% | 0 |
| `.rodata` | 24,096 | 2.5% | 0 |
| `.sdata` | 1,940 | 0.2% | 16 (`camera_motion.c`) |
| `.vutext` | 2,384 | 0.2% | 0 |

**302,904 bytes — 31.2% of the image — is non-`.text` data that no one has attempted**,
and it appears in no published denominator. `docs/scope.md`'s 663,704-byte denominator is
text-only and never says so.

**Jump tables are pinned but blob-supplied.** 94 tables, 14,568 bytes, 60.5% of `.rodata`.
`tools/build.py:pin_jump_tables` removes the compiled object's `.rodata` from `.cod` and
places it in a private `.jtbl_*` output section *outside* `.cod`; `objcopy -j .cod` then
extracts an image whose table bytes came from the blob. To the project's credit,
`verify_jump_tables` does compare the compiled table against retail bytes — so the table
is **proven equal**, just not the copy that ships in the verified image. Three are pinned
today; 83 functions and 145,932 text bytes remain blocked behind this.

Related: `derived_symbols` defines 13 `.LXXXXXXXX` branch labels at the address embedded
in their own name, so the blob's jump table resolves its targets after the surrounding
function becomes C. The blob table therefore points at retail addresses regardless of
what the C object's block layout actually is.

**Remediation:** publish a second denominator over the full loaded image and decide
explicitly whether `.data`/`.rodata`/`.sdata` are in scope. If they are, that is a
302,904-byte workstream that has not started. This invalidates no existing function — it
is a known-unknown, not rework — but if it stays undeclared the project reaches "100% of
functions" with a third of the executable never decompiled, and the scope argument
happens at the worst possible moment.

---

## F7 — Symbol aliases (narrow, but the guard is gone)

Only **two** alias symbols exist tree-wide: `A_001ED88C` and `A_001ED890`, both in
`src/game/unit_0017ABE8.c`, plus 13 `.L` branch labels. That file declares one address
twice under two names to get two addressing modes:

```c
struct Pair { short value; short pad; int rest; };
extern struct Pair A_001ED88C;
extern int D_001ED88C;
...
short value = A_001ED88C.value;
D_001ED88C = 0;
```

The blob says `nonmatching D_001ED88C, 0x4`, so `struct Pair` is the same fiction as F4.
This models no data layout; it is a codegen switch wearing a type.

**The protection has been removed and the brief is stale.** `work/claude/AGENT-BRIEF.md`
still tells workers *"Symbol aliases such as `A_001ED88C` … have no definition in the
whole-image link, so they FAIL integration. Do not use them."* That is no longer true:
`tools/build.py:derived_symbols` now defines any undefined symbol ending in eight hex
digits, and `tools/match.py:write_derived_symbols` does the same in isolation. An invented
symbol name can never fail verification.

Clean by contrast: `build/undefined_syms_auto.txt` defines pseudo-symbols for immediates
(`D_FFFF`, `D_80000000`, `D_20000010`). **No C source references any of them.**

**Remediation:** restore the guard deliberately — reject any source symbol not in the
disassembly's symbol set — and fix the two aliases with F4. Two functions today; the risk
is the removed guard plus a brief that documents protection that no longer exists.

---

## F8 — Padding and unit-range claims: CLEAN

**This is a false alarm and I want to say so plainly.** I checked every one of the 162
entries carrying `unit_start`/`unit_end`:

- **120 bytes** across all extended ranges are not covered by a matched function.
- **Every one of those 120 bytes is zero in the retail image.** Zero non-zero bytes.
- 116 are 4-byte inter-function alignment words *inside* a unit; 4 are trailing.
- **Zero** overlapping unit ranges between source files.
- **Zero** claimed ranges silently covering an unmatched catalog function.

The discipline behind this is real: `claude_units2/NOTES.md` independently establishes
that 965 of 968 inter-function gaps are exactly four zero bytes, and that trailing padding
is a property of the object that must be probed at both ends (`func_00154638` verifies
only *without* trailing padding; `func_00129040` verifies only *with* it). Keep that
practice. Nothing to fix.

---

## F9 — Published metrics overstate the evidence

- **"In proven units"** counts shared files, not proven boundaries (`progress.py:55`).
- **`verified_profiles`** counts tested profiles, not matching ones — 77% non-discriminating.
- **`docs/scope.md` is stale**: it publishes 714 matched / 36,344 bytes / 5.48% while
  `scope_scan.py` on the same tree reports 819 / 53,012 / 7.99%. The page correctly says
  the tools are the source of truth; the table still gets quoted.
- **README** publishes 8.0488% with the caveat that only readable byte-matching C counts.
  It does not surface the 80% island ratio, which is the number a reader most needs.
- **The ledger moved during this audit** — 793 → 819 entries in four minutes, with another
  session writing `config/`. Any figure quoted without a snapshot is unreproducible.
- **The easy tail is being harvested.** 165 of 819 matched functions are ≤16 bytes and 108
  are ≤8 bytes; matched median is 48 bytes against a catalog median of 108 and mean of 303.
  That is a reasonable strategy, but the function percentage will decelerate hard, and the
  ~500 remaining large functions carry all of the unresolved structural questions above.

---

## What I would do next, in order

1. **Land `units2`.** 323 functions, 119 units, already verified, still sitting in a lane.
   It removes 90 arbitrary configurations and eliminates four of ten build configurations.
   This is the single highest-value action available and it is mostly already done.
2. **Gate new islands.** Make `merge_candidates.py` refuse a candidate whose immediate
   neighbour carries an incompatible configuration. Stops the problem growing while the
   backlog is worked.
3. **Run the full profile grid** over the whole ledger and record true match sets. Until
   then, no function should be cited as compiler evidence in `docs/knowledge-book.md`.
4. **Resolve the small-data addressing question honestly.** Test the unsized/incomplete
   extern hypothesis against the `-Wa,-G4` fiction. Add the size/overlap checker either way.
5. **Rewrite the GIF/DMA packet cluster** (28 files) with named tag constants. Biggest
   readability win per unit of effort in the tree.
6. **Publish a whole-image denominator** and state whether `.data`/`.rodata` are in scope.
7. **Fix the metric names** (`co_compiled_functions`, `tested_profiles`) and regenerate
   `docs/scope.md`.

Items 1, 2 and 7 are days. Items 3–6 are the difference between finishing this project
and redoing it.
