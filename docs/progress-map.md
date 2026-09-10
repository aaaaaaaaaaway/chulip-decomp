# Function-size progress map

Open [progress.html](progress.html) in a local browser for the interactive map,
or [progress.svg](progress.svg) for the static chart shown in the README.
No server, package installation or network connection is needed.

Every one of the2,189 catalog functions gets a rectangle. Its area is proportional
to its retail function size. Green means readable C verified in isolation and
in the full-image build; red means unmatched; blue means a catalog-marked
handwritten function that remains unmatched. All colors remain in the663,704-byte
function denominator. No partial-match score or raw-assembly credit is used.
These charts cover function bytes; they do not claim all ELF data is decompiled.

Search by address, function name or matched source path. Click a rectangle or
search result for its byte size, address and source link. Highlight filters dim
other rectangles without changing their areas. “Unmatched functions” includes
blue assembly. Zoom to a selected function, drag while zoomed, and reset to
return to the whole project.

`make progress` regenerates both files from the current ledgers. The promotion
transaction regenerates them and restores them on failure. Public checks and
the commit hook reject a stale map. `make treemap` refreshes only the chart.
An optional local PNG export is available with Pillow installed:

```sh
python3 tools/treemap.py --png work/chulip-progress.png
```

## decomp.dev and objdiff

The familiar community dashboard is [decomp.dev](https://github.com/encounter/decomp.dev).
Its [treemap implementation](https://github.com/encounter/decomp.dev/blob/e9c086adb74d2fe569541cd715cd9312d7641313/js/treemap.ts)
uses report-unit code size and matching percentage. Chulip can export the
[official objdiff v2 report format](https://github.com/encounter/objdiff/blob/fba10a617154f19b3fc25c8817dc81f81d8489b5/objdiff-core/protos/report.proto):

```sh
make report
# writes build/report.json
```

The exporter needs only Python and the public metadata, without the game image,
compiler toolchains or an objdiff installation. It creates one logical display
unit per function, including separate members of co-compiled source files.
These display units make no claim about authentic translation-unit boundaries.
Per-function fuzzy fields are deliberately0 or100; aggregate measures use the
strict verified byte percentage. Complete and matched code are the same under
this project's rules. Unmatched work and original assembly receive zero credit.

The report uses decimal strings for protobuf uint64 sizes/addresses. Each
logical unit's section-relative function address is0; the real address is in
`metadata.virtual_address`. No data-section progress is exported.

The exporter was validated against the pinned official protobuf schema, including
JSON parsing and a binary round trip. Accounting tests cover co-compiled members,
handwritten denominator retention, isolated-only noncredit and invalid ledgers.
The local chart was also checked in Chrome for search, selection, source links,
status filters, tooltips and zoom. Its2,189 rectangle areas and bounds were
independently checked for conservation and overlap. Nothing is hosted on
decomp.dev merely by generating these files; the public service needs separate
repository/report registration.
