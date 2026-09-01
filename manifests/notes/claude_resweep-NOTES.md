# claude_resweep lane notes

Manifest: `work/claude/resweep.jsonl` (174 entries, all MATCH under `tools/batch_verify.py`).

## Scope
350 parked functions / 561 candidate source files, enumerated by walking every
`work/lanes/**` `.c` file (not just `near/` and `nearmatch/`), plus the
permuter `runs/<func>/base.c` working copies and address-named `unit_*.c` files.

## Grid
7 profiles x {-Wa,-G0,-G1,-G3,-G4,-G8} x {function range, range extended to the
next catalog function} = up to 62 configurations per source, ~30k `tools/match.py`
invocations. `work/lanes/claude_resweep/sweep.py`.

## What actually converted things
- 60  the plain regional default already matched; parked purely as bookkeeping
- 45  `Ps2EeAs` at its default -G
- 36  `--range-end` extended to the next function (Ps2EeAs 8-byte `.text` padding)
- 25  compiler `-G8` with assembler `-Wa,-G0` (24) or `-Wa,-G3` (1)
- 06  decomp-permuter
- 01  mechanical statement-order permutation
- 01  Sony profile below the 0x00185400 frontier

## Negative results worth keeping
- `-mno-split-addresses` on every residual x every profile x every -G x both
  ranges converted **zero** functions.
- The `Ps2EeAs` -G sensitivity is real but rarely decisive: across 181 conversions
  only `func_001014E0` changes result with the ps2as -G value. At every other site
  the ps2as expansion is -G-independent.
- 16-byte quadword copy helpers (`func_00161328`, `func_001613D8`, `func_0018A680`)
  are unreachable: retail keeps the temp in `$a2` and leaves the `jr` delay slot
  empty; `u128 mode(TI)`, aligned struct, extra-parameter and temporary-variable
  spellings all produce `lq $v0` with the `sq` scheduled into the delay slot.
- A 64-bit literal cannot be steered by spelling. `0x6400000000008001L` and
  `((long)0xC800 << 47) | 0x8001L` both fold to `lui 0x6400`/`dsll32 0`; retail's
  `ori 0xC800`/`dsll32 15` is a different constant-synthesis strategy.
- `do { ... } while (0)` around a run of calls is load-bearing scheduling
  (`func_00129278`): removing the wrapper breaks the match at +0x49.
