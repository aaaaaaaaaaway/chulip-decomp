# Lane claude_c19 — Sony EE GNU C 2.9-ee-991111-01 band, 0x00190000-0x001A1FFF

Manifest: `work/claude/c19.jsonl` (every entry `"profiles":["ee-gcc2.9-991111-01-O2"]`).
Result: **41 / 41 verified** by `tools/batch_verify.py`; **13,624 exact bytes**
out of the 117-function / 52,976-byte worklist.
Near-misses (NOT in the manifest) are in `near/`.

## New rules proved in this lane

1. **`if (x < 0) return x; return 0;` gives `li -1` + `slt` + `movn`; the ternary
   `(x < 0) ? x : 0` gives `slti` + `movz`.**  GCC folds the *ternary* boundary
   (`x > -1 ? 0 : x` becomes `x > 0 ? 0 : x`) but leaves the two-return `if`
   alone, so the reversed `GT -1` reaches mips.c's `gen_int_relational`, which
   swaps the operands and forces the constant into a register.
   Proof: `func_0019CA00` (2 words -> MATCH).  Same mechanism as the already
   matched `func_001A0498`.

2. **Spelling decides the addressing form of a global struct field.**
   `D_002E2940.field = x;` emits the one-instruction `%lo(sym)($hi)` form;
   `pkt->field = x;` (through a local pointer initialised to `&D_002E2940`)
   emits `0(base)`.  Retail mixes both inside one function, and reproducing the
   mix needs both spellings in the source.  Declaring the pointer local
   *at the top of the function* is also what makes GCC materialise the base in
   the prologue and keep it live across every call.
   Proof: `func_0019CA00`, `func_0019CB80` (frame size 0xB0 -> 0xC0 on the
   `pkt->sema` change alone).

3. **An out-of-line retry/spin block needs an explicit `goto`.**  A
   `for (;;) { if (bind() < 0) return -1; if (ok) break; spin; }` lays the spin
   loop inline; retail places it after the success block and jumps back.  Only
   `if (!ok) goto spin; ... return 0; spin: <delay>; goto retry;` reproduces it.
   Proof: `func_0019F818` (57 word diffs -> MATCH).

4. **Duplicating a whole indexed store into both arms lets GCC hoist the index
   scaling into the branch delay slot and cross-jump the tail.**
   `if (i<0) base=A; else base=B; base[i].a=0;` keeps the `sll` after the
   select; `if (i<0) A[0][i].a=0; else B[0][i].a=0;` gives retail's
   `bgez` / `sll` delay-slot pair plus a single shared `addu`+`sw` tail.
   Proof: `func_0019AB68`, `func_0019AB38` (this retires the `func_0019AB38`
   near-miss recorded by lane `claude_sdkA`).

5. **Assigning a masked parameter back to itself before storing it changes
   register allocation.**  `pkt->f8 = flags & 7;` uses one fewer callee-saved
   register than `flags = flags & 7; pkt->f8 = flags;`, which is what retail
   has.  Proof: `func_00191150` (frame 0x90 -> 0xA0, MATCH).

6. **`extern int func(...)` vs `extern void func(...)` for a discarded result
   moves a scratch register.**  `func_0019AE70` had to be `void` in
   `func_0019D638` and `func_00192B90` had to be `int` in `func_00190F70`;
   each was the single remaining word.

7. **The block whose value is returned by the *fall-through* path must be
   written first.**  Three functions needed the `if` inverted so that the
   common path falls through and the error/`return 0` block is out of line:
   `func_0019B590` (48 diffs -> MATCH), `func_001A0578` (16 diffs -> MATCH),
   `func_0019F818`.

8. **`(unsigned char)` vs `(char)` array element decides the string-copy loop
   shape.**  `if ((pkt->name[i] = path[i]) == 0)` with a `char` destination
   emits `sll rX,rX,24` + `bnel`; with `unsigned char` it emits a bare `bnez`
   with the `sb` in the delay slot.  Both forms occur in this band.
   Proof: `func_0019D818` (char) vs `func_0019E2E8`, `func_0019E488` (unsigned).

