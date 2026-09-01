# Session handoff — Chulip decompilation

State of the parallel matching campaign, so a fresh session can resume without
re-deriving any of it. Everything below is on disk; `work/` is gitignored but
durable, and every result is reproducible from the manifests it names.

## Where progress actually lives

- `config/reconstructed.json` and `config/matched.json` are the ledgers. Truth
  is whatever `python3 tools/progress.py` prints; never quote a number from a
  document.
- Lane outputs live in `work/lanes/<lane>/` with a manifest at
  `work/claude/<lane>.jsonl`. **A manifest is the durable artifact** — if a
  ledger is ever lost, re-landing from manifests reconstructs it.
- `work/claude/hold/` stages candidate sources outside `src/` so a parallel
  session's audit never trips over them.

## The integration pipeline

    python3 work/claude/engine/collect.py <manifest>.jsonl <tag>   # verify + stage
    python3 work/claude/engine/land.py work/claude/merge-<tag>.jsonl

`land.py` bisects on failure and verifies the whole image itself, so a bad
candidate costs one batch rather than the run. **Never run two landings at
once** — `tools/merge_candidates.py` backs up and restores the shared ledgers,
so concurrent transactions silently discard each other's work. That cost real
progress earlier in this campaign.

## Gates that must stay green

    python3 tools/build.py           # complete 970,772-byte image + jump tables + labels
    python3 tools/build_baseline.py  # independent zero-C coverage
    python3 tools/repo_audit.py      # includes the assembly-bridge check
    python3 tools/progress.py --check-readme

## Standing hazards learned the hard way

- A matched source can be **replaced after** every gate has passed. Sixty-six
  ledgered sources were once rewritten into `INCLUDE_ASM` stubs by another
  session's scaffold while still recording `isolated_match: true`.
  `tools/repo_audit.py` now checks this on every run.
- `tools/match.py` **inherits the ledger's `object_flags`** when
  `--object-flag` is omitted, so `--profile X` alone does not test X in
  isolation. Always pass flags explicitly.
- Two comparisons of one function under one profile with different flags now
  use separate work directories; before that fix a parallel sweep could read a
  sibling's output and report the wrong answer.
- Waiter shells that `grep` for a process name match their own command line.
  Wait on a PID.

## Strategy

Byte-weighted, not function-weighted. The average matched function is ~84
bytes and the average unmatched one ~490; the 60 largest unmatched functions
are ~37% of everything reachable. Work families — once one member matches its
siblings usually match first try.

**A blocker needs a mechanism-level proof, not a list of failed spellings.**
Five recorded dead ends fell in one day. Re-test every parked candidate
whenever a toolchain fact changes; one such sweep converted 181 functions.

## Partial progress

`docs/nearmiss.jsonl` records how close every unmatched candidate is, in
differing 32-bit words, with the source and configuration that achieved it.
`python3 tools/nearmiss.py --report` orders the backlog by distance;
`tools/nearmiss.py <func> --source ...` measures and records an improvement and
refuses to record a regression. Treat it as the work queue: the closest
candidates are the cheapest bytes available, and a lane should record every
improvement even when it never reaches a match.

## Reference

`work/claude/AGENT-BRIEF.md` is the worker brief and carries the current rule
set. `docs/knowledge-book.md` sections 3-6 and `docs/scope.md` carry the
curated conclusions and the honest denominator.

---

## Resume state (end of first campaign session)

**Progress at handoff:** run `python3 tools/progress.py` for truth. It stood at
1,035 of 2,189 functions and 91,488 of 663,704 bytes (13.78%) while a landing
was still in flight, so the real figure is higher.

`manifests/` is a git-tracked snapshot of every lane manifest plus this file
and the worker brief. `work/` is gitignored, so `manifests/` is the copy that
survives losing the machine. Re-landing from these reconstructs the ledger.

### Immediately actionable, highest value first

1. **The 64-bit constant cluster — 162 functions, 149,700 bytes.** Worklist
   `work/claude/dli.txt`. A `ori $zero/dsll32/ori` chain means the
   `ee-gcc2.95.3-136-O2-G8-ps2as` profile: the compiler emits one `dli` pseudo
   and the assembler synthesises it. GNU `as` emits `lui/dsll32 0/ori` and can
   never match. Evidence and four worked examples in
   `work/lanes/claude_fable_isel/`.
2. **The 60 largest unmatched functions — 208,920 bytes, ~37% of everything
   reachable.** Slates in `work/claude/giant_{1,2,3,4}.txt`. The average
   unmatched function is 490 bytes against 84 for the average matched one, so
   byte-weighted selection matters more than anything else.
3. **`docs/nearmiss.jsonl` — 174 candidates, 32,084 bytes, 34 within four
   words.** `python3 tools/nearmiss.py --report` orders them. These are the
   cheapest bytes available.

### Open decisions for the user

- **A later ProDG `ps2eeas` is needed for ~124 functions.** Proven at mechanism
  level: retail pads short loops to a body of 4 instructions where the bundled
  assembler uses 5 (threshold is a code immediate at 0x404db6, no option writes
  it), and retail carries `nop;nop` before `div.s` at 171 sites across 84
  functions, per translation unit rather than per site. SN 2.95.3 plus the
  bundled Ps2EeAs matches `func_0013F468` in every byte except those two nops.
  Either source that assembler, or sanction a byte-verified per-TU post-pass as
  the God Hand project did. The knowledge book currently forbids synthetic
  nops, so this is a policy call, not a technical one.
- **Four quadword-copy helpers are not compiler output** from any of ten
  toolchains surveyed. The identical body appears once with the `jr` delay slot
  filled and once unfilled, which no single toolchain does. They should be
  marked `handwritten: true`: `func_00161328`, `func_001613D8`,
  `func_0018A680`, `func_0018A690`.

### Lanes that were running at handoff

Four Fable slates on the largest functions, one on the 64-bit cluster, one on
register allocation, one on the single-bit flag compare, plus band lanes for
0x14/0x16 and the `.sdata` ownership cluster. Their manifests land in
`work/claude/<lane>.jsonl`; collect and land them with the pipeline above.
Anything not yet in `config/reconstructed.json` is still owed.
