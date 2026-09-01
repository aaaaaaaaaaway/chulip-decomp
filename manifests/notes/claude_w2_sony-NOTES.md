# Lane claude_w2_sony — Sony EE GNU C 2.9-ee-991111-01 region (> 0x00185400)

Manifest: `work/claude/w2_sony.jsonl` (every entry `"profiles":["ee-gcc2.9-991111-01-O2"]`).
Result: 32 / 32 verified by `tools/batch_verify.py`; 5,744 exact bytes.
Near-misses (kept for the record, NOT in the manifest): `near/`.

## New rules proved in this region

1. **Uniform field types keep stores in source order.**  When two pointers with
   *different* struct types are stored through in one basic block, GCC's TBAA
   lets the post-reload scheduler permute the whole run.  Declaring every field
   of both structs as plain `int` (casting pointers in and out) puts them in one
   alias set and the stores come out in source order, which is what retail has.
   Proof: `func_0019B760` went 17 -> 8 word diffs on that change alone;
   `func_0019B6D0` (a previously recorded near-miss) matched exactly.
   This is the single highest-yield rule found this session — several of the
   earlier lanes' "retail keeps the stores in order, ours hoists" near-misses
   are this.

2. **A load that retail hoists above a store must be written into a local.**
   `p->a = src->a; p->b = src->b;` schedules load/store/load/store; retail has
   load/load/store/store.  Writing `x = src->a; y = src->b; p->a = x; p->b = y;`
   reproduces it exactly.  Proof: `func_0019B2D8` (8 diffs -> MATCH),
   `func_0019B6D0` (2 diffs -> MATCH).

3. **`p = obj = f()` and `obj = p = f()` are different code.**  C associates
   right-to-left, so `p = obj = f()` stores the call result register to memory
   and then copies, giving retail's `sw $v0`; `obj = p = f()` copies first and
   stores the copy, giving `sw $s0`.  Proof: `func_001975F0`, last word.

4. **`unsigned int` loop counters keep GCC's ascending `sltiu` compare.**  A
   signed `int` counter over a constant range is rewritten into a countdown with
   `addiu -1` / `bgezl`; the same loop with `unsigned int` keeps `addiu +1` /
   `sltiu` / `bnel`, which is what retail has.  This refines the earlier lane's
   "write loops ascending" note: ascending source is necessary but not
   sufficient.  Proof: `func_001A0A98` and `func_001A0F88`, both 11-12 diffs ->
   MATCH on the type change alone.

5. **Returning `-1` as `unsigned int` gives `lui`+`ori`; as `int` it gives
   `addiu`.**  Retail's `lui $v0,0xFFFF` + `ori $v0,$v0,0xFFFF` is an
   `unsigned int` (or `unsigned` field) carrying `0xFFFFFFFF`; a plain `int`
   `-1` is one `addiu`.  Proof: `func_001A0E98` (27 diffs -> MATCH).
   The same applies to masks: `& 0xFFFFFFFCU` gives `lui`+`ori`+`and`.

6. **`(x ^ K) == 0` gives `xori`+`beqz`; `x == K` gives `addiu`+`beq`.**  The
   soft-float classification code is full of retail `xori $v0,$v1,2` /
   `beqz`, which `x == 2` never produces.  Proof: `func_00186440` (4 diffs ->
   MATCH), `func_00187040` (MATCH first try once written that way).

7. **A shared tail must be written as a `goto`.**  Where two arms of an `if`
   end with the same operation on different registers, retail cross-jumps into
   one tail; writing `return d.value;` in both arms duplicates it.  Replacing
   the first arm's `return` with `goto ret_d;` reproduced retail exactly.
   Proof: `func_00197AF8` (10 diffs -> MATCH).

8. **The R5900 short-loop erratum padding is emitted by this compiler.**  Loops
   whose body is shorter than six instructions come out padded with bare `nop`s
   (e.g. `lw` / `nop` x3 / `bnez` / `nop`).  Earlier lanes recorded bare `nop`s
   as a structural blocker; in this region they are *automatic* and match from
   ordinary C.  Proof: `func_001A08D0` (MATCH first try, three padding nops).

9. **`tools/batch_verify.py` rejects any source containing the substring
   `.word`.**  That is a false positive on the newlib `ieee_double_shape_type`
   idiom `u.word.hi`.  Name the union member anything else (`parts`) — the C is
   unaffected and the gate passes.  This silently cost one verified function
   until it was found; worth knowing before writing soft-float code.

