# Lane claude_c11 notes  (band 0x00110000-0x0011FFFF)

Manifest: `work/claude/c11.jsonl` (26 entries, all MATCH under
`tools/batch_verify.py`, report in `final_report.json`).
Fourteen further worklist functions were verified from prior-lane sources but
were integrated upstream by the coordinator mid-session and were removed from
the manifest as duplicates.

## New rules proved in this lane

1. **A MULT_EXPR as the second addend of an address sum is canonicalised to the
   front.** `base + i * K` emits `addu rd, i*K, base`; retail's
   `addu rd, base, i*K` needs `ofs = i * K;` in its own local. This is the
   *exception* to lane w2_1011's rule 11 ("do not give a scaled base its own
   local"): that rule is about the object base (`index * K + D_GLOBAL`), this
   one about a second, inner index. `func_00110810` proves both in one body -
   the outer `index * 0x1320 + D_001ED17C` must be repeated at every site while
   the inner `i * 0x30` must be a local. Distance 11 -> 8 on the local alone.
2. **Where that local is assigned inside the loop is a scheduling knob.**
   With `ofs = i * 0x30;` first, GCC hoists the `mult`/`i++` pair to the loop
   top (distance 21). Computing one value before it (`r = rand() - rand();`)
   and assigning `ofs` after moves the pair to retail's position:
   `func_00110810` 21 -> 8 -> MATCH.
3. **A constant retail keeps in a callee-saved register across calls must be a
   source local assigned before those calls.** `func_0011A5F0` holds `0x8FFF0`
   in `$s3` across `func_00158908`/`func_0018AED0`; with the literal written
   inline in the loop GCC materialises it after the calls in a caller-saved
   register. Adding `depth = 0x8FFF0;` before the calls: distance 65 -> 18.
   (Loop-invariant constants that only live inside a loop containing calls are
   hoisted to callee-saved registers automatically - no local needed.)
4. **The `void`-vs-`int` prototype rule extends to floats.** Declaring a
   discarded call's result `float` rather than `void` makes GCC treat `$f0` as
   clobbered, so the next float load lands in `$f1` and cannot be reused across
   a branch. `func_0011ED48`: `void func_00105150(...)` -> `float
   func_00105150(...)` turned distance 3 into MATCH.
5. **A result variable held in a callee-saved register needs a single-exit
   function.** `func_00119678` returns `$s6`; with `return 0;` / `return 5;` at
   two sites GCC constant-folds both and drops the register (and one callee
   save, shrinking the frame). Wrapping the tail in
   `if (a && b) { ...; used = 5; } return used;` -> MATCH.
6. **`u + w - 8` has four spellings and only one schedules like retail.**
   `sprite->u - 8 + sprite->w` matched; `(w-8)+u`, `u+(w-8)`, `u+w-8` and
   `w+u-8` all differ (`func_00117E58`, 8 -> MATCH).
7. **Independent quad groups in a GS packet are written UV-group-first.** All
   four sprite builders emit the four texture-coordinate quads (`+0x00`,
   `+0x20`, `+0x40`, `+0x60`) before the four vertex quads (`+0x10`, `+0x30`,
   `+0x50`, `+0x70`). Transcribing in ascending address order costs ~80 words.

## Retired blockers (confirmed here)

- **Jump-table switches are matchable now.** `tools/match.py` places compiled
  `.rodata` at the derived `jtbl_` address and reports whether the table bytes
  agree. `func_00118600` matched with its five-case switch and
  `jump table at 0x001E6BE0: 32 bytes MATCH`.
- **The `.sdata`-ownership blocker (w2_1011 note 10) is retired.**
  `tools/match.py` gained `--sdata-start` / `--sbss-start` and derives the
  address from the `D_` symbols the source defines. `func_001163B8` and
  `func_001172F0`, parked for exactly this reason, now match unchanged - they
  only needed the `--range-end` extension for the `Ps2EeAs` eight-byte pad.
- 64-bit `long` GS/GIF tag literals reproduce retail's `ori`/`dsll`/`ori`
  chains everywhere in this band (`0x1000000000008001`, `0x4024C00000008001`,
  `0x90AA400000008001`, `0x434343431`, `0x8000000044`, `0x51001`).

## Suspected translation units

