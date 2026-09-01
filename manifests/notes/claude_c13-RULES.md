# Lane claude_c13 — working rules (band 0x00130000-0x0013FFFF)

## Tooling in this lane
- `python3 work/lanes/claude_c13/d.py <func>...`  — dump retail asm for functions.
- `python3 work/lanes/claude_c13/sweep.py <func> <src> [<func> <src> ...]`
  — tries 4 profiles x 6 `-Wa,-G` values x ps2as range-extend; prints a ready manifest
  line on MATCH, else the deepest first-diff config. ALWAYS use this instead of raw
  `tools/match.py` when hunting.
- `python3 work/lanes/claude_c13/cmp.py <func> <src> [profile] [-Wa,-Gn] [--ext]`
  — side-by-side retail vs. candidate disassembly. This is the primary feedback signal.
- `python3 work/lanes/claude_c13/conflict.py` — flags functions that need Ps2EeAs *and*
  carry a `%gp_rel` reference outside a delay slot (unmatchable without unit-owned .sdata).

Never pass `--profile` to `tools/match.py` without also passing the `--object-flag`s you
mean: it silently inherits the ledger's flags otherwise.

## Rules proved in this lane (2026-09-01)

1. **Cross-jumping tail merge.** When retail duplicates a load/setup inside every arm of a
   switch but shares the trailing `and`/`or`/`store`/`jr`, the source has a COMPLETE
   statement per case, not a shared tail expression. GCC merges identical tails after
   regalloc. Proof: `func_00136AF8` — `D = (D & mask) | bits;` written out per case.
   Case BODIES are emitted in SOURCE order; write the cases in the order their bodies
   appear in retail (dispatch compares stay in value order).

2. **Scaled-index hoist flips the `addu` operand order.** Retail `addu $base,$base,$idx`
   (result reuses the base register) is produced by hoisting the byte offset into a named
   local first:
   ```c
   int offset = i * 0x40;
   ((struct E *)((unsigned char *)obj->entries + offset))->field
   ```
   `obj->entries[i].f`, `(obj->entries + i)->f`, and a local pointer temp ALL give the
   swapped `addu $idx,$idx,$base`. Proof: `func_001331F0`.

3. **Re-reading a global produces retail's redundant register copy.** Where retail has a
   spare `daddu $aN,$vN,$zero` keeping a loaded global alive, write the second use as a
   fresh read of the global rather than reusing the cached local:
   `D_x = D_x | (1 << i);` not `D_x = cached | (1 << i);`. Proof: `func_001367E8`.

4. **Byte-offset loop for `slt` array walks.** `for (offset = 0; offset < 0x1440;
   offset += 0x24)` plus a cast pointer reproduces retail's signed `slt` bound test; a
   pointer loop gives `sltu` and an `int` index loop gets reversed into a downcount.
   (House idiom, see accepted `src/game/func_00138B00.c`.)

5. **`dli` expansion is an assembler discriminator.** For a 64-bit literal the compiler
   emits a macro and the assembler expands it:
   - bundled GNU `as`: `lui hi16` / `dsll32 N` / `ori lo`
   - `Ps2EeAs`:        `ori rX,$zero,K` / `dsll[32] K2` / `ori lo`
   Retail's `ori`/`dsll`/`ori` form therefore PROVES Ps2EeAs for that unit.

6. **The Ps2EeAs conflict.** Ps2EeAs emits the one-instruction `%gp_rel` form only for a
   pseudo in a branch delay slot (or for symbols the unit defines in `.sdata`); everywhere
   else it expands absolutely. A function that needs Ps2EeAs (rule 5) *and* has a
   `%gp_rel` reference outside a delay slot cannot be matched from a per-function source —
   its translation unit must own that symbol in `.sdata`. No `-G` value fixes it
   (tested -G8/-G16/-G32/-G64). Blocked here: func_00130E68, func_00131320, func_00131A10,
   func_00132010, func_00132C20, func_00132DC0, func_00138070 (4,976 bytes).

