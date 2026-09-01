# Chulip matching-decomp worker brief

Repo: /home/syf/claude/soc/chulip-decomp  (PS2 `SLUS_207.42`, loaded at 0x00100000)

## Non-negotiable rules
1. **Byte-exact or nothing.** A candidate counts only when `tools/match.py` reports MATCH.
2. **Natural C only.** No inline asm, no `INCLUDE_ASM`/`GLOBAL_ASM`, no `.incbin`, no
   `glabel`/`endlabel`/`.word`, no synthetic `nop` padding tricks. `tools/merge_candidates.py`
   and `tools/batch_verify.py` reject these outright.
3. **Never edit** `config/*.json`, `config/splat.us.yaml`, `README.md`, `docs/*`, or anything
   in `src/`. Integration is serialized by the coordinator. You only write into YOUR lane
   directory and YOUR manifest.
4. **Never run** `tools/merge_candidates.py --write`, `tools/build.py`, `configure.py`,
   or any `git` command that changes state (no commit/push/checkout/stash/reset).
5. Stay strictly inside your assigned address band. Another agent and a separate Codex
   session own the other bands.

## Where things are
- `asm/cod/text.s` (+ other `asm/**/*.s`) — full retail disassembly, `glabel`/`endlabel`
  delimited, with `/* fileoff VRAM rawbytes */` comments.
- `work/claude/asm_index.json` — `{function: [{vram, raw, text}, ...]}` pre-parsed. Use this.
- `config/functions.json` — catalog: name, address, size, handwritten.
- `config/reconstructed.json` — already-done functions (skip these).
- `src/game/*.c` — accepted sources; read them to learn house style.
- `docs/knowledge-book.md` — the curated matching rules. Read section 2-6 before starting.

## Verifying one candidate
```sh
python3 tools/match.py <func> --source <your.c> --profile ee-gcc2.95.3-136-O2-G8
# add --quiet to suppress the word dump; add --object-flag=-Wa,-G4 when needed (see below)
# whole-unit range check:
python3 tools/match.py <func> --source <your.c> --profile ee-gcc2.95.3-136-O2-G8 \
    --range-start 0xAAAAAAAA --range-end 0xBBBBBBBB
```
On mismatch it prints the first differing byte plus expected/actual word dumps. That diff is
your primary feedback signal — read it, do not guess.

Batch re-verify your whole lane:
```sh
python3 tools/batch_verify.py <your-manifest>.jsonl --report <your-report>.json
```
Manifest line format (one JSON object per line):
```json
{"function":"func_00150000","source":"work/lanes/<lane>/func_00150000.c","profiles":["ee-gcc2.95.3-136-O2-G8"]}
```
Optional keys: `"object_flags":["-Wa,-G4"]`, `"range_start"`, `"range_end"`.

## Toolchain model (established, use it)
Primary profile: `ee-gcc2.95.3-136-O2-G8` = SN Systems GNU C 2.95.3-EE build 1.36, `-O2 -G8`,
with its **bundled** historical assembler. Others exist (`ee-gcc2.95.2-273a-*`, `ee-gcc2.96-O2`)
and are useful as negative controls, but 1.36 `-G8` is the working default.

### Global data addressing — the single most important pattern
How a global is spelled in C decides its addressing mode. Read the retail asm and pick:

| retail asm form                          | C declaration                                   |
|------------------------------------------|-------------------------------------------------|
| `lw $v0, %gp_rel(D_x)($gp)`               | `extern int D_x;`  (scalar, size <= 4)          |
| `lui $at,%hi(D_x)` + `sw $r,%lo(D_x)($at)`| 8-byte object + `-Wa,-G4`  (see below)          |
| `lui $vN,%hi(D_x)` + `%lo(D_x)($vN)`      | `extern int D_x[];` (unsized array, "large")    |
| `lui`+`addiu` then offsets off that reg   | `extern T D_x[];`, index it: `D_x[k]`           |

