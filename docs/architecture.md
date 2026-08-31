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
addresses. Exact game-versus-SDK boundaries and subsystem names are not yet
proven and are therefore not assigned in the function catalog.

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