9. **Confirmed:** the "load retail hoists above a store must be written into a
   local" rule from lane `claude_w2_sony` was needed four more times
   (`func_0019E190`, `func_0019D638`, `func_0019D2E8`, `func_0019CB80`).

10. **Sony EE `cc1` 2.9 has no `__builtin_va_list` / `__builtin_stdarg_start`
    and its `__builtin_saveregs` is an out-of-line libgcc call.**  A stdarg
    function's GPR save area sits 0x30 bytes *below* what
    `__builtin_next_arg()` returns, so no natural spelling reaches the first
    vararg.  This blocks `func_0019C778` (`open`, 644 B) — see `near/`.

## Library families identified

* **newlib stdio** — `FILE` stride 0x58 (`_p` 0x00, `_r` 0x04, `_w` 0x08,
  `_flags` u16 0x0C, `_file` s16 0x0E, `_bf` 0x10/0x14, `_lbfsize` 0x18,
  `_seek` 0x28, `_ub` 0x30/0x34, `_ubuf` 0x40, `_nbuf` 0x43, `_lb` 0x44/0x48,
  `_blksize` 0x4C, `_data` 0x54); `_reent` `_errno` 0x00, `__sdidinit` 0x38,
  `__cleanup` 0x3C, `__sglue` 0x1D8.
  `func_00196018` = `__sfp`, `func_00196B98` = `__smakebuf_r`,
  `func_00194950` = `__swsetup_r` (near), `func_00193130` = `vfprintf` (near),
  `func_00196CE8` = `__ascii_mbtowc` (near), `func_001961A8` = `_free_r`,
  `func_00191B38` = `_malloc_r`, `func_00195FA8` = `__sfmoreglue`,
  `func_00196118` = `__sinit`, `func_00198258` = `_fstat_r`,
  `func_00198F50` = `_isatty_r`, `func_001960F8` = `_cleanup_r`.
* **newlib mprec** — `func_00197A60` = `ulp()` (matched); the double is held in
  one GPR, so `word0`/`word1` are the high/low halves of a
  `union { double d; struct { unsigned lo, hi; } parts; }`.
* **soft float** — `func_001862A0` compare, `func_00185D78` mul,
  `func_00185D10` sub, `func_00185CB8` add, `func_00186020` div,
  `func_00186440` double->u32, `func_00185810` `__floatdidf`.
  `func_001A1D90` is `__fixunsdfdi` (near, 18 words of register naming);
  `func_00199F80` is a double->4-digit helper (near, one delay slot).
  A `(double)(unsigned long long)` conversion has to be written out by hand
  (`(x>>1)|(x&1)`, convert, self-add) because the libcall name cannot link.
* **EE `memcpy`** — `func_00192344`: >=0x20 bytes and 16-byte-aligned uses two
  `lq`/`sq` per iteration (reachable with `int __attribute__((mode(TI)))`),
  then an 8-byte `ld`/`sd` loop, then a byte tail.  Near (2 words: a live-range
  split of the destination cursor).
* **SIF RPC** — `func_0019B590` = `sceSifBindRpc` (matched), `func_0019B0E8`
  get-packet, `func_0019B190` free-packet, `func_0019ACC8` `SifSendCmd`,
  `func_0019B760` `sceSifCallRpc`.  `SifRpcClientData` = `{pkt_addr, rpc_id,
  sema_id, mode, cmd, buff, cbuff, end_function, end_param, server}` with
  `server` at 0x24 — every module in this band tests `cd.server == 0`.