10. **Compiler-generated libcalls cannot be linked.**  Writing `r = r * 10.0;`
    on soft-float doubles makes this compiler emit `jal dpmul`, and the isolated
    linker only resolves names ending in an eight-digit address, so the
    candidate fails to link.  Call the runtime helper by its address name
    (`func_00185D78` = `dpmul`, `func_00186020` = `dpdiv`, `func_00185CB8` =
    `dpadd`, `func_001862F0` = `__floatsidf`) instead.

## Library families identified (with the reference implementations used)

* **newlib `mprec.c` (`_Bigint`)** — `{_next,_k,_maxwds,_sign,_wds,_x[]}`,
  `_reent->_freelist` at `0x4C`, `_reent->_p5s` at `0x48`.
  `func_00196F08` `_Balloc`, `func_00196FB0` `_Bfree` (near),
  `func_00196FE0` `__multadd`, `func_001970F8` `__s2b`, `func_00197240`
  `__hi0bits` (already done), `func_001972C8` `__lo0bits` (already done),
  `func_00197388` `__i2b`, `func_001973C0` `__multiply` (outside this worklist),
  `func_001975F0` `__pow5mult`, `func_001976F0` `__lshift`,
  `func_00197868` `__mcmp` (already done), `func_001978D0` `__mdiff`,
  `func_00197AF8` `__b2d`, `func_00197C78` `__d2b`, `func_00197DF8` `__ratio`,
  `func_00197EB8` the `tens[]`/pow10 helper (near, blocked on `dpmul`).
  `D_001EBFD0` is `p05[3] = {5,25,125}`; `D_001EBFE0` is the 24-entry `tens[]`
  double table.
* **newlib stdio** — `FILE` stride `0x58`, `_p` 0x00, `_r` 0x04, `_w` 0x08,
  `_flags` short 0x0C, `_file` short 0x0E, `_bf` 0x10/0x14, `_lbfsize` 0x18,
  `_cookie` 0x1C, `_read/_write/_seek/_close` 0x20..0x2C, `_ub` 0x30/0x34,
  `_up` 0x38, `_ur` 0x3C, `_ubuf` 0x40, `_lb` 0x44/0x48, `_blksize` 0x4C,
  `_offset` 0x50, `_data` 0x54.  `func_00192660` `sprintf`,
  `func_001925F8` `_sprintf_r`, `func_00193078` `__sbprintf`,
  `func_00193130` `_vfprintf_r`-shaped, `func_00195E48` `fflush` (near),
  `func_00196018` `__sfp`, `func_00195FA8` `__sfmoreglue`,
  `func_00196118` `__sinit`, `func_00196A10` `_fwalk`.
  `_reent`: `_errno` 0x00, `__sdidinit` 0x38, `__sglue` 0x1D8 (`{_next,_niobs,
  _iobs}`), `__sf[3]` 0x1E4.  `D_001E4EB4` holds `_impure_ptr`.
* **newlib `mallocr.c`** — `func_00191B38` `_malloc_r`,
  `func_00198140` `_calloc_r` (near; only the null-check branch form differs,
  the `MALLOC_ZERO` unrolled ladder at 5/7/9 words is exact).
* **Soft float** — a shared decomposed form
  `struct { unsigned cls; int sign; int exp; int pad; unsigned long mant; }`
  (16-byte-aligned, `mant` at 0x10) for doubles and
  `struct { unsigned cls; int sign; int exp; unsigned mant; }` for floats.
  `cls`: 0 = signalling NaN, 1 = quiet NaN, 2 = zero, 3 = normal, 4 = infinity.
  `func_001859D8` decomposes a double, `func_001866B0` a float,
  `func_001858A8` / `func_001865A0` repack.  Arithmetic kernels:
  `func_00185A78` double add, `func_00186740` float add, `func_00186C30` float
  divide, `func_00186188` / `func_00186D90` compare.
  Wrappers matched: `func_001862A0`, `func_00185CB8`, `func_00185D10`,
  `func_00186978`, `func_001869D0`, `func_00186EA8`, `func_00187140`,
  `func_00186440` (double->u32), `func_00187040` (float->u32).
* **SIF RPC / loadfile** — `func_0019B760` is `sceSifCallRpc`
  (`SifRpcClientData` = `{pkt_addr, rpc_id, sema_id, mode, command, buff,
  cbuff, end_function, end_param, server}`; `SifRpcCallPkt` = 16-byte
  `SifCmdHeader` then `rec_id, pkt_addr, rpc_id, client, rpc_number, send_size,
  receive, recv_size, rmode, server`).  `func_0019B0E8` get-packet,
  `func_0019B190` free-packet, `func_0019AE70` write-back-dcache,
  `func_0019ACC8` `SifSendCmd`, `func_001987A0/B0/E0` Create/Delete/WaitSema.
  Wrappers matched: `func_001A0258` (load-module), `func_001A03A8` (peek),
  `func_001A0498` (poke), `func_0019FDF0`.
