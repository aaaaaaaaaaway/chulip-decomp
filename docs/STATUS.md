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

Source-reconstructed and matched: **244 functions / 8,136 bytes**

Matched functions: **244 / 2,189 (11.1466%)**

Matched text bytes: **8,136 / 663,704 (1.2258%)**

There is one public match tier. Readable source that matches its complete range
and survives the exact full-image rebuild is counted; unresolved compiler or
historical source-file provenance remains attached as evidence rather than
hiding the function from progress.

The original 49-function leaf batch is fully source-built. A separate symbolic
leaf pass recovered 112 additional exact functions by deriving readable
statements and then compiling the finite declaration/order variants; only
complete-range byte matches survived. Boundary work also established five
multi-function ranges and added 24 further functions in the latest gated
transaction.

A structured single-conditional pass then added 41 functions / 2,188 bytes.
It models the delay slot at branch time, guarded-path register liveness,
early-return branches, and the R5900 three-operand multiply before attempting
source-shape matching.

The packet/VIF frontier now has 24 exact functions arranged in three combined
ranges plus a ten-helper continuation. One was already source-built; the other
23 remain queued until their public units pass the same complete-image
transaction.
