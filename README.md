# Chulip (USA) matching decompilation

An in-progress, byte-matching decompilation of the USA PlayStation 2 release
of *Chulip* (`SLUS_207.42`). The goal is a complete, readable source
reconstruction of the game executable—not a port, recompilation shortcut, or
assembly transcription.

The current source-plus-assembly build reproduces the complete 970,772-byte
loaded image with SHA-256
`77768f0c5d84a92a6d185499b8bb4bb2205779a81fbdb859b15cc1d9ce28f876`.
Assembly generated from the retail executable is temporary scaffolding and is
never counted as decompilation progress.

<!-- decomp-progress-start -->
## Decompilation progress

![Matched functions](https://img.shields.io/badge/functions-3%20%2F%202189-2f81f7) ![Matched text bytes](https://img.shields.io/badge/text%20bytes-76%20%2F%20663704-2f81f7)

`▏░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░` **0.0115%** of provisional text bytes promoted

| Metric | Matched | Total | Progress |
| --- | ---: | ---: | ---: |
| Functions | 3 | 2,189 | 0.1370% |
| Text bytes | 76 | 663,704 | 0.0115% |

Only readable source that passes isolated byte comparison, compiler-provenance review, and the complete-image rebuild is counted. Generated retail assembly contributes zero progress.
<!-- decomp-progress-end -->

## Project state

- The USA disc revision, main executable, `PT_LOAD`, and ELF sections are
  fingerprinted in `config/`.
- A zero-C baseline and the current source-plus-assembly project both reproduce
  the complete loaded image exactly.
- SN Systems GNU C 2.95.3-EE build 1.36 at `-O2` is proven for the first
  promoted address-contiguous neighborhood. Toolchain claims elsewhere remain
  local until surrounding functions support them.
- `DAT/SYSTEM.BIN`, `DAT/SYSTEX.BIN`, SDK code, data, and linker layout remain
  part of the completion scope.

See [project status](docs/STATUS.md), [architecture notes](docs/architecture.md),
and the append-only [matching knowledge ledger](docs/matching-knowledge.jsonl).

## Quick start

You must supply your own verified disc dump. The expected raw BIN hash and
track layout are recorded in `config/disc.json`; no game data is distributed
by this repository.

```sh
python3 tools/bootstrap.py

# Put "Chulip (USA).bin" and its CUE in disc/ first.
python3 tools/mode2_to_iso.py 'disc/Chulip (USA).bin' disc/chulip.iso
python3 tools/iso9660_extract.py disc/chulip.iso --extract original --json

.venv/bin/python configure.py --split
python3 tools/build.py
python3 tools/progress.py
```

Expected successful build output includes `FULL IMAGE MATCH: 970772 bytes`.
The independent zero-C coverage check is:

```sh
.venv/bin/python configure.py --baseline-split
python3 tools/build_baseline.py
```

## Contributing

Issues and pull requests are open. See [CONTRIBUTING.md](CONTRIBUTING.md) for
the matching checks and the list of content that must stay out of Git.

## Repository layout

| Path | Purpose |
| --- | --- |
| `src/` | Readable reconstructed source |
| `include/` | Shared types, macros, and declarations |
| `config/` | Disc/ELF fingerprints, function catalog, toolchains, and match ledgers |
| `docs/` | Architecture, status, policy, campaign log, and durable findings |
| `tools/` | Extraction, splitting, compilation, matching, build, and audit tools |
| `.github/` | Collaboration templates and public-data CI checks |

Generated assembly, extracted files, historical compiler binaries, and build
products are deliberately excluded from Git.

## Matching standard

A function counts only when readable source:

1. reproduces every byte of the isolated retail function;
2. uses a compiler/flag profile supported by its translation-unit neighborhood;
3. survives a clean, complete-image byte-identical rebuild; and
4. is recorded in the match ledger with its evidence.

Full-function assembly, `.word` transcription, embedded target bytes, stubs,
and semantic-only rewrites do not count. The complete policy is in
[docs/DECOMP_POLICY.md](docs/DECOMP_POLICY.md).

## Legal

This project is not affiliated with Punchline, Victor Interactive Software,
Natsume, or Sony. Do not commit or distribute disc images, archives, extracted
executables, game assets, generated retail disassembly, or proprietary SDK
material. Historical toolchains are downloaded locally from their respective
third-party archives and are not redistributed here.
