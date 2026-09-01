# Rules proved in lane claude_largeA

## R1 — Per-statement reload of a pointer global == one-element array of pointers
Retail shape:
    lui $vN,%hi(D_x); lw $vN,%lo(D_x)($vN)     (same register, pseudo form)
repeated once per *statement*, with CSE only across statements that contain no store.

`extern T *D_x;` NEVER reproduces this: GCC 2.95.3-136 fully CSEs a *scalar* global
pointer across intervening pointer stores (verified probe: three stores, one load).
`extern T *D_x[];` (unsized) reloads but hoists the `lui` into a shared base register.

`extern T *D_x[1];` (or [2]) is the spelling that matches:
  - 4/8 bytes  -> compiler emits the small-data pseudo -> assembler -G0/-G4 expands it
    to lui+lw in the SAME register, exactly as retail;
  - the access is an ARRAY REF, so GCC treats it as aliasing pointer stores and
    reloads it after every store, while still CSE-ing it inside a store-free run.
Use `D_x[0][i].field`.
Proved byte-exact on func_0010BF20 (548 bytes) with -Wa,-G0.

## Parked: func_0012D180 (832 bytes)
near/func_0012D180.c. Whole function matches structurally (frame, all blocks,
all branch offsets) except one register-allocation placement at +0xDA:
retail keeps `lui %hi(D_001FDB00)` in $v1 and copies it to $s3 *inside* the loop
preheader (after `beqz`), filling the branch delay slot with `i = 0`.
The candidate emits the copy before the branch, so the delay slot takes the copy
and the two temporaries swap $v0/$v1. Instruction count and everything else agree.

## R2 — signed `slt` pointer-walk loops come from INDEX loops, not pointer loops
Retail shape: `addiu $rEnd,$rBase,N*stride` then a walk with `slt` (SIGNED) and
no entry guard.  Writing the C as `for (p = T; p < T + N; p++)` gives `sltu`
(pointer compare is unsigned) plus a redundant `sltu`/`beq` entry guard.
Write `for (i = 0; i < N; i++) T[i].f` instead: GCC strength-reduces the index
into a pointer walk but keeps the original SIGNED comparison and drops the guard
because `0 < N` is a compile-time fact.
Corollary: if `i` is still live after the loop (`break` then `if (i < N)`),
strength reduction does NOT happen and the retail loop keeps the `slt $r,$i,N`
counter form.  So the retail loop form *tells you* whether the index is used
after the loop.  Proved on func_00158018 (568 bytes), which contains both forms.

## R3 — `(base + index)->field` vs `base[index].field`
If retail keeps the field displacement in the load/store (`lw $v0,0x4($a0)`)
and adds only `sll`+`addu`, use `(D_x + i)->field`.  `D_x[i].field` makes GCC
fold the field offset into the symbol base (`addiu %lo` then `addu $r,$r,4`),
which costs an extra instruction and can duplicate the `lui`.
Proved on func_00158018 (D_002CFA40).

## R4 — a local temp for an intermediate pointer load changes register allocation
`h->node->flags |= 0x20;` allocated the node pointer over the `%hi` base register
and forced GCC to duplicate the `lui`. Splitting to
`node = h->node; node->flags |= 0x20;` freed the base register and matched retail.
Proved on func_00158018.

## Parked: func_0015E198 (636 bytes)
near/func_0015E198.c. 157 of 159 words, whole structure and frame correct.
Remaining: the final 3-iteration loop. Retail carries three givs
(p += 0x40, unk2D0 pointer += 4, and `slot*0x348 + i*4` += 4 combined with the
loop-invariant `base + 0x2C4`) plus a separate countdown counter (`addiu -1`,
`bgez`); the candidate keeps `i` itself live for the exit test (`slti i,3`),
so GCC never reverses the loop. Also two prologue `sq`/`addiu %lo` instructions
are swapped relative to retail.

## Parked: func_00135020 (640 bytes)
near/func_00135020.c, profile ee-gcc2.95.3-136-O2-G8-ps2as with -Wa,-G0.
Exactly 160/160 words; six words differ, all pure register allocation:
retail copies `&D_001ED368` through $a0 into $s5 (`addiu $a0,%lo` + `daddu $s5,$a0`)
where the candidate writes `addiu $s5,$a0,%lo` directly, and retail computes
`records + entry` straight into the argument register $a3 where the candidate
uses a temp plus `move $a3,$v1`. Everything else (all four gp-relative
delay-slot stores, the absolute `lui $at` store, block layout) matches.

## R5 — D_001ED364-style symbols that show BOTH addressing modes need `ee-gcc2.95.3-136-O2-G8-ps2as`
Confirmed again on func_00135020: every `%gp_rel` store sits in a branch/jal delay
slot and every non-delay-slot access is absolute, from one `extern int` decl.

