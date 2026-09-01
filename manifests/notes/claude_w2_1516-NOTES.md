# Lane claude_w2_1516 notes

Worklist: `work/claude/wave2_n1516.txt` (146 functions, 75,100 bytes, 0x00150000-0x0016FFFF)
Manifest: `work/claude/w2_1516.jsonl` — 33 functions, 4,788 bytes, `batch_verify` 33/33 MATCH.
Helpers (all inside this lane dir): `dump.py` (asm listing), `sym.py` (D_ symbols a function
touches + their recorded sizes from `asm/data/cod`), `prec.py` (find already-reconstructed
functions with a similar opcode shape and print their C), `sweep.py` / `bulk.py` (profile x
object-flag sweeps), `permsearch.py` (compile-and-diff harness + store-order search),
`mkman.py` (regenerate the manifest by re-deriving each entry's profile).

## New rules proved here

1. **The 8-byte `-Wa,-G4` form is legitimate when the recorded size really is 8**, and it is
   also a SCHEDULING knob. `asm/data/cod/sbss.sbss.s` records `D_001ED568, 0x8`, so
   `extern int D_001ED568[2];` + `-Wa,-G4` is a true data model, not the retracted fake
   struct. Declaring the true size makes the compiler emit ONE `la` pseudo, so retail's
   `lui`/`addiu` stay adjacent and the index `sll` keeps its RTL position ahead of them.
   With an incomplete `extern int D[];` the compiler splits the address itself and the
   scheduler hoists the `lui` above the `sll`. Proof: func_00161BE0, func_00161BF8,
   func_00161FE0, func_00161A80. The same reasoning at the genuine 4-byte size gives
   `-Wa,-G3` (func_001512E8: `D_001ED458`/`D_001ED45C` are recorded 4 bytes).
2. **`D[index].field` vs `(D + index)->field` also picks the base REGISTER**, not just the
   `addu` operand order. The subscript form puts the symbol in `$v1` and the loaded value in
   `$v0`; the pointer form uses `$v0` for the symbol. Proof: func_00154600, which needed the
   subscript form at BOTH sites plus the two-exit `if (c == 0) return simple; return complex;`
   shape.
3. **When retail recomputes a base address for a second group of accesses, the second group
   must be a textually DIFFERENT pointer expression** — `(D + index)->a` / `(D + index)->b`,
   or a second local pointer. Using the subscript form there instead makes GCC build a
   separate `base + 0x20` pointer and use offset 0. Proof: func_00155800 (variants E and F
   both match; the subscript tail does not).
4. **`v ^= M; v |= N;` as two statements** gives retail's in-place `xori $a0,$a0` /
   `ori $a0,$a0`; the single expression `v = (v ^ M) | N` routes through `$v0`.
   Proof: func_00161FE0.
5. **Store-order recovery method.** For a run of independent stores, compile the source in
   plain ASCENDING offset order and diff the emitted store offsets against retail: the
   emitted order tracks source order closely, so the few out-of-place stores name the exact
   edits. func_0015E418 (28 stores) took two edits from ascending; func_001632E8,
   func_00155738 and func_00155648 matched at ascending order unchanged. Blind hill-climbing
   on the same space made no progress; exhaustive permutation is only worth it for <= 8
   stores (func_0015E518 fell to a 5040-case sweep, ~9 min).
6. **`dsll N` bitfields: the LOW field width is `32 - N`, not `N`.** `dsll 29` + `dsra32 0` +
   `andi 1` reads bit 3, so the union member is
   `volatile long l : 3; volatile long v : 32; volatile long h : 29;`. Getting this backwards
   costs exactly one word. Proof: func_0015A0A0 (`dsll 29` needed `l : 3`). The band-15
   note's `b16` case is symmetric and hid the error.
7. **A `jal` whose delay slot is `nop` while `$a0` still holds a live value means the callee
   TAKES that value.** Retail preserves `$a0` through the address computation only because it
   is an argument. Proof: func_0015A4E0 (`func_001518C0(index)` — the `void` prototype left
   3 words wrong) and func_001587B8 (a dead-looking `andi $a1,$a1,0xFFFF` is really
   `func_00158698(index, mode)`'s second argument).
8. **Prototyping a discarded-result call as `int` rather than `void` reserves `$v0`** and
   pushes a neighbouring temp to `$v1`. Proof: func_0015A4E0 (`int func_00151CA8(void *)`
   was the last two words).
9. **`x < 0 ? -x : x` compiles to a BRANCH (`bgez` + `negu`); the equivalent `if` statement
   compiles to `movz`.** This is the opposite of the intuition and of the existing ternary
   note. Proof: func_001525E0.
10. **Exact float literals matter to the last bit, and the game uses two different pis.**
    `0x40C90FDA` is `6.283185f` (= 2 * 3.1415925f); `0x40C90FDB` is `6.2831855f`;
    `0x40490FDB` is `3.1415927f`. func_00152670 uses the first family, func_001565D0 /
    func_0015C8B0 / func_0015D0E0 the second.
11. **Give each branch of a duplicated float computation its OWN local.** One shared
    accumulator lets GCC reuse the argument register `$f12` as the destination; separate
    locals (and splitting the load into its own statement) keep it in `$f1` like retail.
    Proof: func_001565D0 variant B.
12. `-ps2as` remains the right profile whenever one symbol shows both addressing modes and
    the GP-relative sites are exactly the branch delay slots (func_00153350, func_00163378,
    func_001637C8) or whenever `mtc1`/`cvt.s.w`/float-literal hazard nops appear
    (func_00152670, func_001565D0, func_0015C8B0, func_0015D0E0). For a size that is not a
    multiple of 8, extend `--range-end` to the next function (func_00152670 needed
    `--range-start 0x00152670 --range-end 0x001526D0`).
13. **A Sony-compiled function exists BELOW the 0x00185400 frontier.** func_00158478 matches
    only `ee-gcc2.9-991111-01-O2`; all three SN profiles miss it. w1517 had recorded it as a
    "cross-jumping" near-miss — it was the wrong compiler, not the wrong C. Worth re-testing
    other sub-frontier near-misses under the Sony profile.

## Blockers re-confirmed (do not re-attempt without a new idea)

- `li $aN,1` + `andi $rX,1` + `beq $rX,$aN`. Beyond the spellings w1517 recorded I also tried
  the DImode route (`long` bitfield with no `(int)` cast, `long` temp, `== 1L`): GCC folds
  even harder there, dropping two more instructions. RTL `nonzero_bits` sees through the
  `andi` in SImode and DImode alike. 22 of the remaining worklist functions (30,292 bytes)
  contain this pattern; `work/lanes/claude_w2_1516/triage2.json` lists them under `blocked`.
  Note the pattern is only a blocker when the compared value comes from `andi ...,1`. A
  register-materialised 1 compared against a CALL RESULT or a LOADED BYTE is fine, because
  GCC cannot prove the range — func_001639D8 and func_00161988 both compile that form
  correctly.
- 64-bit constant materialisation. retail `ori 0xC800; dsll32 15; ori 0x8001` is the
  assembler's `dli` macro; ALL SEVEN profiles (both SN builds, 2.96, Sony 2.9, both
  assemblers) emit the compiler's own `lui 0x6400; dsll32 0; ori 0x8001` instead, for every
  spelling of the constant (literal, `(long)0xC800 << 47 | 0x8001`, unsigned, folded or not).
  Blocks func_00150160 + func_00152210 (identical 160-byte twins, otherwise 1 scheduling swap
  from exact) and func_0015F0B0 + func_0015F4E0.
- Isolated-link limit: a source declaring ~10 small externs fails the `-ps2as` link with
  "small-data section too large". func_001637C8 needs `-ps2as` for its delay-slot GP-relative
  stores but cannot be linked that way; it is otherwise structurally complete.

## Near-misses kept as `nearmiss_*.c` (11 files, 1,624 bytes)

- **Register-allocation swap only, instruction-for-instruction identical**: func_00158B40
  ($v0/$v1 roles for the masked bit vs the loaded flags), func_001585A8 (mask stays in $a1 in
  retail, moves to $t0 in mine because the aux pointer steals $a1), func_00161AD0 (0xFF wants
  $v1 and 1 wants $v0; all 720 store permutations tried, none fixes it).
- **One or two scheduling swaps**: func_00150160 (also blocked on the 64-bit constant),
  func_001587B8 (`mov.s $f12` vs `li $a1` across the `jal` delay slot), func_00161988
  (retail has exactly one post-call `nop`; GNU `as` emits none and `Ps2EeAs` emits two).
- **CSE of a float zero**: func_0015C7E0 — retail materialises `mtc1 $zero` twice for two
  independent `== 0.0f` tests; GCC reuses the first. Two words.
- **`lb` vs `lbu`**: func_001504F0 — retail sign-extends the digit-table load; no spelling of
  `signed char` reproduced it, and forcing it with an `int` temp moves the damage earlier.
- **Assembler-mode conflict**: func_00153568 needs D_001ECC20 GP-relative outside a delay slot
  AND D_001ED470 absolute for its load / GP-relative for its delay-slot store. No single
  assembler does both; the likely answer is that the real translation unit DEFINES
  D_001ECC20 in `.sdata`/`.sbss`, which cannot be modelled from an isolated file.
- func_00161328 / func_001613D8: 16-byte `lq`/`sq` copy where retail's temp is `$a2`; every
  natural spelling gives `$v0`.
- func_00161B28: retail routes the return value through `$a1` and adds two `daddu` moves that
  no single-return or single-variable shape reproduced.

## Suspected translation units

- **`0x00154398-0x0015607x` + `0x001584xx-0x00158Exx` + `0x0015A0xx-0x0015D2xx`** — the big
  object-slot unit over `D_002ABA40` (stride 0x40: `float f[4]` at +0x00, a 16-byte quad at
  +0x10, the 64-bit flag word at +0x20 union'd with `Node *owner` at +0x24, `id` at +0x34,
  `slot` at +0x36, bytes at +0x3B), the parallel `D_002CFA40` (stride 0x20, `int flags` at
  +0x04, floats at +0x14/+0x18/+0x1C) and `D_002BDA40` (stride 0x40, alignment 1 — GCC copies
  it with `ldl`/`ldr`, which is how func_00155648 matched). Confirmed members matched here:
  func_001552B8, func_00155648, func_00155738, func_00155800, func_00155FE0, func_001565D0,
  func_00156B00, func_00156BC8, func_0015A0A0, func_0015A4E0, func_0015C8B0, func_0015C990,
  func_0015D0E0. The `Node` at +0x24 has a payload pointer at +0x10 and a second record
  pointer at +0x14; that second record carries ints at 0x14/0x18/0x1C and floats at
  0x24/0x28/0x2C.
- **`0x0015E178-0x0015EB88`** — the `D_002D78C0` record unit, stride 0x348, initialised field
  by field (func_0015E418, func_0015E518) and indexed with a three-operand `mult`.
- **`0x00161328-0x00162178`** — the pad/controller unit over the 8-byte `D_001ED548`,
  `D_001ED558`, `D_001ED560`, `D_001ED568`, `D_001ED570`, `D_001ED580`, `D_001ED588` pairs
  plus the 1-byte `D_001ED538..D_001ED545` block and `D_002D8600`. Every member is a thin
  wrapper over `func_00189xxx`. Matched: func_00161A80, func_00161BE0, func_00161BF8,
  func_00161FE0, func_00162178.
- **`0x001632E8-0x00163A58`** — the boot/allocation unit: func_001632E8 and func_00163378
  both register a callback pair through `func_00112F40`/`func_00112EB0` and write the
  4-byte `D_001ED594..D_001ED5A4` block; func_001637C8 allocates every buffer in
  `D_001ECD80..D_001ED844`; func_00163938 and func_001639D8 are its siblings.
- **`0x00153350-0x00153618`** — the `D_001A8B60` / `D_001A8B80` display-config unit
  (func_00153350 registers the callback, func_00153568 and func_00153618 build the same
  7-field record from the same two tables; the two differ only in where the destination
  comes from).
