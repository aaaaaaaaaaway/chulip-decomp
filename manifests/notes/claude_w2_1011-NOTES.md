# Lane claude_w2_1011 notes

## Proven rules (this lane)
1. **addu operand order is set by the C type of the base, not by written order.**
   `int global + int offset` preserves the written order; a pointer-typed base is
   always emitted first. `func_0010E608` needed `extern int D_001ED160;` plus
   `*(int *)(in + D_001ED160)`; with `char *D_001ED160` the pointer went first and
   the bytes were wrong at every site.
2. **`p = base + index; p->field` vs `base[index].field`** decide the two-register
   `addu` order for a struct-array element whose base is a loaded pointer.
   `base[index].field` emits `addu rd, index*size, base`; the pointer temporary
   emits `addu rd, base, index*size`. `func_00100DA8` is the proof: same file,
   `base[index].field` in the two copy loops and `p = base + index` for the single
   probe read, word distance 1 -> MATCH.
3. Hoisting `i = 0;` above the guard `if` changes which instruction fills the
   guard branch's delay slot (`func_00100DA8`, word distance 4 -> 1).
4. A whole-struct assignment of a 12-byte struct compiles to the unaligned
   `ldl`/`ldr`/`sdl`/`sdr` block move; retail's `lw`/`sw` pairs come from
   member-by-member copies (`func_00110758`, distance 65 -> MATCH).
5. Two-case integer dispatch where the fall-through is the `return` is a
   `switch`, not `if`/`else if` (`func_00110D10`, distance 23 -> MATCH).
6. 64-bit GS/DMA tag *constants* are reachable: a `long` literal such as
   `0x1000000000008001L` compiles to retail's `ori`/`dsll32`/`ori` chain. The
   recorded blocker only covers 64-bit bitwise arithmetic on *variables*.
   (`func_00117508`.)
7. A loop bound read straight from a global in the `for` condition, with no
   local copy, is often required (`func_0011E9E0`, distance 10 -> MATCH).
8. **The "64-bit bitwise arithmetic is rejected" blocker is stale.** `long`
   variables shift and OR correctly under `ee-gcc2.95.3-136-O2-G8-ps2as`:
   `(long)(int_expr) | ((long)hi << 32)` reproduces retail's 32-bit `sll`/`or`
   chain plus `dsll32 rX,rX,0` and a final 64-bit `or`. Proven byte-exact on
   `func_00115E88` (GS tag builder, first try). Retest every function parked
   for "wide integer operation".
9. When a global base and a scaled index are added, BOTH orders can produce the
   same `addu` yet different register assignment. `D_GLOBAL + index * K` and
   `index * K + D_GLOBAL` are worth trying as a pair on every near-miss
   (`func_00112798`, distance 4 -> MATCH on the swap alone).
10. **Blocked, not wrong:** `tools/match.py`'s isolated linker script hardcodes
   `.sdata 0x001EC880`, so a translation unit can only *own* small data that
   actually lives at 0x1EC880. `func_001163B8` needs `D_001EC8BC`/`D_001EC8C0`
   (recorded in `.sdata` at 0x1EC8BC) GP-relative outside a delay slot, which
   only unit ownership gives; it reaches distance 2 with the right C and the two
   remaining words are the wrong `$gp` displacements. Same limit will hit any
   function touching owned `.sdata` above 0x1EC890.
11. **Do not give the scaled base its own local.** For the very common shape
   "compute `index * K + D_GLOBAL`, store a header, then loop", writing
   `base = index * K;` and reusing `base` makes GCC put the product straight
   into a callee-saved register; retail keeps it in the argument register for
   the header stores and only copies it into `$s2` for the loop. Repeating the
   whole expression `index * K + D_GLOBAL` at every site reproduces that.
   Proven three times: `func_00105C70` 23 -> 0, `func_0010D040` 66 -> 0,
   `func_0010C7E0` 37 -> 0 (980 + 540 + 492 bytes on one rule).
12. The productive shape in this band is "global pointer reloaded before every
   store". Because each store may alias the global, GCC cannot reorder them, so
   the RETAIL STORE ORDER IS THE SOURCE ORDER -- transcribe it literally and the
   function usually matches first try (`func_0010BA98`, `func_0010E6F8`,
   `func_00110020`, `func_00106338` all landed on the first attempt).

## Parked near-misses (source kept in near/)
| function | bytes | distance | blocker |
| --- | ---: | ---: | --- |
| func_00114340 | 300 | 2 | position of the outer `j+1` induction increment |
| func_00113670 | 160 | 2 | position of one `sll rX,rX,16` |
| func_0011ED48 | 208 | 3 | `$f0` vs `$f1` for one reloaded float |
| func_0010A030 | 352 | 2 | `addu` operand registers in the tail loop |
| func_001163B8 | 124 | 2 | needs unit-owned `.sdata` at 0x1EC8BC (linker script pins 0x1EC880) |
| func_0010F0F0 | 348 | 8 | counter/constant register assignment |
| func_00105A38 | 188 | 24 | the two blocks want opposite register assignment |
| func_00115C80 | 376 | 40 | s0-s5 allocation order across 12 stack arguments |
Also still parked from earlier attempts (no source kept): func_00108B10 (224, 25),
func_00112F40 (84, 6), func_0011E988 (88, 19), func_001131F0 (56, one extra
ps2as nop), func_00112F98 (56, 12), func_0010C9D8 (96, 24), func_001175B0 (196,
pointer-rebasing model not recovered).
