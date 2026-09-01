# Chulip matching knowledge book

This is the curated, human-readable companion to the append-only
`matching-knowledge.jsonl` ledger. It records facts that should change how the
next function is reconstructed. Function-specific discoveries belong in the
ledger first; this book keeps only conclusions that have survived exact-byte
verification or a disciplined negative test.

The project borrows the evidence structure of the Kaze no Notam campaign, but
none of that game's PS1 compiler, ABI, linker, or source-layout assumptions are
treated as evidence for this PS2 executable.

## 1. Acceptance standard

A source function is counted as matched only after four gates:

1. The source is readable C expressing the recovered behavior.
2. The isolated verifier matches every byte in the function or proven source
   unit.
3. The compiler, flags, assembler behavior, and unit boundary are supported by
   local evidence.
4. The source-plus-assembly build reproduces the complete 970,772-byte loaded
   image and its expected SHA-256.

Generated retail assembly is useful reconstruction scaffolding, but contributes
zero decompilation progress. Decompiler output, semantic equivalence, matching
instruction counts, and booting are evidence, not completion.

## 2. Target and ABI facts

- The target is the USA `SLUS_207.42` executable loaded at `0x00100000`.
- The executable uses the R5900/Emotion Engine EABI64 environment and GP
  `0x001F4870`.
- The file-backed load image is 970,772 bytes. Its expected SHA-256 is
  `77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.
- Retail object boundaries use eight-byte input subalignment even when compiler
  objects advertise larger alignment.
- The file-backed small-data region and virtual-only BSS have a proven gap; the
  build preserves the BSS start at `0x001ED080` explicitly.
- Generated R5900 assembly uses numeric general-register names during rebuilds
  because several O32 aliases are invalid or mean different registers under
  the selected EABI.

## 3. Compiler and assembler model

The first discriminating source neighborhood selects SN Systems GNU C
2.95.3-EE build 1.36 with `-O2`. Nearby GP-relative setters prove compiler
threshold `-G8`.

The compiler alone is not the complete toolchain identity. Its bundled GNU
assembler 2.9-ee-991111b is required:

- it encodes the compiler's `move` pseudos as retail `daddu` instructions;
- modern GNU `as` encodes the same pseudos as `or`, creating false mismatches;
- its obsolete `.mdebug` and symbol-table metadata can be removed or rewritten
  by modern `objcopy` without changing text or relocations.

The camera source unit establishes an important mixed-threshold model:
compiler `-G8` with historical assembler option `-G0`. Source-owned small data
still receives retail GP-relative references, while float constants such as
half-pi are constructed inline instead of being moved into `.lit4`.

Do not apply this profile globally merely because a small function happens to
match it. Record every matching profile and establish address-local evidence
before applying a profile to neighboring work.

The complete resource-record unit at `0x00137EA0-0x00137FCC` supplies a second
address-local discriminator. It matches build 1.36 `-G8` and rejects build
2.73a even when that compiler is also run with `-G8`; this separates compiler
generation from the small-data threshold.

### The two-sided small-data threshold

How a global is spelled in C decides its addressing mode, and the decision has
two independent halves. The compiler emits `.extern sym, N` and chooses between
a one-instruction pseudo and an explicit `lui`/`%lo` pair by comparing `N` with
its own `-G`. The assembler then chooses between a GP-relative access and an
absolute `%hi`/`%lo` expansion by comparing the same `N` with *its* `-G`. Two
different thresholds therefore produce three distinguishable retail forms:

| Retail form | Object | Spelling |
| --- | --- | --- |
| `lw $v0, %gp_rel(X)($gp)` | at most four bytes | `extern int X;` |
| `lui $rN,%hi(X)` then `%lo(X)($rN)`, same register | exactly eight bytes, assembled `-G4` | `struct S8 { int a; char pad[4]; }; extern struct S8 X;` |
| `lui $rN,%hi(X)` then `%lo(X)($rM)`, different registers | larger than eight bytes | `extern int X[];` |

The middle row is the one that cannot be reached by any single-threshold
spelling. The compiler believes the eight-byte object is small and emits the
pseudo; the assembler at `-G4` believes it is large and expands it absolutely,
which is exactly the retail `lui $at` store form and the same-register load
form. Genuine four-byte neighbours in the same function stay GP-relative, so
one function can legitimately carry both modes. First proved on `func_0014FF10`
and now carried by a large family of state accessors.

Do not reach for an object larger than eight bytes to force absolute
addressing. Above eight bytes the compiler splits the address itself and shares
the base register across accesses, which never matches retail
(`func_00181EB8`).

### The bundled PS2 assembler is authoritative for delay-slot pseudos

Each SN toolchain ships two assemblers: the GNU `as.exe` the project has been
using, and `Ps2EeAs.exe`. They disagree in one narrow but decisive place.

The compiler emits a bare small-data pseudo such as `sb $2,D_001ED1E1` and
leaves the choice of expansion to the assembler. When such a pseudo lands in a
branch delay slot, `Ps2EeAs` expands it to the single-instruction GP-relative
form, while GNU `as` emits the two-instruction absolute macro and warns "macro
used after `.set nomacro'". Retail contains the GP-relative form.

