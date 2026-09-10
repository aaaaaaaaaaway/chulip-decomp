# Parallel matching workflow

`tools/campaign.py` coordinates local discovery work. Its packets, claims,
attempts, and candidates live under ignored `work/campaign/`; none count as
progress.

## Start a lane

Select a family before selecting isolated functions. Search
`docs/matching-knowledge.jsonl`, `docs/candidate-recovery.md`, and existing lane
notes for its global symbols and callees. Older sidecarless exact candidates
can still be recovered through fresh verification. Do not repeat a recorded
permutation plateau unless a new source, type, or compiler hypothesis changes
the experiment.

```sh
python3 tools/family_queue.py --limit 10
python3 tools/family_queue.py --anchor D_001ED6C0
rg -n 'D_001ED6C0|func_00158868' docs work/lanes --glob '*.md' --glob '*.jsonl'
python3 tools/callee_context.py work/campaign/packets/FUNCTION/candidates/CANDIDATE.c
```

The inventory links pending members to already matched source examples. Its
clusters overlap and its byte totals are investigation scope, not promised
matches. For recognizable library code, compare historical target source and
build macros before local syntax searches. Original object grouping still
requires independent artifact or boundary evidence.

`callee_context.py` flags explicit parameter-count and floating-point-position
conflicts against matched callee definitions. It does not rewrite source and is
not a complete C parser. Check the caller's actual argument setup as well as
the callee: historical code may pass unused extra arguments. The giant script
drafts had missing float arguments that the compiler could not diagnose because
their local declarations were wrong too. Fixing these restores semantics; it
does not establish an exact match by itself.

The checker also flags direct empty calls to matched definitions with required
parameters, even behind an unspecified `func()` declaration. This catches
wrappers that accidentally rely on the compiler retaining the incoming argument
register. Findings include the call line and matched provider; confirm the
actual forwarding and return contract in retail before repairing the source.
This narrow scan ignores macros and does not establish general C call arity.

```sh
python3 tools/campaign.py plan --limit 20
python3 tools/campaign.py packet --next --owner NAME
python3 tools/campaign.py status
```

A claim prevents another worker from selecting the same function until its
lease expires. Repeating `packet` with the same owner renews the lease. Packet
directories contain the retail assembly, exact catalog facts, usage hits,
matched references, prior local candidate paths, and a `candidates/` directory.
If a local Ghidra export exists, it is copied into the packet as context only.

All discovery workers must share this worktree so they also share
`work/campaign/claims/`. Give every lane a unique owner. Workers may edit only
their claimed packet and may run isolated harvests concurrently. One
coordinator owns `promote --write`, tracked files, commits, and pushes; those
operations remain serialized.

The full builder compiles independent units concurrently, using up to four
jobs by default. `python3 tools/build.py --jobs 1` selects serial compilation;
`--jobs N` selects another positive limit. Each build still recompiles every
object and verifies the complete image. Candidate searches use one historical
compiler path per attempt, avoiding an additional unused assembly listing.

Collect several exact candidates before a full promotion when workers are
active. The coordinator can stage their reviewed sources and submit one JSONL
manifest to `tools/merge_candidates.py` (dry run, then `--write`). That importer
already replays every candidate and performs one transactional full-image
build for the batch. Preserve each candidate's compiler, flags, complete range,
and source hash; do not merge worker ledger or generated-file changes.

## Check candidates

Put semantic C in the packet's `candidates/` directory, then run:

```sh
python3 tools/campaign.py harvest work/campaign/packets/FUNCTION/candidates
```

The default matrix covers every configured compiler profile. A sibling
`candidate.c.json` may narrow the profiles or record reviewed object flags and
a complete source-unit range. If several profiles match, metadata must also
name the reviewed `build_profile`; the tool never chooses one arbitrarily.
Results are content-addressed, so an interrupted
or repeated harvest skips unchanged experiments and retries changed source.
The strict reconstructed-C audit rejects assembly bridges before compilation.

If review finds an unresolved semantic, storage or ABI issue, record a
`"promotion_hold": "reason and evidence path"` in the candidate sidecar. Harvest
still records the actual byte result, including exact diagnostic matches, and
prints the hold. Campaign promotion and manifest generation reject both a held
proof and an older exact proof whose current sidecar now has a hold. The CLI
checks before copying a source into `src/`. Resolve the evidence, remove the
hold and re-harvest before submitting a new reviewed proof. This records a human
review decision; it does not replace semantic review or make byte equality alone
sufficient for promotion. Hand-written batch manifests still require the same
coordinator review.