| range | shared data / calls | note |
| --- | --- | --- |
| `0x00110020-0x00112AE8` | `D_001ED170`-`D_001ED1A8`, `func_00113228`, `func_00120BE0`, `func_00192568` | particle-pool family: five `(spawn, update, draw)` triples, one per pool. `func_00110810`/`func_00112860` are the two spawn routines and are near-identical; `func_00110298` is the pool tick; `func_00112AE8`/`func_00110D70`/`func_00112208`/`func_001114F8` are the four draw routines and share one body shape. |
| `0x00113228-0x00114B38` | `D_001EC8A0-D_001EC8C0` (`.sdata`), `D_001ED1B0`-`D_001ED1BC`, `D_001EEBE0`/`D_001F6BE0` draw queues | draw-command queue + DMA packet helpers; owns the `.sdata` words at `0x001EC8A0`-`0x001EC8C0`. |
| `0x00115490-0x001163B8` | `D_001E6AF0`/`D_001E6B10`, `D_001ED1C8`-`D_001ED1E8`, `D_001EC8BC`/`D_001EC8C0` | HUD/meter unit; also owns `.sdata` at `0x001EC8BC`. |
| `0x00116438-0x001179xx` | `D_001ED1DD`-`D_001ED1F0`, `D_001F9DC0`/`D_001F9DD0`, `D_001EC8C0`/`D_001EC8C4` | second HUD unit (`func_001172F0`, `func_00117290`, `func_00117138`, `func_00116F90`, `func_00117360`). |
| `0x00117E58-0x00118C70` | no globals except `D_001ED1F4`; `func_0018AED0`, `func_0018B210`, `func_0018B2F8` | **sprite/quad packet builders**: `func_00117E58` (2D quad), `func_00118058` (rotated quad), `func_00118380` (transformed quad), `func_00119840` (top-left quad, in the next unit but byte-identical shape), plus the effect spawner `func_00118600`/`func_00118890` pair over `D_001ED1F4` (stride `0x45C0`). |
| `0x00119678-0x0011A820` | `D_001EDCC0` (matrix), `D_001FA200` (slot table, stride 16), `func_00158908`, `func_00117E58` | screen-effect drawers dispatched by `func_00119BB8` via `D_001ED1FC`/`D_001ED200`. `func_00119678` is a line-strip builder, `func_00119FA0`/`func_0011A5F0`/`func_0011A198`/`func_0011A3D8`/`func_00119D98`/`func_0011A820` are per-effect drawers. |
| `0x0011AA88-0x0011DBF0` | `D_001ED1F8`-`D_001ED210`, `D_001FA340`-`D_001FA374` | actor state machines; `func_0011AE00` dispatches to `func_0011B020`, `func_0011BB90`, `func_0011C740`, `func_0011CE70`, `func_0011DBF0` (13,156 bytes, untouched). |
| `0x0011E3B0-0x0011FC68` | `D_001ED218`-`D_001ED23C`, `D_001FA9D0`/`D_001FA9D4`/`D_001FA9E8` | linked-list scheduler + cutscene driver; `func_0011E718` is the unlink, `func_0011FB50` registers `func_0011FC68` as a callback. |

## Parked near-misses (sources kept in `near/`)

| function | bytes | distance | blocker |
| --- | ---: | ---: | --- |
| func_00112AE8 | 968 | 226 | draw-loop body shape not recovered; header `sd` order and one extra copy of the packet pointer |
| func_00118058 | 804 | 139 | register allocation across the four `sin`/`cos` calls; two `Ps2EeAs` hazard nops before `div.s` land elsewhere |
| func_00119FA0 | 504 | 66 | order in which GCC hoists the four loop constants (`3`, `0x78`, `-0x6C`, `2`) into `$s6`/`$s3`/`$fp`/`$s5` |
| func_00110298 | 340 | 47 | innermost loop wants a byte-offset induction variable with `+0x30` materialised, not folded into the load offset |
| func_0011FB50 | 224 | 30 | `D_001ED230` must be reloaded from memory on every loop iteration; GCC keeps it in a register |
| func_0011E718 | 216 | 18 | two rematerialised constants in the branch tails (register pressure) |
| func_0011A5F0 | 560 | 16 | prologue register naming only; instruction stream is identical |
| func_0011EE78 | 204 | 16 | evaluation order of the two `int`->`float` conversions feeding `func_0014D568` |
| func_00117290 | 92 | 15 | one extra `Ps2EeAs` nop in the clear loop (retail has one, ps2as gives two, GNU `as` gives none) |
| func_00113670 | 160 | 2 | position of one `sll rX,rX,16` (inherited from lane w2_1011) |
| func_00114340 | 300 | 2 | position of the outer `j+1` increment (inherited from lane w2_1011) |

`func_00117290`, `func_001131F0` and `func_00112F98` share one unexplained
symptom: retail has exactly one `nop` before a loop back-branch, `Ps2EeAs`
emits two and GNU `as` emits none. No loop spelling tried changes it.
