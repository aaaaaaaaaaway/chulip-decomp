# Preserved lane findings

`work/` is gitignored, so everything a lane learned lived on one machine only.
This directory is the tracked copy.

- `*-NOTES.md`, `*-RULES.md`, `*-AUDIT.md` — what each lane proved, what it
  ruled out, and the translation-unit groupings it identified. The rules that
  survived review are curated into `docs/knowledge-book.md`; these are the raw
  working notes, including the negative results, which are what stop a later
  lane repeating a dead end.
- `../nearmiss-sources/<lane>-<function>.c` — 208 candidate sources that do not
  yet match. Most are one or two instructions from exact. They are the largest
  reserve of nearly-finished work in the project; `docs/nearmiss.jsonl` records
  how close each one is and under which configuration.

A candidate here is not a failure. One survey of candidates parked like these
recovered 181 functions, sixty of which needed nothing but being tried again
after a toolchain fact changed.
