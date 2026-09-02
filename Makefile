PYTHON ?= python3
VENV_PYTHON := .venv/bin/python
FUNCTION ?=
PROFILE ?= ee-gcc2.95.3-136-O2-G8
CANDIDATES ?=
CANDIDATE_ELF ?= build/current/chulip.us.elf
OWNER ?= local

.PHONY: setup install-hooks split baseline verify match merge reverify-ledger progress boundaries boundary-verify audit elf-report campaign-plan campaign-packet campaign-status campaign-harvest campaign-promote test public-check

setup:
	$(PYTHON) tools/bootstrap.py

install-hooks:
	ln -sf ../../tools/hooks/pre-commit .git/hooks/pre-commit
	@echo "installed .git/hooks/pre-commit"

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

reverify-ledger:
	$(PYTHON) tools/reverify_ledger.py

progress:
	$(PYTHON) tools/progress.py --write-readme

boundaries:
	$(PYTHON) tools/object_boundary_scan.py

boundary-verify:
	$(PYTHON) tools/object_boundary_scan.py --verify-matrices

audit:
	$(PYTHON) tools/repo_audit.py

elf-report:
	$(PYTHON) tools/elf_completeness.py --candidate "$(CANDIDATE_ELF)"

campaign-plan:
	$(PYTHON) tools/campaign.py plan

campaign-packet:
	@test -n "$(FUNCTION)" || (echo "usage: make campaign-packet FUNCTION=func_00101490 OWNER=name" && exit 2)
	$(PYTHON) tools/campaign.py packet "$(FUNCTION)" --owner "$(OWNER)"

campaign-status:
	$(PYTHON) tools/campaign.py status

campaign-harvest:
	$(PYTHON) tools/campaign.py harvest $(CANDIDATES)

campaign-promote:
	@test -n "$(FUNCTION)" || (echo "usage: make campaign-promote FUNCTION=func_00101490" && exit 2)
	$(PYTHON) tools/campaign.py promote "$(FUNCTION)"

test:
	$(PYTHON) -m unittest discover -s tests -p 'test_*.py'

public-check: test
	$(PYTHON) -m compileall -q configure.py tools
	$(PYTHON) tools/gen_splat_config.py --check
	$(PYTHON) tools/progress.py --check-readme
	$(PYTHON) tools/progress.py --check-status
	$(PYTHON) tools/scope_scan.py --check-scope
	$(PYTHON) tools/repo_audit.py
