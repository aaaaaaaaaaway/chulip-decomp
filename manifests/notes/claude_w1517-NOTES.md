# Lane claude_w1517 notes (bands 0x00150000-0x0015FFFF and 0x00170000-0x0017FFFF)

Manifest: work/claude/w1517.jsonl (20 entries, all MATCH, 2,512 bytes)
Helpers: dump.py (asm listing), fam.py / fam2.py (family clustering), sel.py (filter
worklist by referenced symbol), mkman.py (regenerate manifest from func_*.c + flags.json).
`nearmiss_*.c` files are one- or two-instruction misses, kept for the next lane.

## New rules proved here

1. **`(int)` cast on a `volatile long` bitfield.**  Retail `ld` + `dsll N` + `dsra32 0` +
   `andi 1` needs the union member spelled `volatile long low:N; volatile long value:32;
   volatile long high:(32-N);` AND the read spelled `(int)e->u.bN.value & 1`.
   - plain `long` bitfields (no volatile) let GCC narrow to `lwl/lwr` or `dsrl32`;
   - `volatile long long` is TImode and adds `pcpyld`/`pcpyud` junk on conversion;
   - a named `int` temp gives the right opcodes but the wrong register.
   Proof: func_001548C0.
2. **Mixed addressing inside one D_002ABA40 access.**  Use `(base + index)->field` for every
   site that reuses the entry pointer, and `base[index].field` for the ONE site whose field
   offset retail folds into the `%lo` (`addiu $rN,$rBase,ofs` then `addu`).  A pointer temp
   for both collapses the extra `addu`.  Proof: func_0015BA78 / func_0015B998.
3. **An extra callee-saved register in retail = a mutating cursor plus a saved base.**
   Write `p = cursor; base = p; ... p++; ... store p` rather than `base + n` expressions.
   Proof: func_001536A8 (retail saves s0..s4; the `base + n` spelling saved only s0..s3).
4. **16-byte zero local**: `union { long long raw; float f[4]; }` with `u.raw = 0;` gives
   retail's `por $v0,$zero,$zero` + `sq`.  A C initialiser emits a `memset` call instead.
   Proof: func_0015BA00.
5. Trailing float-store runs: source ascending order reproduces retail's
   `first, last, second, third` permutation (func_001548C0, func_00155398).
6. Case-body layout follows source order even inside a `switch`; reorder the cases to match
   retail's block order (func_0015CA60 / func_0015CB00 needed `case 2` written first).
7. `lui $rN,%hi(X)` + `lw $rN,%lo(X)($rN)` with NO gp-relative reference anywhere in the
   function is just the assembler macro at `-Wa,-G0` with a natural `extern T *X;`.
   Functions needing it here: func_00172130, func_00179360, func_001793C0.

## Hard blocker (cost ~1h, do not re-attempt without a new idea)

`addiu $aN,$zero,1` + `andi $rX,$rY,1` + `beq $rX,$aN` — a single-bit flag compared against a
register-materialised 1.  GCC 2.95.3-136 folds `(x & 1) == 1` to `x & 1` in EVERY spelling
tried: int/uint/char/short/long temps, `unsigned int b:1` bitfields, enum `BOOL`/`TRUE`,
`(long)x == 1L`, `switch`, `static __inline__` helper (with and without inlining), and the
2.95.2-273a / 2.96 compilers.  Blocks func_00154508, func_00154560, func_00154468,
func_0017CC88, func_0017CCF0, func_0017CC10 and the rest of the func_00136AE8 bit-check
family (28 worklist functions, ~19 KB).  Solving it unlocks the single biggest cluster left
in these two bands.

## Near-miss classes (files kept as nearmiss_*.c)

- **Saved-register pair swapped** (s0<->s1 / s1<->s2), everything else byte-identical:
  func_00158960, func_0017E668, func_0017F278, func_00154600.  Local-alloc priority; no
  source permutation found that flips it.
- **One extra scheduling nop**: func_0015DED8 / func_0015F0F0 (identical strcpy twins),
  func_0015CBB0, func_0015F4A8.  Retail's loop body is exactly one `nop` shorter.
- **Delay-slot fill choice**: func_00153918 (store vs `ori` in the 3rd `jal` slot),
  func_0017CBB8 (one `li` / `sb` swap).
- **Cross-jumping**: func_0015BBA0, func_00158478 — GCC merges two identical
  `xor`+`sltiu` tails that retail keeps separate.
- **Float add destination register**: func_0015D198 — `add.s $f1,$f1,$f0` vs `$f0,$f0,$f1`;
  operand order controls the loads, not the destination.
- **64-bit constant materialisation**: func_0015F0B0 / func_0015F4E0 / func_0017FBB0 (three
  identical GS-packet builders).  Retail `ori 0x8000; dsll32 13; ori 0x8001` is the
  assembler's `dli` macro; GCC emits `lui 0x1000; dsll32 0; ori 0x8001` under both the
  bundled `as` and `Ps2EeAs`.  Worth ~200 bytes if solved.

## Suspected translation units

- `0x00154398-0x001560xx` + `0x001584xx-0x00158Dxx` + `0x0015B970-0x0015D2xx`: one big
  object-slot unit over `D_002ABA40` (stride 0x40; quads at +0x00/+0x10, 64-bit flag word at
  +0x20 union'd with `Node *owner` at +0x24, `unsigned short id` at +0x36, byte fields at
  +0x2D..+0x30, +0x3B), the parallel `D_002CFA40` array (stride 0x20) and `D_002BDA40`
  (stride 0x40).  74 worklist functions, 29,788 bytes touch D_002ABA40.
- `0x001536A8` + `0x00179818-0x0017A5C0`: display-list cursor unit over `D_002D81B0`
  (`Prim *cursor` at +0x04, 0x10-byte primitives), calling func_001614F8/00161570/00161770/
  001615B0/00161870.
- `0x0017C240-0x0017CD50`: command/message unit.  Every member calls func_001987E0(D_001ECF60),
  packs a small struct on the stack and forwards it through func_0017C240(opcode, buf, size).
- `0x00179360-0x001793C0`: two-member wrapper family over `D_001ED880` (stride 0x2C records)
  forwarding into the 0x17C command unit.