This is why one symbol can legitimately show both addressing modes inside a
single function: the sites in delay slots are GP-relative and the sites outside
them are absolute, from identical compiler output. `func_00117268` is the
proof; its compiler assembly is already instruction-for-instruction identical
to retail, and only the assembler choice decides whether the bytes match.

The `ee-gcc2.95.3-136-O2-G8-ps2as` profile selects this path. Prefer it
wherever a function shows a symbol in both addressing modes.

### The executable was built by two compilers

Retail spills callee-saved registers two different ways. Below roughly
`0x00185400` it uses `sq`/`lq` on sixteen-byte slots; above it, `sd`/`ld` at the
same sixteen-byte stride. `tools/regime_scan.py` derives the split from the
zero-C baseline: 705 `sq` functions all but two below the boundary, 255 `sd`
functions all above it.

The two regimes are two compilers, not one compiler with a setting we had to
find. Game code below the frontier is SN Systems GNU C. The runtime and library
region above it is **Sony EE GNU C 2.9-ee-991111-01**, which spills 64 bits wide
at a sixteen-byte stride natively. Both SN builds spill 128 bits and cannot
reproduce it; Sony's later 3.2 builds use an eight-byte stride and cannot
either. `func_0018FFC0` is the proof.

This also retires two supposed blockers. Sony's compiler emits frameless sibling
calls, which neither SN build will do at any flag (`func_001856F8`), and it
moves float literals into `.lit4` where SN builds materialise them inline.

An earlier investigation concluded that no stock switch could reach 64-bit
register precision, and proposed a binary patch to SN `cc1.exe`. That analysis
of the SN compiler was correct — `override_options` does force 128-bit
precision whenever the R5900 bit is set, and this `cc1` has no pragma handler
at all — but the conclusion was wrong, because the region was never built by
that compiler. **Do not patch a historical compiler; identify the right one.**

Profile: `ee-gcc2.9-991111-01-O2`. Use it for every function above the SDK
frontier and the SN profiles below it.

## 4. Translation-unit and data lessons

The camera block at `0x001017F0-0x00101CC3` is the first proven multi-function
source unit. Its seventeen functions produce 1,236 exact object-text bytes together;
the linker then contributes four bytes of input alignment before the following
object.

Later camera-area units show why whole-unit proof is the default even for easy
functions. The two snapshot functions produce an exact 320-byte object, four
object helpers produce an exact 216-byte object, and the resource loader plus
empty tail produce an exact 96-byte object. The snapshot copy also proves that
`CameraState` has 16-byte alignment: removing the alignment changes the
compiler's aggregate-copy sequence.

This matters because compiling the functions as convenient isolated objects can
change symbol classification, literal placement, alignment, and register
scheduling even when each C body looks correct.

The same camera source owns the aligned 16-byte small-data block beginning at
`0x001EC880`:

| Address | Recovered value | Current interpretation |
| --- | ---: | --- |
| `0x001EC880` | `-999.0f` | camera orbit parameter sentinel used by motion code |
| `0x001EC884` | `0.0f` | camera position offset |
| `0x001EC888` | `0.0f` | camera position offset |
| `0x001EC88C` | `0` | adjacent camera state word |

Keeping only the first word in source shifts the following raw small-data object
because of input alignment. Recover complete aligned ownership blocks and prove
the resulting full-image layout.

## 5. Source-shape lessons

- Model addresses inside large objects as fields of those objects. Declaring
  camera fields at offsets `0x30` and `0x34` as standalone small globals caused
  incorrect GP-relative code; a 16-byte vector field generated the retail
  absolute accesses.
- Type qualifiers affect alias scheduling. `func_00101AD0` requires a
  `const float *`; a `Vec3f *` spelling changes instruction order.
- A scalar or vector copy must be expressed at the recovered width. The camera
  code contains both three-float operations and a proven 16-byte EE quadword
  copy; treating them as interchangeable changes code generation.
- Prefer source declarations and control flow that explain the entire matching
  instruction sequence. A locally better opcode count is not a substitute for
  the correct object model.

