# Matching campaign log

## 2026-08-31 — project start

- Established the USA raw-track hashes and immutable-input policy.
- Added deterministic Mode2/2352 conversion and ISO9660 extraction tools.
- Imported the Kaze campaign's evidence gates and knowledge-ledger structure,
  but no PS1 compiler or linker assumption was carried over to this PS2 game.
- No function is counted as decompiled or matched yet.

## 2026-08-31 — exact build foundation and first source candidate

- Identified `SLUS_207.42` as the main ELF and pinned its file and load-image
  hashes, entry point, GP, sections, and single `PT_LOAD` layout.
- Catalogued 2,189 provisional functions covering 663,704 text bytes. Game,
  SDK, and handwritten ownership remains provisional.
- Produced an independent zero-C split whose complete 970,772-byte load image
  matches SHA-256 `77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.
- Added isolated compiler verification for GNU EE 2.96 and SN Systems GNU EE
  2.95.2 build 2.73a candidate profiles.
- Reconstructed `func_00100488` as an empty C function. Both candidates produce
  its exact 8 bytes, and the merged source-plus-assembly image is fully exact.
- Did not promote the function: its result does not distinguish the compiler,
  and translation-unit provenance has not yet met the policy gate.
- Established an 8-byte linker input subalignment. Without it, a compiler
  object's advertised 16-byte alignment shifted all following text by 8 bytes.

## 2026-08-31 — first compiler-discriminating neighborhood

- Expanded the historical compiler matrix through SN GNU EE 2.95.3 builds.
- `func_00100100` rejects GNU EE 2.96 because of scheduling and SN 2.95.2
  build 2.73a because it saves the return address with `sq/lq`. SN GNU EE
  2.95.3 build 1.36 emits all 40 retail bytes exactly.
- Reconstructed the contiguous functions at `0x00101490`, `0x001014B0`, and
  `0x001014D0`. The two nonleaf wrappers uniquely select build 1.36; the
  adjacent pointer getter matches all candidates and inherits the established
  neighborhood profile.
- Promoted 3 functions / 76 bytes after the complete 970,772-byte image still
  matched. `func_00100100` and `func_00100488` remain exact but unpromoted
  until their startup translation-unit boundary is supported.

## 2026-08-31 — camera-state layout and small-data proof

- Reconstructed seven more functions between `0x00101678` and `0x00101CB8`:
  a three-float aggregate copy, four absolute state-field accessors, and two
  GP-relative small-data setters.
- A scalar `extern float` declaration for the fields at state offsets `0x30`
  and `0x34` incorrectly generated GP-relative accesses. Modeling them as
  fields of the larger `0x001EDE00` aggregate generated the retail absolute
  addressing and exposed the first `CameraState` layout.
- The setters for `0x001EC884` and `0x001EC888` match under `-G8` and reject
  `-G0`, proving the small-data threshold for this module.
- Promoted the seven isolated matches after the complete load image remained
  byte-identical. The ledger now contains 10 functions / 184 bytes.

## 2026-08-31 — historical assembler path and vector copies

- The build 1.36 compiler emits `move` pseudos for pointer copies. Its bundled
  GNU assembler 2.9-ee-991111b encodes those as retail `daddu` instructions;
  modern GNU `as` encodes them as `or` and caused false isolated mismatches.
- Historical objects contain obsolete `.mdebug` metadata and an incorrect
  symbol-table boundary. Passing them through modern `objcopy` while removing
  `.mdebug` repairs the metadata without changing text or relocations.
- Reconstructed `func_00101630` and `func_001018E8`, which copy vectors into
  and out of the state object. Build 2.95.2-2.73a rejects both; build 1.36
  matches under `-G0` and `-G8`.
- All previous isolated matches passed through the corrected compiler-driver
  path, and the integrated load image remained byte-identical. The promoted
  ledger now contains 12 functions / 288 bytes.

## 2026-08-31 — parallel camera-motion recovery

- Three disjoint analysis lanes recovered eight additional exact functions;
  every candidate was then recompiled and verified in the main tree.
- `func_00101928` and `func_00101978` form the first proven multi-function
  source unit. Compiling the unit with build 1.36, `-O2 -G8`, and the bundled
  assembler's `-G0` option reproduces its complete 212-byte text range,
  including the inter-function alignment.
- The same source unit owns the aligned small-data block at `0x001EC880`:
  radius `-999.0f`, two zero position offsets, and a zero state word. Moving
  those 16 bytes from generated assembly into source preserves every GP
  relocation and the complete retail image.
- Reconstructed six more camera transformations and state updates at
  `0x00101868` and `0x00101A00-0x00101BEF`. A `const float *` parameter in
  `func_00101AD0` is required to preserve the retail alias schedule.
- Added verifier/build support for shared source units and per-object assembler
  flags. Both the 970,772-byte source build and independent zero-C baseline
  retain SHA-256 `77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.
