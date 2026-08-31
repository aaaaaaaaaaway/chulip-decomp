# Status

## Completion gates

| Gate | State | Evidence |
| --- | --- | --- |
| Exact USA disc revision fingerprinted | complete | `config/disc.json` |
| Disc filesystem reproducibly extracted | complete | `tools/mode2_to_iso.py`, `tools/iso9660_extract.py` |
| Main executable identified and hashed | complete | `config/elf.json` |
| ELF/code/data layout mapped | complete | `config/elf.json`, `config/splat.us.yaml` |
| Original compiler/linker family identified | partial | SN GCC 2.95.3-EE build 1.36 proven for first contiguous neighborhood |
| Baseline split and nonmatching rebuild works | complete | 970,772-byte whole-image match |
| Isolated byte-match verifier works | complete | `tools/match.py` |
| First source neighborhood promoted | complete | `0x00101490-0x001014DC`, isolated and full-image exact |
| All game code/data byte-matches | pending | — |
| Clean-from-disc reproduction passes | pending | — |

Provisional function catalog: **2,189 functions / 663,704 bytes**

Source-reconstructed in exact current build: **5 functions / 124 bytes**

Promoted matched functions: **3 / 2,189 (0.1370%)**

Promoted matched text bytes: **76 / 663,704 (0.0115%)**

Two startup candidates remain deliberately unpromoted even though they are
isolated and globally exact: their enclosing translation-unit boundary is not
yet established. Progress is derived only from `config/matched.json`.
