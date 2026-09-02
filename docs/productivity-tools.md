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

## Guided search with the permuter

`tools/permute.py` prepares a decomp-permuter working directory for one
function. The permuter searches source rewrites that preserve behaviour and
change register allocation and scheduling, which is the work a lane otherwise
does by hand: `func_00105F28` landed only after one exhausted roughly 5,040
declaration orders and 4,000 statement orders to settle a register-allocation
tie, and 119 unmatched functions are larger than 1 KB.

```sh
python3 tools/permute.py func_0011AE00
python3 tools/permute.py func_0011AE00 --source work/lanes/mine/candidate.c \
    --profile ee-gcc2.95.3-136-O2-G8-ps2as --permuter ../kaze-decomp/tools/decomp-permuter
```

It writes `base.c`, `target.o`, `compile.sh`, and `settings.toml` under
`work/permuter/<function>/`, taking the source, profile, and object flags from
the reconstruction ledger or a verified campaign candidate unless overridden.
The permuter itself is not vendored; point `--permuter` at a checkout.

The compile is delegated to `tools/permute_compile.py`, which routes through
`match.compile_historical_object`. That is deliberate: a search optimising
against a reimplemented driver would drift from the verifier and report
progress on bytes nothing will ever accept. Verified on `func_0011AE00`, the
object `compile.sh` produces is byte-identical to the one `tools/match.py`
judges, and `target.o` carries the retail bytes under the function symbol.

Feed the permuter's `output-*/source.c` candidates back through
`tools/campaign.py harvest`, which records a per-profile word distance so near
misses can be ranked.

## Parallel campaigns

```sh
python3 tools/campaign.py plan --limit 20
python3 tools/campaign.py packet --next --owner NAME
python3 tools/campaign.py harvest work/campaign/packets/FUNCTION/candidates
python3 tools/campaign.py status
```

The campaign tool adds expiring ownership, focused packets, content-addressed
attempt caching, and exact-candidate intake. All mutable state stays under
ignored `work/campaign/`. `tools/match.py` remains the isolated byte authority;
`tools/merge_candidates.py` independently replays successful claims and owns
the serialized public-tree transaction. See `docs/campaign-workflow.md`.

## Whole-ledger re-verification

```sh
# Replay every promoted function/profile claim. Interrupted runs resume.
python3 tools/reverify_ledger.py

# Divide unique source-unit/profile proofs between isolated workers.
python3 tools/reverify_ledger.py --shard-count 4 --shard-index 0

# Run a bounded or targeted audit.
python3 tools/reverify_ledger.py --limit 10
python3 tools/reverify_ledger.py --function 'func_0010*' --profile ee-gcc2.95.3-136-O2-G8
```

This audit does not accept `isolated_match` or `whole_program_match` ledger
fields as proof. It compiles current source over each complete unit range with
the recorded object flags for every claimed profile. Shared units are compiled
once per profile only when their range and flags agree. A byte mismatch or an
ABI-dangerous compiler diagnostic makes the command fail.

Proofs are appended to ignored `work/ledger-reverify/proofs.jsonl`; the current
run summary is `work/ledger-reverify/proofs.summary.json`. Sharded runs default
to separate, shard-named reports. Resume keys include the source, headers,
retail image, toolchains, runtime, host MIPS binutils, and verifier code, so
changing any proof input forces a fresh compilation.
