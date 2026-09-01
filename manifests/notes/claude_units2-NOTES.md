# Lane claude_units2 — turning byte matches into proven translation units

Goal: take already-matched, address-adjacent functions and prove the whole
combined range byte-for-byte from ONE source file compiled with ONE
configuration, instead of one object per function each free to pick its own
compiler and assembler flags.

## Method

1. `runs.json` / `runs2.json` — adjacency runs over `config/reconstructed.json`.
2. `merge.py` — concatenates the per-function sources into one unit source:
   dedupes typedefs and externs, drops prototypes for functions the unit
   defines itself, and renames a type whose name two sources spell with
   different bodies so each function keeps the object model it was proven with.
3. `unify.py` — where two sources declare the *same global* differently
   (a four-byte scalar in one function, an eight-byte struct in another),
   generates one variant per spelling and rewrites the uses, because inside one
   real object only one spelling can be true.
4. `tryrun.py` / `batch2.py` — verify the whole range with
   `tools/match.py --range-start/--range-end` over the profile and
   object-flag grid; `batch2.py` takes the longest verifying prefix and
   recurses, so a split point is a candidate object boundary.
5. `hand_*.c` — units the mechanical merge could not unify, rebuilt by hand.

## Rules proved in this lane

- **A four-byte zero gap between two functions is assembler function
  alignment, not an object boundary.** 965 of the 968 inter-function gaps in
  the image are exactly four zero bytes. `hand_00133688.c` compiles six
  functions across such a gap (0x00133688-0x00133858) as one object and
  matches; the gap is reproduced by the compiler's own `.align`.
  Grouping only on strict `addr + size == next` understates the runs badly:
  it found 188 candidate functions, gap-tolerant grouping found 386.
- **Whether an object emits trailing alignment padding is a property of the
  object, and has to be probed both ways.** `func_00154638` + `func_00154668`
  verify only at the last function's exact end (0x154694) and report a size
  mismatch when the range is extended to 0x154698; `func_00129040` +
  `func_00129048` are the opposite — they verify only with the four trailing
  zero bytes included (0x129078, not 0x129074), and so does
  `func_001638A8` + `func_001638B0`. Both ends must be tried; the one that
  verifies tells you the object's real size.
- **One symbol legitimately shows both addressing modes inside one object.**
  For an eight-byte object assembled by the bundled `Ps2EeAs.exe`, a small-data
  pseudo that lands in a branch delay slot is expanded GP-relative and every
  other one as the two-instruction absolute macro. `func_00105E90`/`func_00105E98`/
  `func_00105EE8` use `D_001ED090` in `lui $v0,%hi` + `lw %lo($v0)`,
  `lw %gp_rel($gp)` (delay slot) and `lui $at,%hi` + `sw %lo($at)` forms — all
  three from one `struct { char *pointer; char pad[4]; }` declaration under
  `ee-gcc2.95.3-136-O2-G8-ps2as`. Splitting them into per-function objects had
  required three different flag combinations for one eight-byte global.
- **`-Wa,-G4` is usually not determined by the bytes.** Several functions
  recorded with `-Wa,-G4` also match with no object flag at all
  (`func_001500C8`); under the `-ps2as` profile the assembler `-G` value made no
  difference to any unit in this lane. Every unit here is recorded with the
  smallest flag set that verifies, which is the honest claim.
- **`lw` and `lbu` on one gp-relative symbol are one `int` object**, with the
  byte access spelled `*(unsigned char *)&X` (`hand_001519E8.c`,
  `D_001ECBE0`).
- **A union used to give one word two bitfield spellings must use `long`, not
  `long long`.** `long long` bitfields inside a union member force sixteen-byte
  union alignment and inflate the record stride (0x40 record became 0x50);
  `volatile long` keeps the eight-byte storage unit
  (`hand_00154638.c`, `D_002ABA40`).
- **Two functions modelling one record with differently-shifted field lists is
  a modelling artefact, not two objects.** The unified record simply carries
  every field at its true offset, with a union where two field types share an
  offset (`hand_0015BD38.c`, `hand_0015E118.c`, `hand_0019AB08.c`).
- **A shared helper has one prototype per object.** Where one function
  discarded `func_0018A690`'s result and another returned it, only the
  `void`-returning prototype reproduces retail's instruction schedule; the
  second function is then `void` as well (`hand_00133688.c`).

## Negative results (candidate real object boundaries)

- **0x00190000.** `func_0018FFC0` needs Sony EE GNU C `ee-gcc2.9-991111-01-O2`
  (64-bit callee-saved spills) and `func_00190000` needs SN
  `ee-gcc2.95.3-136-O2-G8`; no profile in `config/toolchains.json` produces
  both. Under the Sony profile the combined range matches exactly up to
  `+0x40`, which is `func_00190000`'s first byte. This is a compiler change
  inside the image, so it is an object boundary by construction — and it is
  *above* the 0x00185400 SDK frontier, so the two regimes interleave rather
  than meeting at a single address.


## Result

`work/claude/units2.jsonl` — 323 functions in 119 proven multi-function units,
21,248 bytes of retail text, every unit re-verified with
`tools/match.py --range-start/--range-end` after it was written.

Configurations used by these 323 functions, before and after:

