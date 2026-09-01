# Decompilation productivity tools

These diagnostics reuse the exact compiler, assembler, linker script, symbol
inputs, address range, object flags, and rodata placement from `tools/match.py`.
They do not replace exact full-range verification.
Unmatched candidates default to `ee-gcc2.95.3-136-O2-G8`; pass `--profile`
when neighborhood evidence indicates another configured historical profile.

```sh
python3 tools/asm_diff.py func_00100488
python3 tools/similar_functions.py func_00101490 --with-c
python3 tools/region_match.py func_00100290
python3 tools/region_match.py func_00100290 --block 2
python3 tools/dup_guard.py check func_00100290 --record --diff 7
```

All match-related arguments accepted by `asm_diff.py` and `region_match.py`
are also accepted after the `check` or `record` subcommand of `dup_guard.py`:
`--source`, `--profile`, `--range-start`, `--range-end`, repeated
`--object-flag`, `--rodata-start`, and `--no-rodata`.

`similar_functions.py` disassembles the retail text once and stores an opcode
index in ignored `work/cache/opcode_index.json`. Its default pool contains only
functions in `config/matched.json`. The duplicate ledger is the append-only,
ignored `work/cache/dup_guard.jsonl`.

Exit codes are composable in worker loops: 0 means match/success/new candidate,
1 means a byte mismatch, 2 means an input or tool failure, and duplicate checks
use 3 for a previously recorded attempt.