- An eight-byte object read at offset zero needs `volatile`. Without it the
  load is hoisted into the `jr` delay slot, because the compiler still counts
  the access as a single instruction. Offset-four reads need no qualifier
  (`func_001500C8` against `func_0015EDC0`).
- `long` is eight bytes and `long long` is sixteen. A retail `sd`/`ld` field is
  `long`; spelling it `long long` produces `sq`/`por` (`func_0018E608`,
  `func_00198F58`).
- `(base + index)->field` and `base[index].field` are not interchangeable. Only
  the first reproduces the retail `addiu %lo`, `sll`, `addu` operand order; a
  local pointer temporary swaps the `addu` operands.
- Independent trailing stores are reordered by the compiler, not by the struct.
  For a run of stores written in ascending order the emitted order is
  `first, last, second, third, ...`, with the second-to-last landing in the
  `jr` delay slot. Reorder the source, never invent padding (`func_00182EA8`).
- Assigning a mask to a local defeats the single-bit store-flag optimisation.
  `return (x & 2) == 0;` yields `srl`/`xori`/`andi`; `int f = x & 2; return f == 0;`
  yields the retail `andi`/`sltiu` (`func_0014D380`).
- Ternary polarity is inverted by the compiler, so retail `slti`/`movn` needs
  the condition written the positive way round (`func_0014ED90`).
- Prototyping a call whose result is discarded as `int` rather than `void`
  changes register allocation (`func_0014F1E0`).
- Block layout follows source order: write the guard so that the common path
  falls through.
- The branch comparison reads its operands as they stand at the branch, before
  the delay-slot instruction runs. For a branch-likely form the delay slot
  belongs to the taken path only.
- Values produced on a guarded path are not live after the join, and a guarded
  path ending in `jr $ra` makes the tail an else branch rather than common code.

## 6. Negative evidence and dead ends

- Modern assembly of historical compiler output is not authoritative for
  `move`; always use the bundled assembler when the driver supports it.
- `func_001016A0` and `func_00101748` have readable 156-byte semantic
  reconstructions against 168-byte retail functions. The substantive
  instructions and registers agree, but each is missing three hazard nops after
  float-literal materialization. Volatile, union, punning, scheduler, CPU, and
  local compiler-version variants did not recover them. Synthetic nops would be
  a shortcut, so these remain unmatched near-matches.
- An exact standalone function is not automatically a proven source unit.
  `func_00101BF0` only reproduced retail symbol expansion after it was compiled
  with its real neighboring camera functions and source-owned small data.
- Ghidra can recover useful scalar control flow, types, and call relationships,
  but unsupported EE/MMI instructions may produce p-code errors or incomplete
  function bodies. It is never match authority.
- Permutation search is appropriate only after a plausible semantic C candidate
  exists. A search result must still pass the ordinary isolated verifier and
  full-image rebuild; score improvements alone are not evidence.

### Structural blockers with no natural-C expression

These are recorded so they are not re-attempted. Each is a toolchain or ISA
limit, not a missing insight.

- PS2 kernel syscall stubs (`addiu`/`syscall`/`jr`/`nop`, about 160 functions)
  are hand-written assembly and cannot be produced from C.
- VU0 macro-mode code (`lqc2`, `vadd.xyzw`, `vdiv`, `qmtc2`), roughly
  `0x0018A3D0-0x0018AFC8`, is reachable only through inline assembly.
- Sixty-four-bit bitwise arithmetic is rejected by the proven profile with
  "unsupported wide integer operation", which blocks every function that builds
  GS or DMA qword tags. A `volatile long long` bitfield is the one recovered
  way to read such a word.
- The second EE multiply pipe (`mult1`) is never emitted; the compiler issues
  two plain `mult` instructions where retail pairs `mult1` with `mult`.
- Neither SN build accepts `-foptimize-sibling-calls`, so retail frameless tail
  calls (`j callee` with no prologue) cannot be reproduced.
- Hazard `nop`s after float-literal materialisation remain unrecoverable, as
  first recorded for `func_001016A0`. Synthetic `nop`s are not an acceptable
  shortcut, so these stay unmatched near-matches.

## 7. Tool map

