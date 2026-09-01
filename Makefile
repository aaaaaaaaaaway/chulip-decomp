PYTHON ?= python3
VENV_PYTHON := .venv/bin/python
FUNCTION ?=
PROFILE ?= ee-gcc2.95.3-136-O2-G8
CANDIDATES ?=

.PHONY: setup split baseline verify match merge progress boundaries boundary-verify audit public-check

setup:
	$(PYTHON) tools/bootstrap.py

split:
	$(PYTHON) tools/gen_splat_config.py --check
	$(VENV_PYTHON) configure.py --split

baseline:
	$(VENV_PYTHON) configure.py --baseline-split
	$(PYTHON) tools/build_baseline.py

verify: split
	$(PYTHON) tools/build.py

match:
	@test -n "$(FUNCTION)" || (echo "usage: make match FUNCTION=func_00101490 [PROFILE=...]" && exit 2)
	$(PYTHON) tools/match.py "$(FUNCTION)" --profile "$(PROFILE)"

merge:
	@test -n "$(CANDIDATES)" || (echo "usage: make merge CANDIDATES=work/candidates.jsonl" && exit 2)
	$(PYTHON) tools/merge_candidates.py "$(CANDIDATES)"

progress:
	$(PYTHON) tools/progress.py --write-readme

boundaries:
	$(PYTHON) tools/object_boundary_scan.py

boundary-verify:
	$(PYTHON) tools/object_boundary_scan.py --verify-matrices

audit:
	$(PYTHON) tools/repo_audit.py

public-check:
	$(PYTHON) -m compileall -q configure.py tools
	$(PYTHON) tools/gen_splat_config.py --check
	$(PYTHON) tools/progress.py --check-readme
	$(PYTHON) tools/repo_audit.py
