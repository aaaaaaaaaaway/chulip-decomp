# Parallel matching workflow

`tools/campaign.py` coordinates local discovery work. Its packets, claims,
attempts, and candidates live under ignored `work/campaign/`; none count as
progress.

## Start a lane

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