7. **Assembler nop-insertion mismatch (unresolved blocker).** Five functions contain
   `nop`/`nop` between a value producer and the branch that reads it
   (func_00136ED8, func_00137740, func_00136D70, func_001352A0, func_00135670);
   neither bundled assembler emits those. Conversely, in `func_00138B40` both bundled
   assemblers INSERT a nop between `slt` and a following `.set noreorder` `bnel` where
   retail has none. Do not spend budget on these.

8. **Volatile is a two-edged tool.** `extern T *volatile G;` forces retail's repeated
   reload of a global pointer, but GCC 2.95 will not move a volatile MEM into a branch
   delay slot, and the scheduler still pipelines the (non-volatile) stores one ahead of
   the loads. `volatile T *G` (volatile pointee) makes every field access volatile and
   breaks delay-slot fills. func_0013D130 is stuck between these two.

## Family map for this band
- `0x001308F8-0x00133040` GS display-list builders over `struct DrawList { int f0;
  unsigned char *cursor; int f8; int fc; int f10; }` at `D_002D81B0` and `D_002D81C0`.
  House idiom: `p = D_002D81B0.cursor; D_001ECxxx = (int)p; func_00161590(p, N);
  func_00161460(p, N); func_001614E0(p, 3, N); p += 0x10; *(long *)p = <tag>; p += 8; ...
  func_00161590(p, 0); p += 0x10; D_002D81B0.cursor = p;`
- `0x00133688` two mirrored 0x40-byte matrix stacks (`D_001FE5F0`/`D_001FEAF0`).
- `0x00137E20-0x00139348` resource records: `D_00203C20[]` stride 0x24, 144 entries.
  `D_00203C3C`/`D_00203C24`/`D_00203C34` are FIELD LABELS inside record 0.
  `D_00203C00` is one object reached by `+0x8`/`+0xC` from a single base.
- `0x0013A6A0-0x0013F628` actor/cutscene step family over `struct Actor *D_001ED3C8`
  (fields 0xE, 0x14, 0x16, 0x18, 0x1A) with `D_001ED3D8` the next-state id. All need
  ps2as with `--range-end` extended by 4.

## Rules proved later in the session (2026-09-01, second half)

