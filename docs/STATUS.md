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

Source-reconstructed and matched: **717 functions / 36,536 bytes**

Matched functions: **717 / 2,189 (32.7547%)**

Matched text bytes: **36,536 / 663,704 (5.5049%)**

There is one public match tier. Readable source that matches its complete range
and survives the exact full-image rebuild is counted; unresolved compiler or
historical source-file provenance remains attached as evidence rather than
hiding the function from progress.

The first leaf and boundary campaigns established the compiler matrix and
source-unit rules. Bounded recovery then added branch-free leaves and structured
single-conditional functions while retaining complete-range verification.
Later state, packet, message, gameplay, and SDK campaigns used disjoint ignored
lanes for discovery and a serialized transaction for integration.

Every accepted batch has passed the exact 970,772-byte source build, the
independent zero-C baseline, generated progress checks, and the public-tree
audit. Near-matches and isolated candidates that fail source-boundary or
whole-image integration remain uncounted.
