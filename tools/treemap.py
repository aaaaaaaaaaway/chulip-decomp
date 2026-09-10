#!/usr/bin/env python3
"""Generate an offline function-size treemap from the strict matching ledger."""
from __future__ import annotations

import argparse
import hashlib
import html
import json
from pathlib import Path

import progress

ROOT = progress.ROOT
WIDTH, HEIGHT = 1440, 800
COLORS = {"matched": "#36b58a", "unmatched": "#c85c6a", "assembly": "#4b86ca"}
LABELS = {"matched": "Verified C match", "unmatched": "Unmatched", "assembly": "Handwritten assembly (unmatched)"}


def layout(items, x=0.0, y=0.0, width=WIDTH, height=HEIGHT):
    """Squarify positive sizes; coordinates conserve the entire byte-weighted area."""
    ordered = sorted(items, key=lambda item: (-item["size"], item["address"]))
    if not ordered:
        return []
    scale = width * height / sum(item["size"] for item in ordered)
    pending = [(item, item["size"] * scale) for item in ordered]
    rectangles = []

    def worst(row, side):
        if not row:
            return float("inf")
        areas = [area for _, area in row]
        total = sum(areas)
        return max(side * side * max(areas) / total**2, total**2 / (side * side * min(areas)))

    def place(row, x, y, width, height):
        total = sum(area for _, area in row)
        if width >= height:
            strip = total / height
            offset = y
            for item, area in row:
                extent = area / strip
                rectangles.append({**item, "rect": [x, offset, strip, extent]})
                offset += extent
            return x + strip, y, max(0.0, width - strip), height
        strip = total / width
        offset = x
        for item, area in row:
            extent = area / strip
            rectangles.append({**item, "rect": [offset, y, extent, strip]})
            offset += extent
        return x, y + strip, width, max(0.0, height - strip)

    row = []
    for item in pending:
        side = min(width, height)
        if not row or worst(row + [item], side) <= worst(row, side):
            row.append(item)
        else:
            x, y, width, height = place(row, x, y, width, height)
            row = [item]
    if row:
        place(row, x, y, width, height)
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
    for item in data["functions"]:
        x, y, w, h = item["rect"]
        title = f'{item["name"]} · {item["size"]:,} bytes · {LABELS[item["status"]]}'
        out.append(f'<g data-name="{html.escape(item["name"])}"><title>{html.escape(title)}</title>'
                   f'<rect x="{x:.5f}" y="{y:.5f}" width="{w:.5f}" height="{h:.5f}" '
                   f'fill="{COLORS[item["status"]]}" stroke="#101a29" stroke-width="0.65"/>')
        if w > 78 and h > 27:
            out.append(f'<text x="{x+5:.3f}" y="{y+15:.3f}" fill="#07151e" font-size="11" '
                       f'font-family="monospace" pointer-events="none">{item["address"][2:]}</text>')
            if h > 43 and w > 92:
                out.append(f'<text x="{x+5:.3f}" y="{y+30:.3f}" fill="#07151e" font-size="10" '
                           f'font-family="monospace" pointer-events="none">{item["size"]:,} B</text>')
        out.append('</g>')
    return ''.join(out)


def svg_document(data):
    t = data["totals"]
    return f'''<svg xmlns="http://www.w3.org/2000/svg" width="1440" height="960" viewBox="0 0 1440 960">
<title>Chulip function matching treemap</title>
<desc>All {t['total_functions']} functions. Rectangle area represents function bytes. Green verified C; red unmatched; blue handwritten assembly, still unmatched.</desc>
<rect width="1440" height="960" fill="#101a29"/>
<g fill="#eef4fa" font-family="sans-serif"><text x="24" y="38" font-size="26" font-weight="bold">CHULIP / FUNCTION MAP</text>
<text x="24" y="66" font-size="16">{t['matched_functions']:,} / {t['total_functions']:,} functions · {t['matched_bytes']:,} / {t['total_bytes']:,} bytes · {t['byte_percent']:.2f}% of function bytes matched</text>
<text x="24" y="96" fill="{COLORS['matched']}" font-size="14">■ Verified C match</text><text x="235" y="96" fill="{COLORS['unmatched']}" font-size="14">■ Unmatched</text><text x="402" y="96" fill="{COLORS['assembly']}" font-size="14">■ Handwritten assembly (unmatched)</text></g>
<g transform="translate(0 116)">{cells(data)}</g>
<text x="24" y="945" font-family="sans-serif" font-size="13" fill="#b5c3d4">One rectangle per function. Area = retail function bytes. Full target retained; no partial-match credit. Open progress.html to search and inspect.</text>
</svg>'''


def outputs(data):
    template = (ROOT / "tools/templates/treemap.html").read_text()
    payload = json.dumps(data, separators=(",", ":")).replace("<", "\\u003c")
    return {"docs/progress.html": template.replace("__TREEMAP_DATA__", payload),
            "docs/progress.svg": svg_document(data)}


def png_preview(data, path):
    """Optional local raster export; Pillow is not needed for HTML/SVG generation."""
    from PIL import Image, ImageDraw, ImageFont
    im = Image.new("RGB", (1440, 960), "#101a29")
    draw = ImageDraw.Draw(im)
    font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    font = lambda size: ImageFont.truetype(font_path, size)
    t = data['totals']
    draw.text((24, 15), "CHULIP / FUNCTION MAP", font=font(26), fill="#eef4fa")
    draw.text((24, 51), f"{t['matched_functions']:,} / {t['total_functions']:,} functions · {t['matched_bytes']:,} / {t['total_bytes']:,} bytes · {t['byte_percent']:.2f}% of function bytes matched", font=font(16), fill="#eef4fa")
    for x, status in [(24, 'matched'), (235, 'unmatched'), (402, 'assembly')]:
        draw.rectangle((x, 84, x+10, 94), fill=COLORS[status])
        draw.text((x+18, 80), LABELS[status], font=font(14), fill=COLORS[status])
    for item in data['functions']:
        x, y, w, h = item['rect'];y += 116
        draw.rectangle((x, y, x+w, y+h), fill=COLORS[item['status']], outline="#101a29", width=1)
        if w > 78 and h > 27:
            draw.text((x+5, y+4), item['address'][2:], font=font(11), fill="#07151e")
            if h > 43 and w > 92:
                draw.text((x+5, y+19), f"{item['size']:,} B", font=font(10), fill="#07151e")
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