## R6 — `lui`+`ori` for -1 means the compared value is UNSIGNED
`addiu $r,$zero,-1` is what you get comparing a signed int against -1.
Retail's two-instruction `lui $v1,0xFFFF` + `ori $v1,$v1,0xFFFF` appears when the
operand type is unsigned and the literal is written `0xFFFFFFFF`.
Declare the struct field `unsigned int` and write `== 0xFFFFFFFF`.
The same function keeps `addiu -1` for genuinely signed neighbours, so the two
forms coexist and the retail encoding tells you the field's signedness.
Proved on func_0011E540 (468 bytes).

## R7 — a `short` parameter costs `sll 16`/`sra 16` at entry
Retail entering with a bare `daddu $tN,$a1,$zero` and only ever storing the value
with `sh` means the C parameter is `int`, not `short`. Proved on func_0011E540.

## Parked: func_0017EFE0 (396 bytes) — toolchain gap, not semantics
near/func_0017EFE0.c. Retail needs D_001ECF70 (4-byte pointer) GP-relative at
*every* site while D_001ED940 (8-byte) is absolute except in delay slots, i.e.
assembler -G4 plus Ps2EeAs delay-slot behaviour.  But `Ps2EeAs.exe` as invoked by
`tools/match.py` (`assemble_with_bundled_assembler` passes a single `-G4` token)
produces byte-identical output for -G0/-G4/-G8, so it appears to ignore that
option spelling; with it, D_001ECF70 comes out absolute and the function cannot
match. GNU `as` -G4 gets the addressing right but expands the two delay-slot
pseudos as two-instruction macros. Needs an assembler-option fix, not a source fix.

## Parked: func_0010E978 (328 bytes)
near/func_0010E978.c, 82 vs 86 words, all blocks and both float constants correct.
R1's one-element-array spelling reloads the pointer global per statement in straight
line code and inside the innermost loop, but GCC still hoists the load out of the
MIDDLE loop, and once hoisted it materialises `addu $r,$r,0x50` instead of keeping
0x50 as the load displacement (+1 word, +1 alignment nop, twice). `volatile`
overshoots (reload per access, 93 words). Needs a spelling that blocks
loop-invariant motion without blocking per-access CSE.

## Parked: func_00138798 (352 bytes)
near/func_00138798.c, 88/88 words, first 37 identical.
Remaining: retail materialises the `0x24` element-size constant *late*, in $v0, and
GCC's delay-slot filler then duplicates it into three places, letting the
`if (index == D_00203C00[3])` test use an ordinary `bne`.  The candidate hoists
that constant into $a1 once, so the same test comes out as `bnel` and the tail
block layout shifts.  Everything else (both unlink branches, all four flag tests,
the `0xFFFFFFFF` and `~2` masks) matches.

## R8 — comparison operand order is preserved
`if (index == D_00203C00[2])` gives `bne $index,$loaded`; writing it the other way
round gives `bne $loaded,$index`. Retail's rs/rt tells you which side the source
wrote first. Proved on func_00138798 (+5 words of prefix from the swap alone).

## Parked: func_00172628 (380 bytes)
near/func_00172628.c, 95 retail words vs 94; ONE instruction short.
Retail carries a redundant `daddu $a0,$v1,$zero` copy of the loaded `unk04`
before the `& 0x1000000` test (the copy is immediately overwritten by the
`beql` delay slot, so it is pure register-allocation noise). Every branch,
call and mask matches after applying R8/R9.

## R9 — if/else block order tells you which side the source wrote as the `then`
GCC lays the `then` block inline and branches to the `else`. Retail branching
AWAY on `!= 0` means the source tested `== 0` with the bodies swapped.
Inverting three `if ((x & M) != 0) {A} else {B}` into `if ((x & M) == 0) {B} else {A}`
took func_00172628 from 90 to 94 of 95 words. The same applies to `&&`:
retail's `if (!A) goto Y; if (B) goto X; Y...; X:` is `if (!A || !B) { Y } else { X }`,
not `if (A && B) { X } else { Y }`.

## R10 — a `long` (8-byte) argument changes argument-setup scheduling
func_00182490 is byte-identical except for one instruction when the third
parameter of `func_00182210` is prototyped `int`; declaring it `long` moves the
`ori` of the 0x71001 literal ahead of the `li $a1,0x47` exactly as retail does,
and the function matches. When one argument-setup instruction is out of order
and nothing else is, try widening that parameter to `long`.

## R11 — pointer difference: retail's signed divide tells you the C type
`p - packet` on a 16-byte struct pointer compiles to a bare `subu` (GCC knows the
difference is exact). Retail's `subu` + `slti -1` + `addiu 15` + `movn` + `sra 4`
is a *signed division by 16 of a byte difference*, i.e. the C uses `char *`
pointers advanced by `n * 16` and returns `(p - packet) / 16`.
Proved on func_00182490.