| Configuration | as isolated objects | as proven units |
| --- | ---: | ---: |
| `ee-gcc2.95.3-136-O2-G8` | 245 | 262 |
| `ee-gcc2.95.3-136-O2-G8` `-Wa,-G4` | 50 | 16 |
| `ee-gcc2.95.3-136-O2-G8` `-Wa,-G0` | 15 | 0 |
| `ee-gcc2.95.3-136-O2-G8` `-mno-split-addresses` | 4 | 4 |
| `ee-gcc2.95.3-136-O2-G8` `-Wa,-mcpu=4000` | 1 | 0 |
| `ee-gcc2.95.3-136-O2-G8` `-mno-split-addresses,-Wa,-mcpu=4000` | 1 | 0 |
| `ee-gcc2.95.3-136-O2-G8-ps2as` | 3 | 41 |
| `ee-gcc2.95.3-136-O2-G8-ps2as` `-Wa,-G4` | 4 | 0 |

Eight per-function configurations collapse to four per-unit ones. Two of the
project's ten build configurations (`-Wa,-mcpu=4000` and
`-mno-split-addresses,-Wa,-mcpu=4000`) were used by exactly one function each
and disappear entirely; `-Wa,-G0` and `-ps2as -Wa,-G4` disappear from this
lane's functions. Ninety of the 323 functions end up with a different recorded
configuration from the one they were matched alone with, which is the point:
the unit determines the flags rather than the flags being chosen per function.

## Split points

`batch2.json` records 37 places where no configuration in the search grid
(both SN profiles x `{}`, `-Wa,-G4`, `-Wa,-G0`, `-mno-split-addresses`, over
every declaration-spelling variant) unified two adjacent matched functions.
Each is a *candidate* object boundary, not a proven one — a better source
spelling may still unify them, exactly as hand work unified sixteen runs the
mechanical merge could not. Only 0x00190000 is proven, because it is a
compiler change.

## Landing (units3)

`work/claude/units3.jsonl` is the ordered application plan; `PLAN.md` is the
same thing as a table. Each record carries the previous shape plus
`unit_id`, `batch`, `retire_source` and `retire_profile`, so one record names
everything needed to retire one function and point it at its unit.

Gate: `python3 work/lanes/claude_units2/verify_units3.py` — exit 0 means every
unit still byte-verifies and no function in the plan has moved in the ledger.
It re-reads `config/reconstructed.json` on every run, so run it immediately
before applying, and after any batch.

### Why the units are independent of each other and of the rest of the image

Measured, not assumed (`reverify.json`, `retired_scan.json`, `undef_scan.json`):

- **All 119 unit objects emit `.text` and nothing else.** No `.rodata`, no
  `.sdata`, no `.data`, no `.bss`. The only other section is a 24-byte
  `.reginfo`, which the link discards.
- **All 323 objects being retired also emit `.text` and nothing else**, and
  define no symbol beyond their own function (only the `gcc2_compiled.` /
  `__gnu_compiled_c` markers every object carries).
- **No unit references a symbol its retired members did not already
  reference** — zero new undefined symbols across all 119.
- Each unit occupies exactly the address range its members occupied, and the
  full range is byte-identical to retail, so the next object still begins at
  the same address.

Together these remove the mechanism that broke the last attempt. A jump-table
function's table can move when `.rodata` input contents or ordering change;
neither side of this substitution contributes a single `.rodata` byte, so
`.rodata` and `.sdata` layout is untouched by construction. The same argument
covers the small-data block at `0x001EC880`: no object here contributes
`.sdata`.

Residual risk is therefore confined to splat/linker input *ordering* — 119
objects replacing 323 — which is what the batches are for.

### Batch order

Batches are ordered least- to most-exotic so a failure lands early and cheap,
and each batch is independently landable and revertable.

| Tier | Batches | Units | Functions | What is special |
| --- | --- | ---: | ---: | --- |
| A | A01-A09 | 89 | 256 | plain `ee-gcc2.95.3-136-O2-G8`; the ordinary path |
| B | B01-B02 | 18 | 41 | built through the bundled `Ps2EeAs.exe`, a different assembler binary |
| C | C01-C02 | 12 | 26 | above the 0x00185400 SDK frontier, where the compiler regime is contested |

Ten units per batch is arbitrary — the analysis above says any subset works, so
split further if a batch fails and you want to bisect. Failure of one unit
should cost one unit.

### Configuration changes to expect

53 of the 119 units record a different `build_profile`/`object_flags` from the
ledger entries they replace, covering 90 of the 323 functions. That is the
result, not a side effect: the unit determines the flags. In particular 32
functions move from `ee-gcc2.95.3-136-O2-G8` with assorted flags onto
`ee-gcc2.95.3-136-O2-G8-ps2as` with none, because the delay-slot expansion is
what actually explains their bytes.

### On the 109 mixed-configuration adjacency edges

This lane resolves the ones it covers by making the neighbours one object with
one configuration. The 20 edges that put Sony EE GNU C next to SN GNU C across
a four-byte gap are a different matter: `0x00190000` is one of them, and it is
the one boundary here that is *proven* rather than assumed, because no profile
in `config/toolchains.json` builds both sides. Under the Sony profile the
combined range matches exactly up to `+0x40`, which is `func_00190000`'s first
byte. Those edges are real object boundaries; they need the two sides recorded
as separate objects, not unified.
