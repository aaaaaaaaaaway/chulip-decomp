# newlib source snapshot

This directory contains the minimal source and header subset needed to build
Chulip's `dtoa.c` and allocator translation units.

- Upstream: `https://sourceware.org/git/newlib-cygwin.git`
- Commit: `b0ba0ac21747fef4f150f2632aedf0f59e0ae03a`
- Date: 2000-02-21

`stdlib/dtoa.c` contains its original David M. Gay and AT&T permission notice.
The headers retain their upstream notices. The small files in `compat/` state
the PlayStation 2 ABI properties needed by the historical standalone compiler.
The disabled `HAVE_USR_INCLUDE_MALLOC_H` branch uses portable `<malloc.h>` in
place of upstream's absolute host path; that branch is not compiled for Chulip.
