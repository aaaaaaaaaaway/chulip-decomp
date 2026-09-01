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
