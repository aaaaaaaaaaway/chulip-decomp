# Band 0x00190000-0x001A1FFF lane notes

Manifest: work/claude/band19.jsonl (67 entries, all MATCH under ee-gcc2.95.3-136-O2-G8,
no extra object flags needed anywhere in this band).

## Proven general rules (new)
1. `long long` is 16 bytes on this compiler, `long` is 8, pointers 4.
   A retail `sd`/`ld` field must be spelled `long`; `long long` produces `por`+`sq`.
   Proof: func_00198F58.
2. Trailing run of N independent stores: source order (A,B,C,...,F) is emitted as
   (F, A, B, ... ) with the second-to-last source store landing in the `jr $ra`
   delay slot. Reorder the source, not the struct. Proof: func_00195F50 (6 stores),
   func_00199940 (4), func_0019AB08/func_0019AB20 (2).
3. A retail `lui`+`ori` materialisation of a 0xFFFFxxxx mask means the C operand is
   `unsigned`; a signed operand yields `addiu $r,$zero,-N` instead. Proof: func_0019B190.
4. `extern T D_x[];` (unsized array, indexed [0]) is the spelling that reproduces
   `lui %hi` + `%lo(...)` for a scalar global; the same address declared as a plain
   scalar becomes gp-relative. Used throughout this band.

## Blockers (do not re-attempt with the current profiles)
This band is SDK/libc/libm/stdio, and most of it was built with a *different* compiler
than the proven game profile. Two independent signatures:
* frameless sibling calls: retail ends with `... ld ra; j callee; addiu sp` (or a bare
  `j callee` with no frame at all). Neither SN 2.95.3-136, SN 2.95.2-273a nor ee-gcc2.96
  emits this (2.96 emits a sibcall only with -foptimize-sibling-calls and still saves $ra).
  24 remaining functions.
* callee-saved register width: retail saves `sd $s0,0x0($sp)` / `sd $ra,0x10($sp)`;
  our profile always emits `sq $s0` (128-bit) at a different slot. 155 remaining
  functions. cc1.exe has a `register_precision` pragma token but no accepted syntax
  and no -m flag exposes it; -mgp64/-mgp32/-mfp32/-msoft-float do not change it.
* varargs FP save area: retail allocates the 0x20-byte FP save slot but never stores
  $f12..$f19; our compiler stores them (-msoft-float removes the allocation too).
  Blocks the printf-family forwarders (func_0019A740, func_001924C8, func_00192508,
  func_001925F8, func_00192660).
* EE MMI block move/compare (`lq/sq/pcpyh/pcpyld/pcpyud/pxor`) in memcpy/memset/memcmp:
  func_00192344, func_001923F4, func_001922B0 - not expressible as natural C.
* Handwritten-looking load-delay nop padding: func_001A08D0, func_00199E60 (SIO putc).

## Near-matches (semantics believed correct, one codegen detail off)
* func_0019AB68 / func_0019AB38 - identical instruction sequence, register allocation
  differs ($a0 vs $v0 for the loaded table base).
* func_001A06B8 - retail `lui $v1,1; and; sltu $v0,$zero,$v0`; gcc folds
  `(x & 0x10000) != 0` to `srl 16; andi 1` under every spelling tried.
* func_00192FF8 / func_0019ACC8 / func_0019AD08 - only the position of `addiu $sp`
  inside the argument-shuffle prologue differs.
* func_0019B950 - retail keeps two separate `jr $ra` return blocks with empty branch
  delay slots; gcc fills the branch delay slots from the target block.
* func_001994C0 / func_001A09E8 / func_001A0F30 (word copy loop) - retail leaves the
  loop-back branch delay slot empty; gcc fills it with the destination increment.
* func_001A0C58, func_00192D50 (strstr), func_00197868 (word-array compare).
