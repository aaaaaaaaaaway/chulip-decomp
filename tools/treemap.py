#!/usr/bin/env python3
"""Generate an offline function-size treemap from the strict matching ledger."""
from __future__ import annotations

import argparse
import hashlib
import html
import json
import math
import subprocess
from pathlib import Path

import progress

ROOT = progress.ROOT
WIDTH, HEIGHT = 1440, 800
# decomp.dev e9c086adb74d2fe569541cd715cd9312d7641313, js/treemap.ts.
# Only exact matches receive 100%; all other functions use its zero-percent gray.
COLORS = {"matched": "#00c600", "unmatched": "#353535", "assembly": "#353535"}
OUTER_COLORS = {"matched": "#005600", "unmatched": "#262626", "assembly": "#262626"}
LABELS = {"matched": "Verified C match", "unmatched": "Unmatched", "assembly": "Handwritten assembly (unmatched)"}


def layout(items, x=0.0, y=0.0, width=WIDTH, height=HEIGHT):
    """Use the same pinned binary treemap engine and f32 geometry as decomp.dev."""
    ordered = sorted(items, key=lambda item: (-item["size"], item["address"]))
    if not ordered:
        return []
    subprocess.run([
        "cargo", "build", "--quiet", "--locked", "--release",
        "--manifest-path", str(ROOT / "tools/treemap-layout/Cargo.toml"),
        "--target-dir", str(ROOT / "build/treemap-layout"),
    ], check=True)
    result = subprocess.run(
        [str(ROOT / "build/treemap-layout/release/chulip-treemap-layout")],
        input=" ".join([str(width / height)] + [str(i["size"]) for i in ordered]),
        text=True, capture_output=True, check=True,
    )
    rectangles = []
    for line in result.stdout.splitlines():
        index, rx, ry, rw, rh = line.split()
        rectangles.append({**ordered[int(index)], "rect": [
            x + float(rx) * width, y + float(ry) * height,
            float(rw) * width, float(rh) * height,
        ]})
    assert len(rectangles) == len(ordered)
    return rectangles


def snapshot():
    totals = progress.progress_data()
    catalog = json.loads((ROOT / "config/functions.json").read_text())["functions"]
    ledger = {entry["function"]: entry for entry in json.loads((ROOT / "config/matched.json").read_text())}
    items = []
    for entry in catalog:
        name = entry["name"]
        if entry["size"] <= 0:
            raise ValueError(f"nonpositive function size: {name}")
        status = "matched" if name in ledger else "assembly" if entry.get("handwritten") else "unmatched"
        items.append(dict(name=name, address=entry["address"], size=entry["size"], status=status,
                          source=ledger.get(name, {}).get("source", "")))
    assert len(items) == totals["total_functions"]
    assert sum(item["size"] for item in items) == totals["total_bytes"]
    assert sum(item["size"] for item in items if item["status"] == "matched") == totals["matched_bytes"]
    counts = {status: dict(functions=sum(i["status"] == status for i in items),
                           bytes=sum(i["size"] for i in items if i["status"] == status)) for status in COLORS}
    digest = hashlib.sha256()
    for name in ("functions", "matched", "reconstructed"):
        digest.update((ROOT / f"config/{name}.json").read_bytes())
    return dict(totals=totals, counts=counts, ledger_sha256=digest.hexdigest(), functions=layout(items))


def cells(data):
    out = []
    for index, item in enumerate(data["functions"]):
        x, y, w, h = item["rect"]
        title = f'{item["name"]} · {item["size"]:,} bytes · {LABELS[item["status"]]}'
        # Radial shading from decomp.dev's canvas renderer, in absolute coordinates.
        out.append(f'<radialGradient id="unit-{index}" gradientUnits="userSpaceOnUse" '
                   f'cx="{x+w*.4:.5f}" cy="{y+h*.4:.5f}" '
                   f'fr="{(w+h)*.1:.5f}" r="{(w+h)*.5:.5f}">'
                   f'<stop offset="0" stop-color="{COLORS[item["status"]]}"/>'
                   f'<stop offset="1" stop-color="{OUTER_COLORS[item["status"]]}"/>'
                   '</radialGradient>')
        out.append(f'<g data-name="{html.escape(item["name"])}"><title>{html.escape(title)}</title>'
                   f'<rect x="{x:.5f}" y="{y:.5f}" width="{w:.5f}" height="{h:.5f}" '
                   f'fill="url(#unit-{index})" stroke="#000" stroke-width="0.5"/></g>')
    return ''.join(out)


