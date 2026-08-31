PYTHON ?= python3
VENV_PYTHON := .venv/bin/python
FUNCTION ?=
PROFILE ?= ee-gcc2.95.3-136-O2-G8

.PHONY: setup split baseline verify match progress audit public-check

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

progress:
	$(PYTHON) tools/progress.py --write-readme

audit:
	$(PYTHON) tools/repo_audit.py

public-check:
	$(PYTHON) -m compileall -q configure.py tools
	$(PYTHON) tools/gen_splat_config.py --check
	$(PYTHON) tools/progress.py --check-readme
	$(PYTHON) tools/repo_audit.py
