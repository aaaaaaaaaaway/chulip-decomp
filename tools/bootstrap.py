#!/usr/bin/env python3
"""Install the public Python and historical-toolchain prerequisites locally."""

from __future__ import annotations

import argparse
import hashlib
import os
import platform
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
COMPILERS = ROOT / "tools/compilers"
COMPILER_URL = (
    "https://github.com/decompme/compilers/releases/download/compilers/"
    "ee-gcc2.95.3-136.tar.gz"
)
COMPILER_SHA256 = "3b6ae6897229ad005aaf1b0afaa1f3cb46e74b4c21a42e01130c07c0c598067f"
WIBO_ASSETS = {
    ("Linux", "x86_64"): (
        "https://github.com/decompals/wibo/releases/download/1.2.0/wibo-x86_64",
        "13f86a2d618f0dbe67179d349625345eabf9b46450295cb4c904e49f6aff85af",
    ),
    ("Darwin", "arm64"): (
        "https://github.com/decompals/wibo/releases/download/1.2.0/wibo-macos",
        "2b3000ef6a7a490c24ccd71967735ae0005e218922e51806cca1b8d77fd3cf7c",
    ),
    ("Darwin", "x86_64"): (
        "https://github.com/decompals/wibo/releases/download/1.2.0/wibo-macos",
        "2b3000ef6a7a490c24ccd71967735ae0005e218922e51806cca1b8d77fd3cf7c",
    ),
}


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def download(url: str, destination: Path, expected: str) -> None:
    if destination.is_file() and sha256(destination) == expected:
        print(f"verified cached {destination.relative_to(ROOT)}")
        return
    destination.parent.mkdir(parents=True, exist_ok=True)
    partial = destination.with_suffix(destination.suffix + ".partial")
    print(f"downloading {url}")
    with urllib.request.urlopen(url) as response, partial.open("wb") as output:
        shutil.copyfileobj(response, output)
    actual = sha256(partial)
    if actual != expected:
        partial.unlink(missing_ok=True)
        raise SystemExit(f"download hash mismatch for {url}: {actual}")
    partial.replace(destination)


def setup_python() -> None:
    python = ROOT / ".venv/bin/python"
    uv = shutil.which("uv")
    if not python.is_file():
        if uv:
            subprocess.run([uv, "venv", str(ROOT / ".venv"), "--python", sys.executable], check=True)
        else:
            subprocess.run([sys.executable, "-m", "venv", str(ROOT / ".venv")], check=True)
    if uv:
        subprocess.run(
            [uv, "pip", "install", "--python", str(python), "-r", str(ROOT / "requirements.txt")],
            check=True,
        )
    else:
        subprocess.run([str(python), "-m", "pip", "install", "-r", str(ROOT / "requirements.txt")], check=True)


def setup_toolchain() -> None:
    system = (platform.system(), platform.machine())
    if system not in WIBO_ASSETS:
        raise SystemExit(f"no pinned Wibo bootstrap asset for {system[0]} {system[1]}")
    wibo_url, wibo_hash = WIBO_ASSETS[system]
    wibo = COMPILERS / "wibo"
    download(wibo_url, wibo, wibo_hash)
    wibo.chmod(wibo.stat().st_mode | 0o111)

    target = COMPILERS / "ee-gcc2.95.3-136"
    compiler = target / "bin/ee-gcc.exe"
    assembler = target / "lib/gcc-lib/ee/2.95.3/as.exe"
    if not compiler.is_file() or not assembler.is_file():
        if target.exists():
            raise SystemExit(f"incomplete toolchain directory exists: {target}")
        archive = COMPILERS / "downloads/ee-gcc2.95.3-136.tar.gz"
        download(COMPILER_URL, archive, COMPILER_SHA256)
        COMPILERS.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix="ee-gcc2.95.3-136-", dir=COMPILERS) as temp:
            temp_path = Path(temp)
            with tarfile.open(archive, "r:gz") as bundle:
                bundle.extractall(temp_path, filter="data")
            temp_path.rename(target)
    print("verified required compiler and assembler: ee-gcc2.95.3-136")


def check_host_tools() -> None:
    required = [
        "mipsel-linux-gnu-as",
        "mipsel-linux-gnu-ld",
        "mipsel-linux-gnu-nm",
        "mipsel-linux-gnu-objcopy",
    ]
    missing = [command for command in required if not shutil.which(command)]
    if missing:
        print("warning: missing host tools: " + ", ".join(missing), file=sys.stderr)
        print("Debian/Ubuntu package: binutils-mipsel-linux-gnu", file=sys.stderr)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--skip-python", action="store_true")
    parser.add_argument("--skip-toolchain", action="store_true")
    args = parser.parse_args()
    os.chdir(ROOT)
    check_host_tools()
    if not args.skip_python:
        setup_python()
    if not args.skip_toolchain:
        setup_toolchain()
    print("bootstrap complete")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
