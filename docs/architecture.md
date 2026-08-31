# Architecture

## Executable container

The USA disc boots `SLUS_207.42`. Its single EE `PT_LOAD` begins at virtual
address `0x00100000`, has `0xED014` file bytes and `0x1E53AC` memory bytes, and
enters at `0x00100008` with GP `0x001F4870`. `config/elf.json` is authoritative
for the mapped text, VU text, data, rodata, small-data, and BSS ranges.

The `.text` range is `0x00100000-0x001A3000`. Automated discovery currently
finds 2,189 provisional functions; 188 carry instruction-pattern evidence of
handwritten code. These are discovery labels, not yet ownership or source-file
boundaries.

## Disc-resident containers

`DAT/SYSTEM.BIN` and `DAT/SYSTEX.BIN` have custom `BIN` headers and no embedded
ELF signature. They remain in scope as unmapped runtime containers; they are
not silently excluded from the completion target.

## Ownership frontier

Late-text diagnostic strings reference Sony EE libraries such as GS and pad
code, providing an initial SDK-identification frontier around the high text
addresses.

A second, sharper signal now supports the same boundary. The executable was not
produced by one compiler configuration: functions below a single address spill
`$s0`-`$s7` with `sq`, at 128-bit register precision, while functions above it
use `sd` at the same sixteen-byte slot stride. `tools/regime_scan.py` derives
this from the zero-C baseline disassembly rather than asserting it:

```
functions spilling callee-saved registers: 972
  128-bit sq regime: 705
  64-bit  sd regime: 255
  mixed within one function: 12
first sd-regime function: 0x001855F0
last sq-regime function below it: 0x00185218
sq-regime functions above the boundary: 2 (0x001926D0, 0x001A1340)
```

The cut is clean: every one of the 705 `sq` functions except two lies below
`0x001855F0`, and every one of the 255 `sd` functions lies above it. The twelve
mixed functions spill both widths within one body, which is ordinary inside a
single object and does not weaken the split.

Reading of the upper region agrees with that boundary. It contains an IEEE
float and double classify/pack/unpack library, `libm` sine, cosine and arctangent
kernels with their `fabs`/`isnan`/`copysign` helpers, a VU0 macro-mode vector
library, a C runtime with a `FILE`-like structure and a four-entry
read/write/seek/close vtable, `strstr`, `memcpy`, `memset` and `memcmp`, a
linear-congruential `rand`, an errno layer, SIF and DMA transfer code, and a
contiguous block of PS2 kernel syscall stubs. The `libgcc` 64-by-64 multiply
helper appears at `0x00187180`.

So the frontier is provisionally `0x00185400`, in the gap between the last
`sq` function and the first `sd` function: game code below, SDK and runtime
above. This remains provisional because the compiler setting that selects
64-bit register precision has not been recovered, so no upper-region function
has yet been matched byte-for-byte through its own regime. Subsystem names are
still not assigned in the function catalog.

## View/camera state frontier

The address-contiguous module beginning near `0x00101490` maintains a large
state object at `0x001EDE00`. Its first twelve bytes are a three-float vector;
offset `0x30` begins a 16-byte vector copied as one EE quadword, and its first
two floats have widely used accessors. `CameraState`
is the current evidence-based working name because the callers repeatedly feed
view-related state, but field semantics beyond the proven layout remain
provisional.

An aligned source-owned small-data block begins at `0x001EC880`. Its first
four words are a `-999.0f` radius sentinel, two zero position offsets, and a
zero state word. The floats are emitted through GP-relative addressing. Exact
setters at `0x00101CA8` and `0x00101CB8` prove the module's `-G8` compiler
setting: the same source under `-G0` expands into absolute `lui`-based accesses
and does not match.

The seventeen contiguous motion routines at `0x001017F0-0x00101CC3` are a
proven shared source unit rather than isolated artificial objects. Their camera
position updates, angle accumulation, vector copies, state accessors, and view
notifications reproduce all 1,236 object-text bytes only when the historical
assembler constructs half-pi literals inline. The following four bytes are
linker input alignment, not part of the source object's text section.

Four later source islands extend the same subsystem evidence:

- `func_00102440` updates the camera position and small-data radius, and
  independently rejects both compiler `-G0` and SN build 2.73a.
- The snapshot pair at `0x00103AD0-0x00103C0F` copies a 16-byte-aligned
  `CameraState` into and out of the object at `0x001EDE40`. Its complete
  320-byte source unit rejects the older compiler's aggregate-copy schedule.
- Four object helpers at `0x00103CF8-0x00103DCF` form an exact 216-byte unit
  that copies camera state and updates transform buffers.
- The resource pair at `0x00104178-0x001041D7` is an exact 96-byte unit. It
  requires compiler `-G8` with historical assembler `-G0` and addresses two
  fields inside the raw small-BSS allocation at `0x001ED080`.

These islands support a local camera-area compiler model; they do not prove
that the entire executable used one compiler profile or source layout.

## Resource-record frontier

Ten contiguous functions at `0x00137EA0-0x00137FCB` manage three indexed
record families and an adjacent 16-byte object. Expressed as one natural C
unit, they reproduce the full 300-byte emitted range, including four internal
alignment words. This range uniquely selects SN GCC 2.95.3 build 1.36 with
`-O2 -G8`: GCC 2.96, both configured `-G0` profiles, and SN GCC 2.95.2 with
`-G8` all reject. The unit is therefore matched; its outer historical source
file edges may still expand as adjacent functions are recovered.
