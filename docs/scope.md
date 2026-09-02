# Scope and denominator

A completion percentage means nothing without an honest denominator. This page
records what "complete" can mean for this executable, which parts of it no C
compiler can produce, and where the current numbers overstate the work.

Every figure here is derived, not asserted. Regenerate them with:

```sh
python3 tools/scope_scan.py     # what is expressible, and what is not
python3 tools/regime_scan.py    # where the compiler changes
python3 tools/progress.py       # what is matched, and how well it is proven
```

## What the executable is made of

`tools/scope_scan.py` classifies all catalog functions from the zero-C
baseline disassembly. The table below is generated; run
`python3 tools/scope_scan.py --write-scope` after work lands.

<!-- decomp-scope-start -->

| Class | Functions | Bytes | Share of text |
| --- | ---: | ---: | ---: |
| matched | 1,227 | 159,436 | 24.02% |
| reachable, not yet written | 666 | 364,048 | 54.85% |
| jump-table switch | 48 | 124,412 | 18.75% |
| kernel syscall stub | 0 | 0 | 0.00% |
| VU0 macro mode | 41 | 4,976 | 0.75% |
| hand-written assembly | 188 | 7,052 | 1.06% |
| second multiply pipe | 19 | 3,780 | 0.57% |

Not expressible in C at all: **12,028 bytes (1.81%)** -- kernel syscall stubs, VU0 macro mode, and hand-written assembly.

Switch functions whose tables are pinned but whose bodies are unwritten: **124,412 bytes (18.75%)**. These are reachable work and stay in the denominator.

Reachable denominator: **651,676 bytes**, against which **159,436 (24.4655%)** is matched.

<!-- decomp-scope-end -->

Those inexpressible bytes are the only ones a complete decompilation may
legitimately leave as assembly.

## The largest single block of unmatched code

Switch functions are by far the biggest block of unmatched bytes, and they are
ordinary C. A `switch` compiles to a jump table in `.rodata`, and placing that
table at its retail address was once a build limitation; `tools/build.py` now
pins compiled tables there, and switch functions have been matched under that
mechanism. What remains is the size of the bodies rather than any gap in the
reconstruction, which is why the class stays inside the reachable denominator.

## Two compilers, one executable

`tools/regime_scan.py` shows a sharp boundary. Below roughly `0x00185400`,
functions spill `$s0`-`$s7` with `sq` at 128-bit register precision; above it
they use `sd` at the same sixteen-byte slot stride. Of 705 `sq` functions all
but two are below the line, and all 255 `sd` functions are above it.

- Below: game code, SN Systems GNU C (`ee-gcc2.95.3-136-O2-G8`).
- Above: the C runtime and libraries, Sony EE GNU C (`ee-gcc2.9-991111-01-O2`).

The full profile grid supports this and quantifies it: 271 functions below the
line discriminate SN with no counter-examples, and 78 above it are Sony-only,
including several 200-300 byte bodies. Ninety-three functions above the line
are ledgered with the SN profile, but none of them discriminates it and 73 also
match Sony outright, so their label is arbitrary rather than evidence of the
regimes interleaving.

The upper region holds libm kernels, IEEE float and double pack/unpack, a VU0
vector library, stdio with a `FILE`-like structure and a read/write/seek/close
vtable, the string and memory routines, a linear-congruential `rand`, an errno
layer, SIF and DMA transfer code, and the kernel syscall stubs. Whether SDK code
should count toward "decompiling Chulip" is a scope decision; it is recorded
separately so the question stays answerable.

## Where the numbers currently overstate the work

Two caveats, both visible in `tools/progress.py`:

**The function count runs ahead of the byte count.** Small functions are matched
first, so the matched share of functions is more than twice the matched share of
bytes; compare the two rows `tools/progress.py` prints. Text bytes is the honest
measure.

**Compiler attribution is now mostly discriminated, but that is not provenance.**
This page previously recorded the opposite, from a time when 178 of 820 entries
matched exactly one profile. Measured against the ledger today, 1,134 of 1,213
entries reproduce under exactly one profile, 79 remain ambiguous, and none
reproduce under all nine. `tools/reverify_ledger.py` replays every one of those
claims. What a single verified profile does not establish is that the function
was compiled in the object the ledger implies, which is the next caveat.

**Most matched functions are not yet in proven translation units.** A retail
translation unit was compiled once, with one set of flags. Today most matched
functions sit alone in their own object, each free to choose its own compiler
and assembler flags. Those functions have the right bytes, confirmed by the
whole-image rebuild, but not yet a proven reason for them: neighbouring
functions sometimes require flag combinations that could not all have been true
of one real object.

`tools/progress.py` reports the ratio on every run, so it cannot drift
unnoticed:

```
co-compiled:       258 / 1213 (21.3%); 955 compiled alone
  (sharing a source file, NOT a proven object boundary)
build configurations in use: 22
```

The parenthetical is the point. Co-compilation counts functions that share a
source file, which is weaker than a proven object boundary, and the
configuration count is a description of the ledger rather than of the evidence.

Consolidating adjacent functions into single source units, compiled once with
one configuration, is what converts a byte match into a reconstruction. Until
that ratio rises, treat the matched count as bytes proven rather than
translation units understood.
