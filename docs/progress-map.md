# Function-size progress map

Open [progress.html](progress.html) in a local browser for the interactive map,
or [progress.svg](progress.svg) for the static chart shown in the README.
Viewing the generated files needs no server, package installation or network
connection. Regenerating them requires Python and Rust/Cargo; Cargo downloads
the locked layout dependencies on the first run and caches them thereafter.

Every one of the 2,189 catalog functions gets a rectangle. Its area is proportional
to its retail function size. Green means readable C verified in isolation and
in the full-image build; gray means unmatched, including catalog-marked
handwritten functions. All functions remain in the 663,704-byte
function denominator. No partial-match score or raw-assembly credit is used.
These charts cover function bytes; they do not claim all ELF data is decompiled.

Search by address, function name or matched source path. Click a rectangle or
search result for its byte size, address and source link. Highlight filters dim
other rectangles without changing their areas. “Unmatched functions” includes
original assembly. Zoom to a selected function, drag while zoomed, and reset to
return to the whole project.

`make progress` regenerates both files from the current ledgers. The promotion
transaction regenerates them and restores them on failure. Public checks and
the commit hook reject a stale map. `make treemap` refreshes only the chart.
An optional local PNG export is available with Pillow installed:

```sh
python3 tools/treemap.py --png work/chulip-progress.png
```

## decomp.dev and objdiff

The community dashboard is [decomp.dev](https://github.com/encounter/decomp.dev).
This generator now calls the same **streemap 0.1.0 binary layout engine** as its
[layout implementation](https://github.com/encounter/decomp.dev/blob/e9c086adb74d2fe569541cd715cd9312d7641313/crates/images/src/treemap.rs),
through the small Rust helper in `tools/treemap-layout`. `Cargo.lock` pins the
library and its dependencies; build output stays in ignored `build/treemap-layout`.
The former custom Python squarified layout has been removed. Items are ordered
by descending size with address ties, then use upstream's normalized f32 geometry.

HTML, SVG and PNG share its [renderer conventions](https://github.com/encounter/decomp.dev/blob/e9c086adb74d2fe569541cd715cd9312d7641313/js/treemap.ts):
radial shading, black borders, green at 100% and gray at 0%, with no text inside
any block. Names and sizes remain available through hover, selection and search.
Upstream uses blue for partial matching. Because this project's report only
credits fully verified matches, there are no blue partial-progress blocks.
The local search/zoom interface remains specific to Chulip; this is not a hosted
decomp.dev page or a claim that our logical function units are original objects.

Chulip can export the
[official objdiff v2 report format](https://github.com/encounter/objdiff/blob/fba10a617154f19b3fc25c8817dc81f81d8489b5/objdiff-core/protos/report.proto):

```sh
make report
# writes build/report.json
```

The exporter needs only Python and the public metadata, without the game image,
compiler toolchains or an objdiff installation. It creates one logical display
unit per function, including separate members of co-compiled source files.
These display units make no claim about authentic translation-unit boundaries.
Per-function fuzzy fields are deliberately 0 or 100; aggregate measures use the
strict verified byte percentage. Complete and matched code are the same under
this project's rules. Unmatched work and original assembly receive zero credit.

The report uses decimal strings for protobuf uint64 sizes/addresses. Each
logical unit's section-relative function address is 0; the real address is in
`metadata.virtual_address`. No data-section progress is exported.

The exporter was validated against the pinned official protobuf schema, including
JSON parsing and a binary round trip. Accounting tests cover co-compiled members,
handwritten denominator retention, isolated-only noncredit and invalid ledgers.
The local chart was also checked in Chrome for search, selection, source links,
status filters, tooltips and zoom. Its 2,189 rectangle areas and bounds were
independently checked for conservation and overlap. Nothing is hosted on
decomp.dev merely by generating these files; the public service needs separate
repository/report registration.
