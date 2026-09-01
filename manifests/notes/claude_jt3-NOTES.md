# Lane claude_jt3 — remaining jump-table `switch` functions

Worklist: `work/claude/jt3.txt` (regenerated; 71 rows, of which 20 were already
claimed by earlier lanes -> 51 genuinely open, 135,652 bytes).
Manifest: `work/claude/jt3.jsonl` (copy of `work/lanes/claude_jt3/manifest.jsonl`).
Profile used for every match: `ee-gcc2.95.3-136-O2-G8-ps2as`, no object flags.

## Matched (5 functions, 4,812 bytes)

| function | bytes | notes |
|---|---|---|
| func_00144FD8 | 1116 | menu state machine, 53-case table |
| func_0013A120 | 1404 | session state machine, 104-case table (first try) |
| func_001513E0 | 1072 | resource-cache dispatcher, 8 parallel arrays |
| func_00148CE0 | 676  | session state machine, 33-case table |
| func_0011AE00 | 544  | GIF-packet builder, 6-case table |

## NEW RULE (the big one): a global pointer that retail RELOADS after every
## store through it is a union member.

Retail repeatedly emits, for one statement per line:

```
lui v1,%hi(D_001ED3C8); lw v1,%lo(D_001ED3C8)(v1); sh $zero,0x16(v1)
lui v0,%hi(D_001ED3C8); lw v0,%lo(D_001ED3C8)(v0); sh $zero,0x18(v0)
...
```

i.e. the pointer load is *not* CSE'd across a store through it. Declaring
`extern struct Ctx *D_001ED3C8;` and writing `D_001ED3C8->f = ...` gives ONE
load for the whole block — GCC's strict-aliasing says a `short` store cannot
alias a pointer object. Consecutive *loads* still share a base in retail, so
`volatile` is wrong (it reloads for loads too, and reorders nothing).

The construct that reproduces retail exactly is a one-member union:

```c
union CtxRef_001ED3C8 { struct Ctx_001ED3C8 *ctx; };
extern union CtxRef_001ED3C8 D_001ED3C8;
...  D_001ED3C8.ctx->field_0x16 = 0;
```

`c_get_alias_set` returns **0** for any access reached through a union member,
so every store invalidates the cached load — and, as a bonus, other memory
operations can no longer be hoisted across it, which fixes a whole class of
"my schedule swapped two independent memory ops" mismatches.

Verified negative controls (none of these reload; only the union does):
plain `extern struct S *P`, file-scope `struct S *P`, `extern char *P` + cast,
`extern int P` + cast to `struct S *`, self-referential struct, typedef'd
struct, `volatile short` fields, 16-bit bitfields, inner-union field.
Shapes that DO reload but are unusable here: `extern struct S *P[1]` (kills the
gp-relative form, symbol is no longer "small"), `*(short*)(P+off)` with
`extern int P`, and `unsigned char` fields (char is alias set 0 anyway).

The same trick applies to plain scalars: `func_0011AE00` only matched once
`D_001ED204` (the switch selector) was wrapped in
`union Sel_001ED204 { int value; }` — otherwise GCC hoisted its load above the
four `sd` stores that precede it.

Symbols proven to need it so far: `D_001ED3C8`, `D_001ED204`. The gap scan
below lists ~20 more open functions with the same reload signature.

## OTHER RULES PROVEN IN THIS LANE

1. **`-G` is irrelevant for `extern` small symbols under `Ps2EeAs`.** Tested
   `-G0/-G4/-G8/-G16/-G64` on the same `.s`: identical bytes every time. The
   expansion is decided purely by position — inside a `.set nomacro` block
   (i.e. a filled delay slot) it is the one-instruction `%gp_rel` form, outside
   it is the two-instruction absolute macro (`lui $at` + `%lo($at)` for a
   store, `lui rD` + `%lo(rD)` for a load). So `object_flags` are noise on this
   profile; do not add them.
2. **A non-delay-slot `%gp_rel` reference is a translation-unit boundary
   marker.** It cannot be produced from an `extern`; the compiler only writes
   `%gp_rel` explicitly for a symbol the unit itself defines. Screen for it
   with `work/lanes/claude_jt3/gpscan.py` before spending time on a function.
   `func_00146940` is blocked exactly this way (`D_001ED3B8`, in `.sbss` at
   0x001ED3B8, so it cannot be placed by the isolated linker script either).
3. **The switch range is set by the *lowest* source case too.** `func_00146940`
   emitted `addiu -0xA` + `sltiu 0x5B` until an explicit `case 0: break;` was
   added; retail's `lh` + `sltiu 0x65` needs the source to span 0..100. Adding
   an empty low case is free (it shares the default label) and is the cheapest
   fix when the retail `sltiu` bound does not equal `maxcase+1`.