- The promoted ledger now contains 20 functions / 1,076 bytes.

## 2026-08-31 — complete camera-motion source unit

- Reconstructed `func_00101BF0`, a 184-byte camera-position and view-angle
  update. A standalone candidate was deliberately rejected because external
  small-data symbols changed its assembler expansion.
- Merged all ten contiguous recovered functions from `0x00101928` through
  `0x00101CC3` into one source unit. The resulting 924-byte object text matches
  as a whole; the linker-proven 8-byte input alignment supplies the retail
  four-byte gap before `0x00101CC8`.
- The exact complete-image build now contains 21 promoted functions / 1,260
  bytes. This strengthens the source boundary instead of retaining convenient
  artificial per-function units.

## 2026-08-31 — camera unit extended backward

- Reconstructed `func_001017F0`, a 120-byte vertical camera and angle update.
  The function independently confirms the compiler `-G8` plus historical
  assembler `-G0` model and the same source-owned small-data sentinel.
- Merged the six already recovered intervening accessors and vector operations
  into the real camera source. The seventeen-function unit now reproduces all
  1,236 object-text bytes at `0x001017F0-0x00101CC3` together.
- Both the source build and independent baseline still reproduce the complete
  970,772-byte load image and expected SHA-256. The promoted ledger now contains
  22 functions / 1,380 bytes.

## 2026-08-31 — batch workflow and later camera units

- Added deterministic generation of Splat source islands from the
  reconstruction ledger, a JSONL batch verifier, and a ranked untouched-function
  queue. A 58-candidate manifest now re-verifies the nine integrated camera
  matches and 49 pending exact leaves in one compact, restartable pass.
- Reconstructed `func_00102440`, the two-function camera snapshot unit, the
  four-function camera object-helper unit, and the two-function resource unit:
  nine functions and 748 retail bytes in total.
- Negative compiler controls reject SN build 2.73a for all nontrivial units.
  The resource unit additionally requires compiler `-G8` and historical
  assembler `-G0`; the standalone camera update rejects compiler `-G0`.
- Added proven inner symbols at `0x001ED088` and `0x001ED08C` without splitting
  the underlying raw 16-byte small-BSS allocation.
- The exact source build and independent zero-C baseline both retain the
  970,772-byte image SHA-256. The promoted ledger now contains 31 functions /
  2,128 bytes; the exact source build contains 33 functions / 2,176 bytes.

## 2026-08-31 — transactional batch integration

- Added a named SN GCC 2.95.2 build 2.73a `-O2 -G8` profile. All 49 first-batch
  leaf candidates also match it, proving that small isolated functions cannot
  identify the compiler generation by themselves.
- Boundary probing extended three candidate ranges and recovered five adjacent
  functions. The combined resource-record source at
  `0x00137EA0-0x00137FCC` reproduces all 300 emitted bytes and uniquely selects
  SN GCC 2.95.3 build 1.36 `-G8`, rejecting every tested alternative including
  build 2.73a `-G8`.
- Added a fail-closed transactional importer. It validates natural C and ledger
  consistency, regenerates source islands, rebuilds the exact full image and
  independent baseline, refreshes README progress, audits the public tree, and
  restores all modified metadata if any gate fails.
- Integrated 34 exact functions: ten promotion-grade resource helpers and 24
  provenance-blocked state/accessor leaves. The exact source build now contains
  67 functions / 2,724 bytes; the promoted ledger contains 41 functions /
  2,412 bytes.
