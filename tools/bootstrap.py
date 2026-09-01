#!/usr/bin/env python3
"""Install the public Python and historical-toolchain prerequisites locally."""

from __future__ import annotations

import argparse
import hashlib
import json
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
TOOLCHAINS = ROOT / "config/toolchains.json"
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


def configuration() -> dict[str, object]:
    return json.loads(TOOLCHAINS.read_text())


def relative_tool_path(value: object) -> Path:
    path = Path(str(value))
    try:
        return path.relative_to("tools/compilers")
    except ValueError as error:
        raise SystemExit(f"toolchain path is outside tools/compilers: {path}") from error


def archive_specs(config: dict[str, object]) -> dict[Path, dict[str, object]]:
    """Return every unique configured archive and the files it must provide."""
    result: dict[Path, dict[str, object]] = {}
    profiles = config.get("profiles")
    if not isinstance(profiles, dict) or not profiles:
        raise SystemExit("config/toolchains.json has no profiles")
    for profile_name, raw_profile in profiles.items():
        if not isinstance(raw_profile, dict):
            raise SystemExit(f"invalid toolchain profile: {profile_name}")
        for prefix, artifact_key in (("", "compiler"), ("assembler_", "assembler")):
            archive_key = prefix + "archive"
            if archive_key not in raw_profile:
                continue
            url_key = prefix + "archive_url"
            hash_key = prefix + "archive_sha256"
            missing = [key for key in (url_key, hash_key, artifact_key) if not raw_profile.get(key)]
            if missing:
                raise SystemExit(
                    f"profile {profile_name} lacks {', '.join(missing)} for {archive_key}"
                )
            archive = ROOT / str(raw_profile[archive_key])
            artifact = ROOT / str(raw_profile[artifact_key])
            relative = relative_tool_path(raw_profile[artifact_key])
            target = COMPILERS / relative.parts[0]
            spec = result.setdefault(
                archive,
                {
                    "url": str(raw_profile[url_key]),
                    "sha256": str(raw_profile[hash_key]),
                    "target": target,
                    "required": set(),
                    "profiles": set(),
                },
            )
            identity = (spec["url"], spec["sha256"], spec["target"])
            requested = (str(raw_profile[url_key]), str(raw_profile[hash_key]), target)
            if identity != requested:
                raise SystemExit(f"conflicting metadata for archive {archive.relative_to(ROOT)}")
            spec["required"].add(artifact)
            spec["profiles"].add(str(profile_name))
        if raw_profile.get("assembler") and not raw_profile.get("assembler_archive"):
            archive = ROOT / str(raw_profile["archive"])
            artifact = ROOT / str(raw_profile["assembler"])
            target = COMPILERS / relative_tool_path(raw_profile["assembler"]).parts[0]
            if target != result[archive]["target"]:
                raise SystemExit(
                    f"profile {profile_name} assembler needs separate archive metadata"
                )
            result[archive]["required"].add(artifact)
    return result


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def sha256_stream(stream) -> str:
    digest = hashlib.sha256()
    for chunk in iter(lambda: stream.read(1024 * 1024), b""):
        digest.update(chunk)
    return digest.hexdigest()


def verify_archive_install(archive: Path, spec: dict[str, object]) -> None:
    """Prove configured installed artifacts still equal the pinned archive."""
    expected = str(spec["sha256"])
    if not archive.is_file() or sha256(archive) != expected:
        raise SystemExit(f"missing or invalid pinned archive: {archive.relative_to(ROOT)}")
    target = Path(spec["target"])
    with tarfile.open(archive, "r:*") as bundle:
        members = {}
        for member in bundle.getmembers():
            name = member.name
            while name.startswith("./"):
                name = name[2:]
            members[name] = member
        for installed in spec["required"]:
            installed = Path(installed)
            relative = installed.relative_to(target).as_posix()
            member = members.get(relative)
            archived = bundle.extractfile(member) if member is not None else None
            if archived is None or not installed.is_file():
                raise SystemExit(
                    f"pinned archive lacks installed artifact: {installed.relative_to(ROOT)}"
                )
            with archived:
                archived_hash = sha256_stream(archived)
            if sha256(installed) != archived_hash:
                raise SystemExit(
                    f"installed artifact differs from pinned archive: "
                    f"{installed.relative_to(ROOT)}"
                )


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


def setup_wibo(config: dict[str, object], check_only: bool) -> None:
    profiles = config["profiles"]
    if not any(profile.get("runner") == "wibo-driver" or profile.get("assembler_runner") == "wibo" for profile in profiles.values()):
        return
    system = (platform.system(), platform.machine())
    if system not in WIBO_ASSETS:
        raise SystemExit(f"no pinned Wibo bootstrap asset for {system[0]} {system[1]}")
    wibo_url, wibo_hash = WIBO_ASSETS[system]
    configured_hash = str(config["runtime"].get("wibo_sha256", ""))
    if configured_hash != wibo_hash:
        raise SystemExit("Wibo asset hash disagrees with config/toolchains.json")
    wibo = COMPILERS / "wibo"
    if check_only:
        if not wibo.is_file() or sha256(wibo) != wibo_hash:
            raise SystemExit("missing or invalid pinned Wibo executable")
    else:
        download(wibo_url, wibo, wibo_hash)
        wibo.chmod(wibo.stat().st_mode | 0o111)


