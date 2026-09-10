# Recovering unfinished candidate batches

Before starting a new matching search, compare prior lane manifests and candidate
sources with the current reconstruction ledger. A source file without a campaign
sidecar can still have a valid historical proof in its original lane manifest.
The default campaign range is the catalog function body; a compiler's ordinary
trailing alignment can therefore make an otherwise exact source appear to miss
by one word.

## Inventory and replay

1. Search `work/lanes` and `work/claude` for `manifest.jsonl`, other lane JSONL
   manifests, and lane notes. Also inventory packet candidates without `.c.json`
   sidecars. Compare function names with `config/reconstructed.json`; do not
   count old reports as current progress.
2. Recover the recorded source, compiler profile, object flags, range and data
   placement from the original manifest. Compare the source hashes when both a
   lane copy and a packet copy exist. Rank unreconstructed candidates by byte
   value and evidence of a prior exact result. Replay a bounded batch, recording
   every result rather than retrying the same unpromising draft each session.
3. Verify the proposed range against `config/functions.json` and the retail
   bytes. Extending a body to the next function is justified only when that
   interval is the compiler's natural alignment and the retail padding bytes
   match. Never add source padding or extend through another function. Record
   the body size, padding size and next function separately.
4. Copy each source into its normal campaign packet with a new descriptive name
   and matching `.c.json` metadata. Keep original candidate files intact. Use
   `tools/match_artifacts.py` for cheap triage, then run the complete isolated
   verifier through `python3 tools/campaign.py harvest PATH --recheck`. The thin
   text comparator is not the final gate for jump tables or other data.
5. Review readable source and any owned data. An isolated exact source with a
   small-data definition still needs correct full-image placement. Import a
   reviewed batch through the guarded promotion pipeline; whole-image matching,
   the independent baseline and public checks remain mandatory.
6. Publish separate counts for recovered prior source and newly solved source.
   Leave near matches and integration failures uncounted. Preserve successful
   packet sidecars so the next pass does not rediscover their range and profile.

## Evidence from the 2026-09-09 jump-table lane recovery

The local `work/lanes/claude_jt3/manifest.jsonl` recorded five exact sources. Two
were already in the current reconstruction ledger. Three remaining sources
replayed with the recorded SN 1.36 / G8 / PS2 assembler profile and no extra
object flags:

| Function | Function bytes | Existing alignment | Complete verification range |
| --- | ---: | ---: | --- |
| `func_0013A120` | 1,404 | 4 | `0x0013A120..0x0013A6A0` |
| `func_00144FD8` | 1,116 | 4 | `0x00144FD8..0x00145438` |
| `func_00148CE0` | 676 | 4 | `0x00148CE0..0x00148F88` |

These are 3,196 bytes of recovered prior function source, not new algorithms.
Their integration status is the live reconstruction ledger. The four other
unfinished drafts in that lane did not reproduce an exact match and remain
separate search targets. Historical near-match scores did not all reproduce,
which reinforces the need for fresh replay.

The lane notes also contained useful source-shape evidence: a pointer loaded
through a union member preserves alias-sensitive reloads without volatile
accesses. Applying that established pattern to the large `func_00149C88` draft
removed all four mismatching shared-tail branch pairs, reducing its distance
from 15 to seven words. This is search evidence and does not count as a match.

## Return declarations are a diagnostic, not a blanket rewrite

Correcting an unused callee result from `void` to an evidence-supported `int`
can change register allocation in historical GCC. This solved two object-family
functions in the same session. A bounded follow-up scanned 20 large pending
functions totaling 90,824 bytes: 18 paired comparisons completed and two drafts
were rejected by existing ABI-diagnostic checks. Blanket return corrections
solved no new function in that batch; two drafts improved by six and twelve
words. Some previously exact sources became worse.

Use matched callee definitions and retail return paths to identify justified
experiments. Preserve parameter declarations during a return-type experiment,
record the exact changed declarations and compare the output. Matched local
source does not authenticate one original prototype shared by every historical
translation unit. Do not rewrite already matched callers en masse.
