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