The `$at` form is the *assembler* expanding a compiler-emitted pseudo. GCC emits the pseudo
only when it believes the symbol is small (`size <= 8` under `-G8`); the assembler then makes
it gp-relative only when `size <= its own -G`. So an object of exactly 8 bytes, assembled with
`-Wa,-G4`, yields `lui $at` + `%lo` while 4-byte scalars in the same file stay gp-relative.
Spell it as:
```c
struct S8 { int a; int b; };
extern struct S8 D_001ED42C;
...
D_001ED42C.a = value;
```
and add `"object_flags":["-Wa,-G4"]`. (Discovered and byte-proven on `func_0014FF10`.)


**Addressing (the single most important family of rules)**
- The retail `lui`/`%lo` form for a small-BSS symbol is chosen by the ASSEMBLER, not by
  the declared size. GCC at `-G8` marks an external small when `0 < size <= 8`, emits a
  bare pseudo plus `.extern sym, N`, and leaves expansion to the assembler.
- **Declare the true size and choose the assembler.** The bundled GNU `as` expands
  absolutely iff `N > its -G`, and `-G` is CONTINUOUS: `-Wa,-G3` makes a genuine 4-byte
  object absolute while 2- and 1-byte neighbours stay GP-relative; `-Wa,-G1` does the
  same for a 2-byte object beside a 1-byte one. A symbol the unit *defines* in
  `.sdata`/`.sbss` stays GP-relative at every `-G`, including `-G0`.
- **`Ps2EeAs` ignores `-G` completely.** It expands every small-data pseudo absolutely
  except inside a branch delay slot, where it emits the one-instruction GP-relative
  form. Prefer the `-ps2as` profile whenever one symbol shows both modes and the
  GP-relative sites are exactly the delay slots. It also emits the `mtc1`/`cvt.s.w`
  hazard nops GNU `as` omits, and it pads `.text` to 8 bytes -- so when a function's
  size is not a multiple of 8, extend `--range-end` to the next function.
- An incomplete extern (`extern T X[];`) emits no `.extern` and makes the COMPILER split
  the address, giving `lui $rN` and `%lo($rM)` in DIFFERENT registers. That is never the
  retail `$at` or same-register form.
- **Never declare more bytes than `asm/data/cod` records between a label and the next.**
  Claiming fewer is fine -- the recorded size is label spacing, an upper bound. An
  earlier version of this brief told you to declare a fake 8-byte struct and assemble at
  `-Wa,-G4`; that is RETRACTED. It produced right bytes from a false data model and
  overlapped the neighbouring symbol at 94 of the 97 sites where it was used.
- Object identity test: retail forming ONE base register and reaching several words by
  immediate offset means ONE object, and the split labels are a disassembler artifact.
  A separate `lui %hi` per word means SEPARATE objects needing separate externs.

**Types**
- `long` is 8 bytes; `long long` is 16. A retail `sd`/`ld` field is `long`.
- 64-bit bitwise arithmetic is rejected ("unsupported wide integer operation"). A
  `volatile long long` bitfield is the one way to read a 64-bit flag word: retail
  `dsll N` means bit position `32 - N`, width 32; extract into an `int` temp first.
- A 32-bit AND mask that is a small negative int must be spelled `unsigned` on
  unsigned data, or you get `addiu $r,$zero,-0x81` instead of retail's `lui`+`ori`.

**Source shape**
- `(base + index)->field` and `base[index].field` are NOT interchangeable; only the
  first gives retail's `addiu %lo` / `sll` / `addu` order.
- Independent trailing stores are emitted `first, last, second, third, ...`, with the
  second-to-last in the `jr` delay slot. Reorder the SOURCE, not the struct.
- Statement order is a first-class knob and permutes cheaply -- brute-force it.
- Assigning a mask to a local defeats the single-bit flag optimisation:
  `int f = x & 2; return f == 0;` gives retail `andi`/`sltiu`.
- `(x & (1<<n)) != 0` collapses to `srlv`+`andi` unless the mask is a named local.
- Ternary polarity is inverted; write the condition the positive way round.
- Prototyping a discarded call's result as `int` rather than `void` changes register
  allocation.
- Loop bounds must stay inline; hoisting the load into a local inserts a `daddu`.
- GCC inverts a two-exit `if`: `if (c == 0) { return simple; } return complex;` puts
  *complex* inline and *simple* behind a `beql`.