* **EE SIO / kernel** — `func_00199E60` is `sio_putc` (0x1000F130 status,
  0x1000F180 TX); `func_001A08D0` scans the 0x80000000 kernel table.

## Suspected translation-unit groupings

* `0x00185810-0x00185D78` + `0x001859D8` + `0x001862A0`-`0x001862F0` +
  `0x00186440`-`0x00186548` — the **double** soft-float unit.  Shared
  `DoubleParts` layout, shared decompose/repack helpers, and the wrappers all
  call into `func_00185A78`/`func_001858A8`.
* `0x001865A0-0x00187140` — the **float** soft-float unit, same shape with
  `FloatParts` and `func_001866B0`/`func_001865A0`.  `D_002DE5F0` and
  `D_002DE608` are its two static NaN constants (referenced only from
  `func_00186020` and `func_00186C30`).
* `0x00196F08-0x00197DF8` — one **mprec** unit.  Every function takes the same
  `_reent *` first argument and they call each other exclusively; `D_001EBFD0`
  (`p05`) and `D_001EBFE0` (`tens`) are owned here.
* `0x00195E48-0x00196B98` + `0x00192598-0x00193130` — **stdio**.  `D_001E4EB4`
  (`_impure_ptr`) is shared across both; the `sprintf` family at `0x001924C8`,
  `0x00192508`, `0x001925F8`, `0x00192660` are consecutive and share the exact
  same stack-frame recipe (0xE0 frame, FILE at sp+0, va save area at the top).
* `0x0019F818-0x001A0578` — the **fileio/loadfile RPC** unit.  All of them
  share `D_002E3E80` (a single 0x200-byte command buffer whose split labels
  `D_002E3E80`/`D_002E3E88` are a disassembler artifact — retail forms one base
  register and reaches both) and `D_002E4080` (the `SifRpcClientData`).
  `D_001E5B94`/`D_001E5B98` are its init flags.
* `0x001A0988-0x001A1038` — a **resume/reinit dispatcher** unit; two nearly
  identical functions (`func_001A0A98`, `func_001A0F88`) over `{handle, arg}`
  tables `D_001E6360` and `D_001E66E8`.
* `0x001A16A0` and `0x001A1E80` are libgcc 64-bit divide/modulo helpers
  (`__udivdi3`/`__umoddi3` shape, sign-fixup preamble, no calls).

## Near-misses (in `near/`, all one to four words)

* `func_0019B760` (`sceSifCallRpc`, 492 B) — **2 of 123 words**.  Everything
  including the whole 12-store block, both `SifSendCmd` calls, the branch-likely
  layout and the cross-jumped failure tail is exact; only two adjacent client
  stores (`hdr.pkt_addr` and `hdr.rpc_id`) come out in the other order.
  Exhaustive over all 24 permutations of the four client stores, plus load
  temporaries, `volatile`, and pointer-vs-int field types.  Post-reload
  scheduling.
* `func_00195E48` (`fflush`) — one missing `nop` at the end of the
  `if (fp->_data == 0)` block; everything else including the `lh`/`lhu`
  distinction is exact.
* `func_00198140` (`_calloc_r`) — retail spends an extra word laying the
  `return 0` out as its own block reached by `bnel`; every structural spelling
  of the null check gives the tighter `beq` form.
* `func_00196FB0` (`_Bfree`) — 3 of 11 words; retail reuses the incoming `$a0`
  for the freelist base and emits `addu index, base`, ours allocates `$v1`.
* `func_0018E3C0` (`fabs`) / `func_0018EA78` (`copysign`) — one extra register
  copy; retail puts the `0xFFFFFFFF` mask in `$a0` and needs a second copy of
  the value, ours keeps the value in `$a0`.
* `func_00186188` / `func_00186548` / `func_00186C30` / `func_00194870` /
  `func_0019B990` / `func_00199E60` / `func_00197EB8` — see the per-file
  comments; all are cross-jumping or delay-slot-filler differences except
  `func_00197EB8`, which is blocked on the `dpmul` libcall name.

## Confirmed blockers in this band (do not re-attempt)

* `sync` (`func_00199420/440/460/480`, `func_00187A30`) — no natural C form.
* `cfc2.ni` / VU0 macro mode (`func_00187280`).
* EE MMI parallel ops (`func_001922B0`, `func_001926D0`, `func_00192940`,
  `func_00192A54`, `func_00192B90`, `func_001923F4`, `func_00196D24`,
  `func_00196E04`, `func_001927FC`, `func_00192344`, `func_001871E0`).
* `func_0019AF1C` — 4 bytes, bare `jr $ra`, no body can produce it.
