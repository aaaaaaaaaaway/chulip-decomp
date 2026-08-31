# Contributing to the Chulip decompilation

Thank you for helping. This project values readable reconstruction, exact
evidence, and discoveries that make later work easier.

## Before starting

1. Read `docs/DECOMP_POLICY.md` and `docs/SETUP.md`.
2. Search open issues and pull requests for the address or subsystem.
3. Open or claim a function-matching issue before taking a substantial range.
4. Work on a focused branch such as `match/00101678-camera-vector`.

You may contribute documentation, tooling, names, and architectural research
without possessing the game. Byte matching and the full private build require
your own verified USA disc dump.

## Source workflow

For each reconstructed function:

1. Put readable source under `src/`; do not transcribe instructions or bytes.
2. Run the isolated verifier with every relevant compiler profile.
3. Record exact and rejected profiles. A trivial function that matches every
   compiler does not prove its translation-unit provenance.
4. Add byte-exact candidates to `config/reconstructed.json`.
5. Add a function to `config/matched.json` only after provenance is supported
   by an address-contiguous neighborhood and the full-image build passes.
6. Record durable compiler, ABI, linker, or source-shape findings in
   `docs/matching-knowledge.jsonl`.
7. Regenerate the README progress block.

```sh
python3 tools/match.py func_00101490 --profile ee-gcc2.95.3-136-O2-G8
.venv/bin/python configure.py --split
python3 tools/build.py
python3 tools/progress.py --write-readme
python3 tools/repo_audit.py
```

The final build output must say `FULL IMAGE MATCH`; a successful compile,
similar disassembly, or working gameplay is not a byte match.

## Pull requests

Keep pull requests small enough to review. Include:

- function names, addresses, and byte totals;
- compiler profile and exact verifier result;
- why the profile is credible for the surrounding translation unit;
- full-image result, or a clear request for a maintainer to run the private
  gate when you cannot;
- any names, types, or architecture knowledge learned while matching.

Do not mix broad formatting or symbol renames into a matching PR. Maintainers
may leave an isolated exact candidate unpromoted until neighboring evidence is
available; that is useful progress, not a rejection.

## Prohibited content

Never commit or attach:

- ROM/disc archives, BIN/CUE/ISO images, or extracted executables;
- ripped models, textures, audio, movies, or other game assets;
- generated retail assembly or raw target-byte excerpts;
- PlayStation SDK files or historical compiler binaries;
- Ghidra projects, proprietary database files, or credentials.

The repository audit rejects common forbidden paths and binary formats. If a
review needs target bytes, describe the address range and hashes rather than
uploading the data.

## Commit style

Use imperative, scoped subjects, for example:

```text
Match camera vector accessors at 0x001018C8
Document EE small-data compiler behavior
Harden disc extraction bounds checks
```

Every commit should leave the public audit green. Source promotions must also
leave the private complete-image gate green.