| Stage | Tool | Role and authority |
| --- | --- | --- |
| Disc conversion | `tools/mode2_to_iso.py` | Deterministically converts the verified Mode2/2352 dump. |
| Disc extraction | `tools/iso9660_extract.py` | Extracts the filesystem without modifying the source dump. |
| ELF inventory | `tools/elf_inventory.py` | Records executable sections, segments, entry point, GP, and hashes. |
| Split and linker generation | Splat + spimdisasm | Generates temporary assembly and the reconstruction linker script. |
| Compiler execution | Wibo + pinned SN GCC driver | Runs the historical Windows-hosted EE compiler reproducibly. |
| Historical assembly | bundled GNU assembler | Produces authoritative source-object encodings for the proven profile. |
| ELF repair/linking | GNU MIPS binutils | Removes obsolete metadata, resolves relocations, links, and extracts images. |
| Isolated proof | `tools/match.py` | Compares a complete function or shared source-unit byte range. |
| Batch proof | `tools/batch_verify.py` | Re-verifies a JSONL candidate manifest with complete ranges and compact, restartable results. |
| Candidate ranking | `tools/candidate_queue.py` | Ranks untouched functions by size and instruction features without changing proof state. |
| Split generation | `tools/gen_splat_config.py` | Derives source islands from the reconstruction ledger and rejects stale manual boundaries. |
| Transactional integration | `tools/merge_candidates.py` | Validates candidate provenance, updates ledgers and source islands, and rolls back unless the full image, baseline, progress, and public audit all pass. |
| Full-image proof | `tools/build.py` | Requires the reconstructed 970,772-byte image and SHA-256 to match. |
| Independent coverage proof | `tools/build_baseline.py` | Proves that generated assembly still covers the untouched image exactly. |
| Progress and hygiene | `tools/progress.py`, `tools/repo_audit.py` | Derives public metrics and rejects missing evidence, local paths, secrets, or generated inputs. |
| Static analysis | Ghidra | Analysis aid for control flow, types, references, and call graphs only. |
| Bounded source search | decomp-permuter | Explores semantic source-shape variants; never supplies match authority. |

Ghidra projects, permuter populations, extracted targets, generated assembly,
compiler binaries, and temporary lane reports stay ignored. Durable conclusions
from them are rewritten into source, the JSONL ledger, and this book.

## 8. Working loop

1. Select a function and inspect callers, callees, globals, and neighboring
   boundaries.
2. Write the smallest readable semantic candidate; use Ghidra only as one input
   to that reconstruction.
3. Test the relevant compiler/profile matrix and retain negative results.
4. If close, inspect the first real mismatch and try bounded source-shape
   changes. Use permutation search only when the semantic search space is clear.
5. Verify the entire function or source-unit range with `tools/match.py`.
6. Integrate the source and data boundaries, regenerate the split, and run the
   full-image and independent baseline gates.
7. Count readable source after complete-range and full-image proof. Preserve
   compiler or historical source-boundary ambiguity as a provenance note.
8. Record reusable facts in `matching-knowledge.jsonl`, update this book when a
   general rule changes, audit the public tree, then commit and push.

For throughput, selection and isolated verification may run in parallel across
disjoint ignored lanes. Integration remains serialized: regenerate source
boundaries from the ledger, verify shared units, rebuild the complete image,
run the independent zero-C baseline, and audit the public tree before a commit.

## 9. Current frontier

- The early camera module is the strongest compiler and translation-unit
  evidence region.
- `func_001017F0` extends the exact camera source boundary backward to
  `0x001017F0`; the complete source unit matches as one object.
- Nine additional camera-area functions in four exact source islands extend
  compiler evidence through `0x001041D7`.
- The ten-function resource-record unit is the second compiler-
  discriminating neighborhood.
- Seven hundred and eleven readable source functions / 36,196 catalog bytes are
  exact over their complete ranges and in the full-image build. Every one
  counts as matched; ambiguous compiler or historical source-file provenance
  remains attached as evidence.
- A bounded symbolic pass recovered 112 branch-free leaves without emitting
  target bytes as source: it derived readable statements from retail
  instructions, compiled the finite declaration and independent-statement
  order variants, and retained only strict complete-range matches.
- The recovery engine also handles a single forward conditional by preserving
  branch-time operand values across the delay slot, restoring registers that
  are live only on the guarded path, and distinguishing early-return paths from
  common tails. This added 41 exact functions.
- Five boundary-tested units at `0x0012FC88-0x0012FCC0`,
  `0x0014B4A0-0x0014B4C0`, `0x00178248-0x0017826C`,
  `0x0017F9A0-0x0017F9B8`, and `0x0019A7D8-0x0019A83C` preserve their
  internal alignment and now build as combined readable C.
- The adjacent `func_001016A0` and `func_00101748` near-matches remain blocked on
  authentic hazard scheduling, not semantics.
- Small exact functions elsewhere in the executable remain useful throughput
  candidates, but they increase public metrics only after complete-range
  verification, full-image reconstruction, independent baseline, and public
  audit all pass.
- Parallel lanes use ignored artifacts or isolated clones. The shared checkout,
  generated split, and build directories are single-writer resources; candidate
  integration is serialized and revalidated on the current committed base.