* **EE kernel/thread** — `func_001987A0` CreateSema, `func_001987B0`
  DeleteSema, `func_001987C0` SignalSema, `func_001987D0` iSignalSema,
  `func_001987E0` WaitSema, `func_001987F0` PollSema, `func_001985A0`
  CreateThread, `func_001985C0` StartThread, `func_00198A20` FlushCache,
  `func_001A0828`/`func_001A0870` interrupt disable/enable.

## Suspected translation units

* `0x00190318-0x00191554` — one **async command RPC client** (11 functions, all
  matched).  Shared: `D_002DEBC0` (`SifRpcClientData`, 0x28), `D_002DEC40`
  (0x30 send buffer), `D_002DEC70` (**one 0x450 object**; the split label
  `D_002DEC84` is a disassembler artifact — retail forms one base and reaches
  0x413 by immediate offset), `D_002DEC00` (**one 0x40 object**; `D_002DEC20`
  is likewise an artifact), `D_002DF0C0` (0xC0), `D_002DF180` (0xE81),
  `D_002E0180` (recv), `D_001E4BC0` (pending rpc id), `D_001E4BC4` (sema).
  Every entry point is `PollSema -> check cd.server -> fill D_002DEC40/70 ->
  sceSifCallRpc(mode 1) -> record the rpc number in D_001E4BC0`.
  `func_00190848` is the matching `sync` (near, 3 words).
* `0x0019C778-0x0019EF38` — the **fileio RPC client** (`D_002E2940`, a 0x8E0
  command buffer; `D_002E3580` recv; `D_002E3C00` client; `D_002E3A00[0x20]`
  16-byte fd table; `D_001E5B80` init flag, `D_001E5B88`/`D_001E5B8C` semas,
  `D_001E5B00[0x20]` async-slot table).  13 of them matched.
  Four of the remaining ones (`func_0019CB80`, `func_0019CDB8`, `func_0019D028`,
  `func_0019ED00`, 2,464 B) are blocked by a single word: retail recomputes
  `andi $vX,$s3,0x8000` at both use sites, and every spelling tried lets GCC's
  gcse keep the first result in a callee-saved register.  See
  `near/func_0019CB80.c` — everything else in that file is byte-exact.
* `0x0019F518-0x001A0578` — the **loadfile/fileio bind** unit (`D_002E3CC0`,
  `D_002E3D00`, `D_002E3D80`, `D_002E4080`, `D_002E3E80`, `D_002E40A8`,
  `D_002E40C0`, flags `D_001E5B94`/`D_001E5B98`).  Its retry idiom is a
  `for (i = 0x100000; i != -1; i--)` spin between `sceSifBindRpc` attempts.
* `0x00199508-0x001996B8` + `0x00199B80-0x00199E60` — the **EE console/SIO**
  unit (`D_001E5AA8` register table, `D_002E05C0` sema, `D_002E0B10` state,
  `D_002E0B40` packet, 512-entry circular queue at `+8` of the thread arg).

## Confirmed blockers in this band (do not re-attempt)

* Jump-table switches: `func_0019BFD8` (`jtbl_001EC2F0`).
* EE MMI parallel ops: `func_001922B0`, `func_001926D0`, `func_00192940`,
  `func_00192A54`, `func_00192B90`, `func_001923F4`, `func_00196D24`,
  `func_00196E04`, `func_001927FC`, `func_00192344` (near).
* `sync`: `func_00199420/440/460/480`, `func_00198C30`, `func_00198CC0`.
* `func_0019AF1C` — 4 bytes, bare `jr $ra`.
* Stdarg: `func_0019C778` (see rule 10).
* `func_0019F9E0`, `func_0019FBE8`, `func_0019D2E8` contain a 0x400-byte copy
  guarded by a runtime `((src|dst)&7)` test with an `ldl/ldr` loop on one arm
  and an `ld/sd` loop on the other.  The two loops are reproducible from
  32-byte struct assignments through differently aligned types; `func_0019D2E8`
  is otherwise complete (see `near/`), blocked only on register allocation.