def install_archive(archive: Path, spec: dict[str, object], check_only: bool) -> None:
    target = Path(spec["target"])
    required = set(spec["required"])
    present = target.is_dir() and all(Path(path).is_file() for path in required)
    if check_only:
        if not present:
            names = ", ".join(sorted(str(Path(path).relative_to(ROOT)) for path in required))
            raise SystemExit(f"missing configured toolchain files: {names}")
        verify_archive_install(archive, spec)
        return
    download(str(spec["url"]), archive, str(spec["sha256"]))
    if not present:
        if target.exists():
            raise SystemExit(f"incomplete toolchain directory exists: {target}")
        COMPILERS.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix=target.name + "-", dir=COMPILERS) as temp:
            temp_path = Path(temp)
            with tarfile.open(archive, "r:*") as bundle:
                bundle.extractall(temp_path, filter="data")
            missing = [
                path
                for path in required
                if not (temp_path / Path(path).relative_to(target)).is_file()
            ]
            if missing:
                names = ", ".join(
                    sorted(str(Path(path).relative_to(ROOT)) for path in missing)
                )
                raise SystemExit(
                    f"archive does not provide configured toolchain files: {names}"
                )
            temp_path.rename(target)
    if not all(Path(path).is_file() for path in required):
        raise SystemExit(f"archive did not provide all configured files: {archive.relative_to(ROOT)}")
    verify_archive_install(archive, spec)
    print(
        f"verified {target.relative_to(COMPILERS)} for profiles: "
        + ", ".join(sorted(spec["profiles"]))
    )


def setup_linux32_runtime(config: dict[str, object], check_only: bool) -> None:
    profiles = config["profiles"]
    if not any(profile.get("runner") == "linux32-cc1" or profile.get("assembler_runner") == "linux32" for profile in profiles.values()):
        return
    runtime = config.get("runtime", {})
    keys = (
        "libc6_i386_archive",
        "libc6_i386_archive_url",
        "libc6_i386_archive_sha256",
        "linux32_loader_sha256",
        "linux32_libc_sha256",
    )
    missing = [key for key in keys if not runtime.get(key)]
    if missing:
        raise SystemExit("linux32 profiles require runtime metadata: " + ", ".join(missing))
    archive = ROOT / str(runtime["libc6_i386_archive"])
    root = COMPILERS / "runtime/root"
    required = (root / "usr/lib32/ld-linux.so.2", root / "usr/lib32/libc.so.6")
    present = root.is_dir() and all(path.is_file() for path in required)
    if check_only:
        if not present:
            raise SystemExit("missing pinned linux32 runtime")
        if not archive.is_file() or sha256(archive) != runtime["libc6_i386_archive_sha256"]:
            raise SystemExit("missing or invalid pinned linux32 runtime archive")
        if sha256(required[0]) != runtime["linux32_loader_sha256"]:
            raise SystemExit("installed linux32 loader differs from pinned runtime")
        if sha256(required[1]) != runtime["linux32_libc_sha256"]:
            raise SystemExit("installed linux32 libc differs from pinned runtime")
        return
    if not present:
        if root.exists():
            raise SystemExit(f"incomplete linux32 runtime exists: {root}")
        if shutil.which("dpkg-deb") is None:
            raise SystemExit("dpkg-deb is required to extract the pinned linux32 runtime")
        download(
            str(runtime["libc6_i386_archive_url"]),
            archive,
            str(runtime["libc6_i386_archive_sha256"]),
        )
        root.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix="linux32-runtime-", dir=root.parent) as temp:
            extracted = Path(temp) / "root"
            subprocess.run(["dpkg-deb", "-x", str(archive), str(extracted)], check=True)
            if not all(
                (extracted / path.relative_to(root)).is_file() for path in required
            ):
                raise SystemExit("pinned linux32 runtime lacks its loader or libc")
            extracted.rename(root)
    if not all(path.is_file() for path in required):
        raise SystemExit("pinned linux32 runtime lacks its loader or libc")
    if sha256(required[0]) != runtime["linux32_loader_sha256"]:
        raise SystemExit("installed linux32 loader differs from pinned runtime")
    if sha256(required[1]) != runtime["linux32_libc_sha256"]:
        raise SystemExit("installed linux32 libc differs from pinned runtime")
    print("verified pinned linux32 runtime")


def setup_toolchain(check_only: bool = False) -> None:
    config = configuration()
    setup_wibo(config, check_only)
    for archive, spec in archive_specs(config).items():
        install_archive(archive, spec, check_only)
    setup_linux32_runtime(config, check_only)


def check_host_tools() -> None:
    required = [
        "mipsel-linux-gnu-as",
        "mipsel-linux-gnu-ld",
        "mipsel-linux-gnu-nm",
        "mipsel-linux-gnu-objcopy",
        "mipsel-linux-gnu-readelf",
        "mipsel-linux-gnu-size",
    ]
    missing = [command for command in required if not shutil.which(command)]
    if missing:
        raise SystemExit(
            "missing host tools: "
            + ", ".join(missing)
            + "; Debian/Ubuntu package: binutils-mipsel-linux-gnu"
        )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--skip-python", action="store_true")
    parser.add_argument("--skip-toolchain", action="store_true")
    parser.add_argument("--check", action="store_true", help="verify without downloading or installing")
    args = parser.parse_args()
    os.chdir(ROOT)
    check_host_tools()
    if not args.skip_python and not args.check:
        setup_python()
    if not args.skip_toolchain:
        setup_toolchain(check_only=args.check)
    print("bootstrap check complete" if args.check else "bootstrap complete")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
