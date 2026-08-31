# Contributor setup

## Supported host

The verified development host is Linux x86-64. The bootstrap also knows the
pinned macOS Wibo asset, but the complete macOS build lane has not yet been
accepted. Windows contributors can work through WSL2.

Required host packages on Debian or Ubuntu:

```sh
sudo apt install python3 python3-venv binutils-mipsel-linux-gnu
```

Then run `python3 tools/bootstrap.py`. It creates the ignored `.venv`, installs
the Python versions from `requirements.txt`, downloads Wibo 1.2.0, and
downloads SN Systems GNU C 2.95.3-EE build 1.36 with its bundled assembler.
Every download is checked against `config/toolchains.json`; none is committed
to Git.

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