- Values consumed by a call after another call must be stored *after* the first call,
  or the frame shrinks.
- Branch-likely (`beql`/`bnel`) executes its delay slot ONLY when taken. Ordinary
  conditionals read their compare operands before the delay slot and run it on both
  paths.

**Before recording anything as blocked**
A list of failed source spellings proves nothing about the problem -- only about your
search. Five recorded dead ends fell in one day, including one listed as permanent since
the project's first commits; each fell because the answer lay outside the space being
searched. Before you park something, ask what you have NOT varied: the assembler, the
compiler binary (five SN toolchains sit in `tools/compilers/ps2-bundle/`), the section
placement, or whether the retail source contained a construct you have not considered.
Retest every parked candidate whenever a toolchain fact changes -- one sweep after four
such corrections converted 181 functions, sixty of which needed only to be tried again.

**Structural blockers -- do not attempt**
- Any function spilling `$s0`-`$s7` with `sd` rather than `sq`. That is an unreached
  compiler setting (64-bit register precision) covering essentially everything above
  `0x00185400`, which is also the SDK frontier. Run `python3 tools/regime_scan.py`.
- PS2 kernel syscall stubs; VU0 macro mode (`lqc2`/`vadd`/`qmtc2`); `mult1`; frameless
  tail calls (`j callee`, no prologue); hazard `nop`s after `mtc1`/float literals.
- Jump-table switches: GCC emits its own table into `.rodata`, which the isolated
  linker script cannot place at the retail address.
- Do NOT invent symbol aliases such as `A_001ED88C`. The whole-image link now resolves
  any name ending in an eight-digit address, so an invented symbol will silently pass
  every gate. That makes it worse, not safer: it lets a source model one address twice
  without ever proving the data layout. An address that genuinely shows two addressing
  modes is one object -- model it as a single struct and use the ps2as profile.
- Do NOT declare an object larger than the data section says it is. Several existing
  sources declare an 8-byte struct where `asm/data/cod/sbss.sbss.s` records 4 bytes, and
  88 of them physically overlap the next symbol. Nothing catches this because `.sbss` is
  NOLOAD and no byte reaches the image, so it is on you to check the recorded size before
  reaching for a padding struct.

## Your job
For every function in your band that is NOT in `config/reconstructed.json`:
1. Read its retail asm.
2. Write the smallest readable C that explains **every** instruction.
3. Verify with `tools/match.py`. Iterate on the byte diff.
4. On MATCH, save `work/lanes/<lane>/<func>.c` and append a manifest line.
5. On repeated failure, move on. Record the blocker in your notes; do not burn the budget.

Skip entirely (report them, do not attempt):
- functions whose asm contains `syscall` (PS2 kernel stubs, cannot be natural C)
- `config/functions.json` entries with `"handwritten": true`

Prefer clusters: consecutive addresses that share globals are probably one translation unit.
Note suspected unit boundaries in your report — they are what unlocks *promotion*.

## Record partial progress -- this is required, not optional

A candidate that does not match is not worthless. The distance between it and
retail is the real measure of partial work, and without a durable record the
next lane starts from zero. One survey found 350 candidates parked as prose
notes in `near/` directories and recovered 181 of them; sixty needed nothing
but being tried again.

**Whenever you improve a candidate's word-distance, record it:**

    python3 tools/nearmiss.py <func> --source <your.c> --profile <profile> \
        [--object-flag=-Wa,-G4] [--range-start 0x... --range-end 0x...] \
        --note "what is still wrong, in one line"

It measures the distance itself, appends to `docs/nearmiss.jsonl`, and keeps
only improvements -- a worse result is refused, so you cannot regress the
record. Do this for every candidate you park, and re-record whenever you get
closer, even if you never reach a match. `python3 tools/nearmiss.py --report`
shows the whole backlog ordered by how close it is.

The `--note` matters as much as the number. "one register differs, $v0 where
retail has $v1" tells the next lane which wall it is behind; "does not match"
tells it nothing.

## Report back
- counts attempted / matched
- your manifest path and lane dir
- the suspected translation-unit groupings you found (address ranges + shared globals)
- any new general rule you proved, with the function that proves it
