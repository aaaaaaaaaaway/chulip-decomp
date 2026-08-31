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
