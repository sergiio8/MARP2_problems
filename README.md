# MARP 2 — Algorithmic Problem-Solving Coursework

This repository is an academic collection of solutions for **MARP 2** (the
course name appears in the source metadata). It contains independent,
judge-style programming exercises implemented in C++. It should be read as a
coursework and algorithm-practice archive, not as a production application,
library, or unified software project.

## What is included

The repository currently contains:

- 32 C++ source files (`*.cpp`), including numbered exercises such as
  `23.cpp`–`30.cpp` and judge-labelled files such as `juez1.cpp`–`juez22.cpp`
  and `juez28.cpp`.
- Pre-built, extensionless executable artifacts with names matching several
  source files (for example, `juez1` and `juez21`).
- A small number of working or historical variants, including
  `juez1b.cpp` and `juez21guardado.cpp`.

The filenames do not include the original problem statements, so the
repository does not provide a definitive problem title or input specification
for every exercise.

## Algorithms and techniques

The source code demonstrates common techniques from an algorithms and
optimization curriculum:

| Area | Verified examples |
| --- | --- |
| Dynamic programming | Coin-change variants, bounded/unbounded selection, path and interval recurrences, and matrix-based subproblems |
| Optimization | Knapsack-style maximization and minimum-cost formulations |
| Branch and bound | Priority-queue search with feasibility checks and upper bounds in `juez21.cpp` and related variants |
| Backtracking / state-space search | Constraint-based seating, allocation, and assignment problems |
| String and sequence algorithms | Longest-common-subsequence-style reconstruction in `juez10.cpp`, string transformations, and interval recurrences |
| Graph and matrix methods | Matrix cost recurrences, shortest-path-style transitions, and adjacency/state tables |
| Standard data structures | `vector`, stacks, queues, priority queues, hash maps, and custom matrix wrappers |

These descriptions identify implementation techniques visible in the source;
they are not substitutes for the original exercise statements.

## Source organisation

The current layout is intentionally preserved as an archive of submitted or
working solutions:

```text
.
├── *.cpp                 # Independent C++ exercise solutions
├── juez*                 # Extensionless compiled artifacts for some solutions
├── 23.cpp ... 30.cpp     # Additional numbered exercises
└── temporary/variant files
```

There is no build system, test harness, or shared library. Most programs have
their own `main()` and read from standard input using a repeated
`resuelveCaso()` pattern or a fixed number of cases. Exact input and output
formats must therefore be obtained from the corresponding assignment or online
judge; they cannot be reconstructed reliably from filenames alone.

## Building and running a solution

Because each source file is a separate program, compile the exercise you want
to run individually. A C++17 compiler is a reasonable starting point, but the
repository does not declare a required compiler version or dependency
configuration.

```bash
g++ -std=c++17 -O2 juez10.cpp -o juez10
./juez10 < input.txt
```

The same pattern applies to another source file:

```bash
g++ -std=c++17 -O2 23.cpp -o exercise-23
./exercise-23 < input.txt
```

The input files in these examples are illustrative only; no sample datasets
are included in the repository.

## Limitations and maintenance notes

- Problem statements, constraints, provenance, and correctness explanations
  are not included.
- There is no repository-wide automated test suite or continuous-integration
  configuration.
- Compiled binaries are stored alongside source files, which makes the root
  directory harder to navigate and can make artifacts platform-dependent.
- Similar and saved variants are present but are not documented as canonical
  or historical solutions.
- Naming is based on local judge/course numbering rather than descriptive
  problem names.
- The code is educational material and should not be treated as production
  quality without additional review, documentation, portability checks, and
  tests.

## Suggested future organisation

If this archive is expanded for public or long-term use, the most useful next
steps would be:

1. Move source files into a `solutions/` directory and keep build outputs out
   of version control.
2. Add a problem index mapping each filename to its original statement,
   category, and complexity.
3. Preserve variants in an explicitly named archive directory or document why
   each variant exists.
4. Add representative sample inputs and outputs, plus a small compile/test
   workflow.

## Academic context

The repository contains coursework material and should be used in accordance
with the relevant course and institution policies. Where attribution appears
in source files, it should be retained and supplemented with the appropriate
course or author information before redistribution.
