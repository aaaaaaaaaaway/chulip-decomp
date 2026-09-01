# Contributor setup

## Supported host

The verified development host is Linux x86-64. The bootstrap also knows the
pinned macOS Wibo asset, but the complete macOS build lane has not yet been
accepted. Windows contributors can work through WSL2.

Required host packages on Debian or Ubuntu:

```sh
sudo apt install python3 python3-venv binutils-mipsel-linux-gnu dpkg
```

Then run `python3 tools/bootstrap.py`. It creates the ignored `.venv`, installs
the Python versions from `requirements.txt`, and installs every compiler and
assembler referenced by `config/toolchains.json`. This includes the two SN
Systems releases, Sony EE GNU C 2.9, GNU C 2.96, Wibo 1.2.0, and the pinned
32-bit glibc runtime needed by the native Linux compilers. Historical
assemblers bundled with the compiler archives are used where they are known to
work. Every archive has a URL and SHA-256 in the toolchain configuration, and
the check compares installed compiler artifacts back to those pinned archives.
The 32-bit loader and libc have artifact hashes as well. None is committed to
Git.

The cross-binutils suite remains a checked host dependency. Distribution
packages are dynamically linked to other host libraries, so pinning only the
cross-binutils package would not create a hermetic toolchain. The bootstrap
therefore checks every required command and leaves the exact load-image gate as
the authority instead of claiming a false binutils pin.

To audit an existing installation without downloading or modifying it:

```sh
python3 tools/bootstrap.py --check --skip-python
```

## Supplying the target

Obtain your own USA disc dump. The project expects a raw Mode2/2352 BIN named
`disc/Chulip (USA).bin`; its SHA-256 must be
`f1efe2cc0aedb685e1a244bd07b16c402e2bb3319aadaf1381267a0c4a654c06`.

```sh
python3 tools/mode2_to_iso.py 'disc/Chulip (USA).bin' disc/chulip.iso
python3 tools/iso9660_extract.py disc/chulip.iso --extract original --json
.venv/bin/python configure.py --split
python3 tools/build.py
```

The build must report the exact 970,772-byte load-image match. `disc/`,
`original/`, generated assembly, compiler binaries, and build output are all
ignored and must remain untracked.

The standard split emits temporary retail matchings used to place compiler
generated jump tables. A separate baseline split is useful for comparisons but
is not a hidden prerequisite for `tools/build.py`. Compiled jump-table sections
are non-loadable proof sections: the loadable image keeps the already verified
retail bytes at those addresses, so proof data cannot create an overlapping
segment that changes runtime memory. The linker also extends the final
zero-filled BSS tail to the executable's declared PT_LOAD memory boundary.

## ELF completeness

An exact load image is not the same claim as an identical ELF file. The normal
build proves the bytes loaded by the game, while modern linking can still
produce different ELF offsets, section tables, or BSS metadata.

After a build, inspect both levels explicitly:

```sh
make elf-report
make elf-report CANDIDATE_ELF=build/baseline/chulip.us.elf
```

`tools/elf_completeness.py` is read-only. It hashes target and candidate bytes
in memory and reports full-container identity, PT_LOAD bytes mapped by virtual
address, ELF and program headers, allocated sections, and NOBITS/BSS layout as
separate results. It never writes or embeds bytes from the target executable.
Use `--json` for machine-readable output. Optional gates are
`--require-load-image`, `--require-layout`, and `--require-container`.

## Working without a disc

The public repository still supports documentation, catalog, ledger, and tool
changes without copyrighted inputs:

```sh
python3 tools/repo_audit.py
python3 tools/progress.py --check-readme
python3 -m compileall -q configure.py tools
```

GitHub Actions runs exactly this public-data lane. A maintainer with a verified
disc performs the private full-image gate before counting source matches.