4. **`(x >> n) & 1` must go through a named `int` local to get retail's
   `beq $v0,$a0` form.** Written inline, GCC folds `== 1` into `!= 0` and emits
   `bnez` with no constant. With `bit = (int)(flags >> 2) & 1; if (bit == 1)`
   it materialises `addiu a0,zero,1` once per block and compares against it —
   this is what retail does wherever three flag bits are tested in a row.
   Where retail really does use `bnez`, write the expression inline instead.
5. **`return -1` vs `return 0xFFFFFFFF`.** Retail's `lui 0xFFFF`+`ori 0xFFFF`
   only comes out of an *unsigned* function returning the unsigned constant;
   `int` + `-1` folds to a one-instruction `addiu`. Proven on `func_001513E0`.
6. **Prototype a discarded call result as `int`, not `void`,** when the next
   temp must avoid `$v0`. `func_00144FD8` was one register off (`v0` vs `v1`
   on the final pointer reload) until `func_0017C830` was declared to return
   `int`.
7. **`written = 0;` before vs after a call decides whether it gets a
   callee-saved register.** In `func_00119BB8` moving the initialiser above the
   `func_00113228` call is what forced `s1` and the 0x80 frame.
8. **Store a computed result into a temp, then store the temp once**, when
   retail keeps the value in an `s` register and does a single `sw` at a merged
   tail (`func_001513E0`: `handle = f(); arr[id] = handle;` not
   `arr[id] = f();` in both branches).
9. **Fall-through between cases is real source, not cross-jumping.** In
   `func_00148CE0` case 21 physically falls into case 13's body; writing it as
   a duplicated body cost 4 instructions.
10. **Four independent trailing `sd` stores come out `1st, 2nd, 4th, 3rd`** in
    the GIF-tag builders (`func_00119BB8`, `func_0011AE00`): source order
    `lo, hi, hi2, lo2` produces retail's `0x0, 0x8, 0x18, 0x10`.

## Near misses (documented, not in the manifest)

* `func_00146940` (1116 B) — 1 instruction. Blocked by rule 2: `D_001ED3B8`
  must be defined by the same translation unit (non-delay-slot `%gp_rel` store
  at 0x00146988). Everything else matches; source kept out of the manifest.
* `func_00119BB8` (476 B) — 2 instructions. Retail copies the `buf` parameter
  twice (`s0 = a0` at entry, `s5 = s0` after the first call) and pads one
  `nop`; every variant tried (extra local, `void *` param, passing `buf` to the
  callee, initialising `out` from `buf` before the checks) coalesces the copy.
* `func_0017D830` (168 B) — 1 register. Retail needs 8 live registers
  (`h` and `w` as fresh pseudos while both parameters stay live); every source
  shape that creates those pseudos also makes GCC copy *both* parameters at
  entry instead of just `$a0`. 24 generated permutations tested.
* `func_00138F88` (544 B) — inherited from lane claude_jt2, still off in the
  middle of the loop body.

## Translation-unit groupings observed

* `0x00119BB8 / 0x0011AE00` — one unit: same header layout (`buf->field_0x3 =
  0x10`, `func_00113228(out, 9)`, giftag `0x1000000000008001`, `return
  total + 1`), same `D_001ED1F8/1FC/200/204/20C` small-data cluster.
* `0x0013A120 / 0x0013D318 / 0x0013E4C8 / 0x0013FBF0 / 0x00140228 / 0x00140708
  / 0x001429A8 / 0x001442C0 / 0x00144FD8 / 0x00145938 / 0x00146940 / 0x00148CE0
  / 0x00149C88` — the `D_001ED3C8` menu/session state machines. They share the
  `Ctx` layout (0x8 short, 0xC short, 0xE short, 0x14 state, 0x16, 0x18, 0x1A)
  and the `func_00136AE8()` session pointer whose 64-bit flag word lives at
  offset 0. `D_001ED3B0/3B8` belong to that unit (see rule 2), so the unit
  boundary is somewhere around 0x00145938-0x00146940.
* `0x001513E0 / 0x001505C0 / 0x00151810…` — resource-cache unit owning the
  eight `D_002A….` handle arrays and `D_001ECB70…` small data.

## Helper scripts (this dir)

* `jt.py FUNC` — disassembly plus the decoded jump table grouped by target.
* `wd.py FUNC SRC [PROFILE]` — word-level diff of expected vs actual with
  addresses; the fastest way to see *which* instruction moved.
* `gpscan.py` — lists open functions containing a non-delay-slot `%gp_rel`
  reference (rule 2 screen).
* `v.sh FUNC [PROFILE]`, `t.sh FUNC SRCPATH [PROFILE]` — verify with
  `--range-end` set to the next function automatically.
