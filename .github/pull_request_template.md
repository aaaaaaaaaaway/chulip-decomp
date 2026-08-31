## Summary

Describe the focused change and the address range or subsystem it affects.

## Match evidence

- Functions/addresses:
- Compiler profile:
- Isolated verifier result:
- Complete-image result:
- Translation-unit provenance:

Use `N/A` for documentation or tooling-only changes.

## Checklist

- [ ] I did not include ROMs, extracted files, generated retail assembly, SDK material, compiler binaries, or target-byte dumps.
- [ ] Readable source expresses behavior; it does not encode the target instructions or bytes.
- [ ] `python3 tools/repo_audit.py` passes.
- [ ] I updated `config/reconstructed.json` for exact source candidates.
- [ ] Promoted functions pass isolated and complete-image checks and are recorded in `config/matched.json`.
- [ ] I ran `python3 tools/progress.py --write-readme` after changing promoted progress.
- [ ] I recorded durable findings in the knowledge ledger where applicable.
