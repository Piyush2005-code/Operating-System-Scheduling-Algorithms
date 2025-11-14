
CPU Scheduling Project

Overview
--------
This repository contains a small CPU scheduling project implementing multiple scheduling algorithms (stubs and simple implementations). It is arranged to be easy to build locally, run tests, and integrate into CI or a reproducible container.

Goals of this repo:
- Clear, well-documented code for teaching and experiments.
- Simple CLI and a tiny web frontend (under `web/`) for quick manual testing.
- Reproducible runs using scripts and an included `Dockerfile`.

Structure
---------
- `main.cpp` - CLI driver. Accepts an input file as a positional argument or `--all-tests` to iterate `testcases/`.
- `*.cpp`, `*.h` - scheduler implementations and helpers.
- `testcases/` - example input files for common scenarios.
- `Dockerfile` - reproducible build/run environment.

Quickstart (native)
-------------------
1. Build:

	make

2. Run one testcase interactively:

	./scheduler {path of input.txt}