## Recovery intake

Never merge an old discovery branch into `main`. Preserve it as an immutable
local checkpoint, compare its reconstruction ledger with the current ledger,
and ignore entries already present on `main`. For each remaining function:

1. Create a normal campaign packet and lease.
2. Copy only the candidate C into the packet's `candidates/` directory.
3. Record the old profile, object flags, complete range when known, and normal
   `src/game/` destination in the candidate sidecar.
4. Harvest it again with the current verifier and toolchain.

Old README, split configuration, ledgers, generated output, and claimed match
status are not recovery inputs. They are reconstructed by transactional
promotion after the candidate passes current gates.

## Hard walls

Use high-cost or experimental agents only for a single documented hard wall,
not for bulk matching. A wall dossier must establish all of the following:

- Function boundary, ABI, profile, object flags, and verification range are no
  longer open questions.
- Relevant sanctioned profile and flag combinations have been harvested.
- At least two lawful source-shape families or two bounded mechanical searches
  have plateaued, followed by roughly 20 targeted variants with no improvement.
- The best candidate passes the strict source audit and its remaining mismatch
  is localized and classified.
- Candidate hash, exact command, size delta, mismatch map, attempted levers,
  and related solved functions are recorded in the packet.

An escalation worker keeps the existing lease and writes only into that
packet. It cannot promote, edit tracked files, commit, or push. Its result is a
hypothesis until the coordinator independently harvests and promotes it.

## Promote an exact candidate

```sh
python3 tools/campaign.py promote FUNCTION
python3 tools/campaign.py promote FUNCTION --write
```

The first command is a dry run. Promotion copies the selected exact source to
`src/` and passes a generated manifest to `tools/merge_candidates.py`. The
importer independently recompiles every profile claim and retains the change
only after the full image, baseline, progress, and public repository gates all
pass. A failed or dry-run promotion removes the temporary public source.

Only reviewed source, proof metadata, and durable findings belong in Git.

When authentic object evidence expands a provisional one-function source into
a shared source unit, prepare one manifest record for every function in that
unit and run `tools/merge_candidates.py --replace-existing`. The importer
replays every function proof, updates both exact ledgers together, and removes
superseded source files inside the same rollback-protected transaction.


## Prepare a bounded permuter search

`tools/permute.py` uses the existing historical compiler adapter. Review a small
source variation space first; stock random rewrites are not automatically safe.
The search score is diagnostic. Every output still requires semantic review,
complete emitted-byte verification, and the full promotion gates above.

For reviewed instruction-only text, direct calls can be represented using their
actual catalog symbols to remove symbolic-versus-absolute call scoring noise:

```sh
python3 tools/permute.py func_0017B3A0 \
  --source work/campaign/packets/func_0017B3A0/candidates/parallel_menu_panel.c \
  --profile ee-gcc2.95.3-136-O2-G8-ps2as \
  --output-dir work/permuter/func_0017B3A0 \
  --range-end 0x0017B5E0 --relocate-direct-calls
```

The explicit end includes the four native alignment bytes beyond this catalog
function. Without that option, the target uses the catalog function size.
The optional relocation mode decodes only external direct JAL destinations from
retail instructions and resolves them against the real function catalog. It does
not infer embedded data, jump tables, HI16/LO16 pairs or aliases. Review that the
selected range contains instructions/alignment, with no embedded literal data.
Internal and unknown call targets are rejected. Use ordinary raw-target mode
when this narrow mode does not apply.

The generated target is linked with the verifier's existing derived-symbol step
and compared against every selected retail byte before preparation succeeds.
Preparation validates the selected range before changing an existing source/oracle
pair. Target construction failures remove target.o, including failures before
assembly or during linking. The candidate compiler is
unchanged. Generated settings select R5900 disassembly; when invoking the
permuter, use `--stack-diffs --no-ignore-branch-targets` to retain those differences.
The score can still differ from a complete-byte comparison for other reasons.

On the corrected 17B3A0 source this removed 30 false call-relocation points
(score 90 to 60), while the same two instruction positions remained different
across all 576 bytes. This is a scoring correction, not a new match. See
`work/astra_permuter_oracle/proof.json` for the integrated-tool replay and
`work/parallel_permuter_panel_oracle/score_proof.json` for the before/after proof.
