# Near-misses (lane claude_sdkA)
- func_0018E5D0 (isnan) / func_00197F28 (isinf): every instruction and register
  agrees; only the position of the high-word `dsra32 $a0,$a0,0` differs (retail
  3rd, compiler 6th). Invariant across 9 source shapes (union field order,
  declaration order, folded mask, unsigned types, pointer-cast __HI/__LO,
  split `lx |= -lx`). Post-reload scheduling, not semantics.
- func_0018A680 / func_0018A690: qword copy (`lq`/`sq`). `mode(TI)` gives the
  right opcodes but retail allocates $a2..$t1 with all loads hoisted before all
  stores; every probed shape allocates $v0/$v1 (interleaved) or $v0,$v1,$a2,$a3.
- func_0019C398: whole body correct; retail allocates the loaded `D_001E5B84[0]`
  to $v0 and the `-1` literal to $v1, the compiler does the reverse, and the
  trailing store/return pair picks up two extra `move`s.
- func_001A0C58: identical instruction multiset and store order (4,0,8,C); the
  post-reload scheduler places `andi` one slot early (before `lui 0x2000`
  instead of after `addiu %lo`). Not reachable from source order.
- func_0019AF1C: 4 bytes, a bare `jr $ra` with no delay-slot nop. No C body can
  produce a 4-byte function; the following function's first word serves as the
  delay slot. Structural, not a source problem.
- func_0019B950: three-test predicate; retail keeps `return 0` as the shared
  fall-through with `return 1` out of line and a nop in every delay slot. Both
  the nested-if and the short-circuit && spellings give a tighter two-block
  form with the constant hoisted into a delay slot.
- func_0019BF68: everything matches after prototyping func_0019BE80 as
  `(void)`; only the `sltiu`/`bnez` pair lands in $v0 instead of retail's $v1.
  Invariant under `>= 0x20`, `> 0x1F`, signed/unsigned index.
- func_00198DE8: same instruction sequence; retail allocates $s1 to `arg0` and
  $s0 to the D_001E5338 base, the compiler swaps the two (so the prologue saves
  and the bnez delay slot pair up differently).
- func_0018EF48: only the delay-slot choice inside the guarded block differs.
  Retail emits `sw -1, D_001E3194` then puts `lw a0, D_001E3160` in the jal
  delay slot; the compiler emits the load first and sinks the store. The two
  globals are provably distinct symbols, so no source order or `volatile`
  qualifier reorders them.
- func_0018EEB0: two delay-slot picks differ. Retail puts `sw v0,D_001E3168`
  in the second jal's delay slot and interleaves the trailing `lui`/`sw`
  pairs; the compiler emits the store ahead of the call, fills the slot with
  `move a0,sp`, and hoists both trailing `lui`s. Everything else matches.
- func_00189290 note: proved that an ascending `for` is required -- GCC
  reverses the counter itself while keeping an ascending, biased address
  induction variable. A descending source loop gives a descending cursor.
- func_001888C8: DMA D_CTRL (0x1000E060) read-then-conditional-write. Retail
  loads the discarded value into the same register that holds the address and
  keeps the parameter in $a0; every spelling of the discarded volatile read
  allocates the load to $a0 and copies the parameter to $a1 first.
- func_0019AB38: retail hoists `dsll $v1,$a0,3` into the `bgez` delay slot so
  the table load can overwrite $a0. With `int` or `long` index the shift stays
  after the table select and the index is copied first.
- func_0019BEE0: exactly one word differs -- retail materialises the
  D_002E3A00 base with `lui $v1` and the compiler uses `lui $v0`. Identical
  under pointer-limit, index and while-loop spellings. Same $v0/$v1 scratch
  choice that blocks func_0019BF68.
- func_0019B4E0: retail copies the func_0019B1B0 result into $s2 immediately
  after the call and then loads the source fields; the compiler issues the
  first field load first. All six store orders and both if polarities tested.
- func_0019C428: body correct but retail's frame is 0x60 (s0-s4 saved) and the
  compiler's is 0x40. Retail keeps BOTH the `lui %hi(D_002E3C80)` register and
  the full `%lo`-added base live across the three calls; every spelling tried
  (unsized array of pointers, struct pointer, local base) lets the compiler
  rematerialise one of them.
- func_001889C8 / func_00188B98 (and siblings): a spin-wait with a countdown
  from 0xFFFFFF containing an inner `v0 = 0; nop; nop; bnez v0` loop whose
  condition is a compile-time zero, plus two bare hazard nops. That shape is
  not reachable from natural C (same class as the func_001016A0 hazard-nop
  blocker) and was not attempted further.
- func_001923F4 (memset) and func_0018A4D0: EE MMI (`pcpyh`/`pcpyld`/
  `pextlw`/`pextuw`) with `sq` stores. `mode(TI)` reaches `lq`/`sq` but not the
  parallel-copy opcodes.

## Toolchain note (retracted claim)

Mid-session I believed `tools/match.py`'s fallback to modern `mipsel-linux-gnu-as`
encoded the compiler's `move` pseudo as `or` (0x25) where retail has `daddu`
(0x2D), and I built a lane-local mirror of match.py that used the unused
`tools/compilers/ee-gcc2.9-991111-01/ee/bin/as`. That is NOT needed: with clean
build directories, the stock `tools/match.py` encodes `move` as `daddu` for
every one of the 47 candidates (gcc's own output carries the EABI64 marker).
All 47 were re-verified serially through the unmodified harness after deleting
`build/match/<func>`, and `tools/batch_verify.py` reports 47/47. The mirror was
deleted. If a future function ever does need the era assembler, it is at
`tools/compilers/ee-gcc2.9-991111-01/ee/bin/as` (i386 ELF, run through
`tools/compilers/runtime/root/usr/lib32/ld-linux.so.2`, then repair its ELF
with `objcopy --remove-section=.mdebug` before linking).