def svg_document(data):
    t = data["totals"]
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="1440" height="960" viewBox="0 0 1440 960">
<title>Chulip function matching treemap</title>
<desc>All {t['total_functions']} functions. Rectangle area represents function bytes. Green verified C; gray unmatched, including handwritten assembly.</desc>
<rect width="1440" height="960" fill="#181c25"/>
<g fill="#eef4fa" font-family="sans-serif"><text x="24" y="38" font-size="26" font-weight="bold">CHULIP / FUNCTION MAP</text>
<text x="24" y="66" font-size="16">{t['matched_functions']:,} / {t['total_functions']:,} functions · {t['matched_bytes']:,} / {t['total_bytes']:,} bytes · {t['byte_percent']:.2f}% of function bytes matched</text>
<text x="24" y="96" fill="{COLORS['matched']}" font-size="14">■ Verified C match</text><text x="235" y="96" fill="#b5c3d4" font-size="14">■ Unmatched (including original assembly)</text></g>
<g transform="translate(0 116)">{cells(data)}</g>
<text x="24" y="945" font-family="sans-serif" font-size="13" fill="#b5c3d4">One rectangle per function. Area = retail function bytes. Full target retained; no partial-match credit. Open progress.html to search and inspect.</text>
</svg>'''


def outputs(data):
    template = (ROOT / "tools/templates/treemap.html").read_text()
    payload = json.dumps(data, separators=(",", ":")).replace("<", "\\u003c")
    return {"docs/progress.html": template.replace("__TREEMAP_DATA__", payload).replace("__TREEMAP_CELLS__", cells(data)),
            "docs/progress.svg": svg_document(data)}


def png_preview(data, path):
    """Optional local raster export; Pillow is not needed for HTML/SVG generation."""
    from PIL import Image, ImageDraw, ImageFont
    im = Image.new("RGB", (1440, 960), "#181c25")
    draw = ImageDraw.Draw(im)
    font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    font = lambda size: ImageFont.truetype(font_path, size)
    t = data['totals']
    draw.text((24, 15), "CHULIP / FUNCTION MAP", font=font(26), fill="#eef4fa")
    draw.text((24, 51), f"{t['matched_functions']:,} / {t['total_functions']:,} functions · {t['matched_bytes']:,} / {t['total_bytes']:,} bytes · {t['byte_percent']:.2f}% of function bytes matched", font=font(16), fill="#eef4fa")
    for x, status in [(24, 'matched'), (235, 'unmatched')]:
        draw.rectangle((x, 84, x+10, 94), fill=COLORS[status])
        label = LABELS[status] if status == 'matched' else 'Unmatched (including original assembly)'
        draw.text((x+18, 80), label, font=font(14), fill="#b5c3d4")
    pixels = im.load()
    for item in data['functions']:
        x, y, w, h = item['rect']; y += 116
        cx, cy, r0, r1 = x+w*.4, y+h*.4, (w+h)*.1, (w+h)*.5
        inner, outer = [[int(color[i:i+2], 16) for i in (1, 3, 5)] for color in
                        (COLORS[item['status']], OUTER_COLORS[item['status']])]
        for py in range(max(116, math.ceil(y)), min(916, math.ceil(y+h))):
            for px in range(max(0, math.ceil(x)), min(1440, math.ceil(x+w))):
                amount = max(0, min(1, (math.hypot(px-cx, py-cy)-r0)/(r1-r0)))
                pixels[px, py] = tuple(round(a+(b-a)*amount) for a,b in zip(inner, outer))
        draw.rectangle((x, y, x+w, y+h), outline="#000", width=1)
    draw.text((24, 929), "One rectangle per function. Area = retail function bytes. Full target retained; no partial-match credit.", font=font(13), fill="#b5c3d4")
    path.parent.mkdir(parents=True, exist_ok=True);im.save(path)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    parser.add_argument('--png', type=Path, help='optional raster export; requires Pillow')
    args = parser.parse_args()
    data = snapshot()
    for name, content in outputs(data).items():
        path = ROOT / name
        if args.check:
            if not path.is_file() or path.read_text() != content:
                raise SystemExit(f'{name} is stale; run make progress')
        else:
            path.write_text(content)
    if args.png:
        png_preview(data, args.png)
    print(f'TREEMAP {"OK" if args.check else "UPDATED"}: {len(data["functions"])} functions, {data["totals"]["total_bytes"]} bytes')


if __name__ == '__main__':
    main()