9. **Constant integer division/modulo is NOT strength-reduced.** A literal `x % 10`
   compiles to `li $vN,10` / `beql $vN,$zero,.L` / `break 0,7` / `div`/`mfhi` — the
   `beql`+`break` divide-by-zero trap that earlier lanes recorded as unexplainable is
   just GCC's `divmodsi4` trap for a register divisor. Only power-of-two divisors are
   turned into shifts. Proof: `func_0013DF28` (`field_0xc % 10`), `func_0013D288`.
   A division whose *result* is dead leaves the `li`+trap alone (the trap is a separate
   side-effecting insn, the `div` is deleted): that is what `func_0013D288`'s
   `addiu $v0,$zero,3` / `beql` / `break` with no `div` is. A `divu` by a power of two
   (`func_00130B70`'s `/8`) means the divisor was a VARIABLE at expand time, not a
   literal — spell it as a local initialised to the constant.

10. **`D_001ED3C8` is genuinely EIGHT bytes** (`asm/data/cod/sbss.sbss.s`:
    `.space 0x08`), not four. Modelling it as
    ```c
    struct ActorSlot { struct Actor *actor; int field_0x4; };
    extern struct ActorSlot D_001ED3C8;
    ```
    is the true data model, and it does two things at once:
    - the compiler emits `.extern D_001ED3C8, 8`, so bundled GNU `as` at `-Wa,-G4`
      expands it ABSOLUTELY while 4-byte neighbours (`D_001ED3D8`) stay GP-relative.
      Several actor functions therefore do NOT need `-ps2as` after all
      (`func_0013D288` matches under `ee-gcc2.95.3-136-O2-G8 -Wa,-G4`).
    - **it forces retail's repeated reload of the actor pointer without `volatile`.**
      Reading `D_001ED3C8.actor` (a COMPONENT_REF of a global struct) is not CSE'd
      across a store through that pointer, whereas reading a bare
      `extern struct Actor *D_001ED3C8` is. This RETIRES the "actor-timer delay-slot
      reload" blocker (`claude_w2_1213` NOTES blocker (B)): the reload and the
      delay-slot fill are no longer mutually exclusive, because no `volatile` is
      involved. Proof: `func_0013AA38`, `func_0013AAF8`, `func_0013D130`,
      `func_0013F4E0`, `func_0013D288`.

11. **Don't cache a pointer whose only two uses straddle a call.** In `func_0013AAF8`
    the tail needed `if (D_001ED3C8.actor->f16 != 0) { call(); } call2(D_001ED3C8.actor->f14);`
    with NO local — a local for the reloaded pointer swaps `$v0`/`$v1`. Conversely
    `func_0013AD58` wants TWO distinct locals for the two loads. Match retail's register
    numbering by counting how many distinct pointer pseudos it uses.

12. **Assigning the extracted bit to a local defeats `(x & 1) == 1` -> `!= 0`.**
    Retail's `li $v1,1` + `beq` (rather than `bnez`) needs
    `int flag = (int)(x >> 5) & 1; if (flag == 1)`. Proof: `func_00130408`.

## Blocked / near-miss ledger for this lane
- Assembler nop-insertion mismatch (rule 7): func_00138B40, func_00138940,
  func_00136D70, func_001352A0, func_00135670, func_00137740, func_00136ED8.
- Ps2EeAs / gp_rel conflict (rule 6): func_00130E68, func_00131320, func_00131A10,
  func_00132010, func_00132C20, func_00132DC0, func_00138070.
  (Group C's evidence suggests func_00132010 should be retried as part of the
  0x00132010-0x00132C1C unit, which func_00132B10 proves is a -ps2as unit.)
- Scheduling / register-allocation near-misses, all otherwise instruction-exact:
  func_001308F8 (1 word), func_00139EB8 (1 insn), func_0013AD58 (regalloc only),
  func_00130B70 (regalloc only), func_0013DF28 (tail store order),
  func_00130408 (one sw/ld pair), func_00138798 (3 words), func_001388F8 (1 copy).

## CORRECTION to rule 6 (proved 2026-09-01 by the group-B sub-lane)

Rule 6 is **not a hard blocker** — it is a translation-unit-ownership signal.
`func_001332D8` needs Ps2EeAs (inline `lui`/`ori`/`mtc1` float literals plus the
`mtc1`/`cvt.s.w` hazard nops) *and* has `lwc1 $f12,%gp_rel(D_001EC98C)($gp)` outside a
delay slot. Declaring the symbol `extern` gives the absolute form at every `-G`;
**defining** it in the unit —

```c
float D_001EC98C __attribute__((section(".sdata"))) = 0.0f;   /* exactly the 4 bytes
                                                                 and value that
                                                                 asm/data/cod/sdata.sdata.s
                                                                 records */
```

— makes `tools/match.py` derive `.sdata` at `0x001EC98C`, and Ps2EeAs then emits the
one-instruction GP-relative form byte-identically. The other functions listed as
rule-6-blocked (func_00130E68, func_00131320, func_00131A10, func_00132010,
func_00132C20, func_00132DC0, func_00138070) should be retried this way; note only ONE
source file in the whole image may define each such symbol, so this is a genuine
unit-ownership claim the coordinator has to arbitrate.

Related: **the GNU-`as` literal threshold and the small-data threshold collide at
exactly 4.** For a float constant the compiler emits an `li.s` macro; bundled GNU `as`
puts it in `.lit4` iff `-G >= 4` (which fails to link here with
`R_MIPS_LITERAL against .lit4`), and makes a 4-byte extern GP-relative iff `-G >= 4`.
So GNU `as` can never give inline float literals *and* a GP-relative 4-byte extern
(verified across `-Wa,-G0..-G7`); Ps2EeAs plus unit-owned `.sdata` is the only route.
