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

`tools/scope_scan.py` classifies all 2,189 catalog functions from the zero-C
baseline disassembly. The figures below are a snapshot; the tools are the
source of truth and will disagree with this page as work lands.

| Class | Functions | Bytes | Share |
| --- | ---: | ---: | ---: |
| Matched | 714 | 36,344 | 5.48% |
| Reachable, not yet written | 1,141 | 464,808 | 70.03% |
| Jump-table switch | 85 | 146,188 | 22.03% |
| VU0 macro mode | 41 | 4,976 | 0.75% |
| Hand-written assembly | 188 | 7,052 | 1.06% |
| Second multiply pipe | 20 | 4,336 | 0.65% |

Only **16,364 bytes, 2.47% of the image, cannot be expressed in C at all**:
kernel syscall stubs, VU0 macro-mode vector code, the second EE multiply pipe,
and the hand-written entry code. Those are the only bytes a complete
decompilation may legitimately leave as assembly.

That gives a reachable denominator of **647,340 bytes**, against which the
project has matched **5.61%**.

## The largest single gap is ours, not the game's

Jump-table switches are 85 functions and 146,188 bytes — 22% of the whole
executable, and by far the biggest block of unmatched code. They are ordinary C.
A `switch` compiles to a jump table in `.rodata`, and the reconstruction does
not yet place that table at its retail address, so the `%hi`/`%lo` immediates
can never match. **This is a build limitation, not a limit of the language**,
and closing it is worth more than any other single piece of work available.

## Two compilers, one executable

`tools/regime_scan.py` shows a sharp boundary. Below roughly `0x00185400`,
functions spill `$s0`-`$s7` with `sq` at 128-bit register precision; above it
they use `sd` at the same sixteen-byte slot stride. Of 705 `sq` functions all
but two are below the line, and all 255 `sd` functions are above it.

- Below: game code, SN Systems GNU C (`ee-gcc2.95.3-136-O2-G8`).
- Above: the C runtime and libraries, Sony EE GNU C (`ee-gcc2.9-991111-01-O2`).

The upper region holds libm kernels, IEEE float and double pack/unpack, a VU0
vector library, stdio with a `FILE`-like structure and a read/write/seek/close
vtable, the string and memory routines, a linear-congruential `rand`, an errno
layer, SIF and DMA transfer code, and the kernel syscall stubs. Whether SDK code
should count toward "decompiling Chulip" is a scope decision; it is recorded
separately so the question stays answerable.

## Where the numbers currently overstate the work

Two caveats, both visible in `tools/progress.py`:

**The function count runs ahead of the byte count.** Small functions are matched
first, so 32% of functions is 5.5% of bytes. Text bytes is the honest measure.

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
in proven units:   159 / 714 (22.3%); 555 compiled alone
build configurations in use: 10
```

Consolidating adjacent functions into single source units, compiled once with
one configuration, is what converts a byte match into a reconstruction. Until
that ratio rises, treat the matched count as bytes proven rather than
translation units understood.
