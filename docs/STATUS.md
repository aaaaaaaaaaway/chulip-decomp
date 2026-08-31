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
| Transactional candidate integration works | complete | `tools/merge_candidates.py` with automatic rollback across all gates |
| First source neighborhood matched | complete | `0x00101490-0x001014DC`, isolated and full-image exact |
| All game code/data byte-matches | pending | — |
| Clean-from-disc reproduction passes | pending | — |

Provisional function catalog: **2,189 functions / 663,704 bytes**

Source-reconstructed and matched: **67 functions / 2,724 bytes**

Matched functions: **67 / 2,189 (3.0608%)**

Matched text bytes: **2,724 / 663,704 (0.4104%)**

There is one public match tier. Readable source that matches its complete range
and survives the exact full-image rebuild is counted; unresolved compiler or
historical source-file provenance remains attached as evidence rather than
hiding the function from progress.

The first batch manifest re-verifies 58 exact candidates in one restartable
pass. Twenty-nine of its 49 leaf candidates are now source-built; boundary
probing extended that set by five more functions. A separate ten-function
packet/VIF lane and nine empty leaves are exact and queued for integration.
