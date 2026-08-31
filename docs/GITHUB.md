# GitHub maintainer settings

The public repository contains only source, configuration, documentation, and
public-data tooling. The retail-input complete-image gate remains local.

Recommended repository settings:

- default branch: `main`;
- enable issues and squash merging;
- automatically delete merged branches;
- protect `main` after the initial push;
- require the `Metadata and policy audit` check for pull requests;
- require one approving review once a second maintainer is available;
- do not upload build artifacts from private full-image verification.

Suggested topics: `chulip`, `decompilation`, `playstation-2`, `ps2`, `mips`,
`reverse-engineering`.

Before inviting broad public contributions, choose and commit an explicit
license for the repository's original source and tools. That is a maintainer
rights decision and is intentionally not guessed by the bootstrap.
