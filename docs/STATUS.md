# Status

## Completion gates

| Gate | State | Evidence |
| --- | --- | --- |
| Exact USA disc revision fingerprinted | complete | `config/disc.json` |
| Disc filesystem reproducibly extracted | complete | `tools/mode2_to_iso.py`, `tools/iso9660_extract.py` |
| Main executable identified and hashed | complete | `config/elf.json` |
| ELF/code/data layout mapped | complete | `config/elf.json`, `config/splat.us.yaml` |
| Original compiler/linker family identified | partial | SN GCC 2.95.3-EE build 1.36, bundled assembler, and `-O2 -G8` proven for first state module |
| Baseline split and nonmatching rebuild works | complete | 970,772-byte whole-image match |
| Isolated byte-match verifier works | complete | `tools/match.py` |
| Batch candidate verifier and ranked queue work | complete | `tools/batch_verify.py`, `tools/candidate_queue.py` |
| First source neighborhood promoted | complete | `0x00101490-0x001014DC`, isolated and full-image exact |
| All game code/data byte-matches | pending | — |
| Clean-from-disc reproduction passes | pending | — |

Provisional function catalog: **2,189 functions / 663,704 bytes**

Source-reconstructed in exact current build: **33 functions / 2,176 bytes**

Promoted matched functions: **31 / 2,189 (1.4162%)**

Promoted matched text bytes: **2,128 / 663,704 (0.3206%)**

Two startup candidates remain deliberately unpromoted even though they are
isolated and globally exact: their enclosing translation-unit boundary is not
yet established. Progress is derived only from `config/matched.json`.

The current batch manifest re-verifies 58 exact candidates in one restartable
pass: nine integrated camera matches and 49 pending leaf candidates. Batch
success alone does not promote a candidate; compiler and source-unit provenance
remain separate acceptance gates.
