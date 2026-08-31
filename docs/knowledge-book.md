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
- Sixty-seven readable source functions are exact over their complete ranges
  and in the full-image build. All 67 count as matched; ambiguous provenance is
  retained in their ledger evidence.
- The adjacent `func_001016A0` and `func_00101748` near-matches remain blocked on
  authentic hazard scheduling, not semantics.
- Small exact functions elsewhere in the executable are useful candidates, but
  remain subject to local compiler and source-unit provenance before they can
  increase public completion metrics.
