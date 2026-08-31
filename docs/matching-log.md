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
