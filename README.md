# MARP2 problems

Standalone C++ solutions and experiments from the **MARP 2** algorithm coursework. The repository is best understood as an academic problem collection rather than a reusable library or a single application: each source file contains its own `main` function and reads the input format expected by that exercise.

## What is covered

The implementations provide examples of:

- dynamic programming over sequences, grids, matrices, and bounded selections;
- backtracking and branch-and-bound search;
- priority queues and heap-based search;
- matrix and graph-like relationship problems;
- string processing and sequence comparison; and
- sorting, reconstruction of solutions, and related contest-programming techniques.

These topics are identified from the algorithms and data structures present in the checked-in source. The repository does not include the original exercise statements, so it does not claim a complete mapping from filenames to problem names.

## Repository layout

| Path pattern | Contents |
| --- | --- |
| `coursework/MARP2/src/judge/*.cpp` | Individual judge/course exercises, including saved variants |
| `coursework/MARP2/src/numbered/*.cpp` | Additional numbered exercises; `28.cpp` is absent from the current checkout |
| `coursework/MARP2/artifacts/prebuilt-macos/*` | Prebuilt executables retained as coursework artifacts |
| `archive/24.cp`, `archive/tempCodeRunnerFile.cpp` | Preserved scratch/incomplete artifacts; not part of a supported build |

The prebuilt executables are Mach-O binaries for Apple ARM64 and are not portable across platforms. They are retained as generated artifacts, not source files or build inputs. The C++ source is the authoritative, inspectable material.

## Prerequisites

- A C++ compiler with standard library support, such as `g++` or `clang++`.
- C++17 is a conservative standard for compiling the collection. Individual files may work with an older standard, but no repository-wide minimum has been declared.
- A shell for the command examples below.

No package manager, external library, or repository-wide build system is required.

## Build and run one exercise

Compile a source file into a local build directory:

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra coursework/MARP2/src/judge/juez15.cpp -o build/juez15
```

Run it with the input expected by that exercise:

```sh
./build/juez15 < input.txt
```

The programs are independent and do not share a common command-line interface. Because the exercise statements and sample inputs are not stored here, consult the relevant course/judge statement for the required input and output format.

To try another solution, repeat the same pattern with its source filename, for example:

```sh
g++ -std=c++17 -Wall -Wextra coursework/MARP2/src/judge/juez21.cpp -o build/juez21
./build/juez21 < input.txt
```

## Scope and limitations

This is coursework and a personal problem-solving archive, not a maintained production package. It currently has:

- no shared build configuration or automated test suite;
- no bundled problem statements, input fixtures, or correctness proofs;
- inconsistent naming and organization inherited from the original exercises; and
- a small number of scratch, duplicate, and prebuilt platform-specific files.

Compilation status can vary by source. For example, most standalone solutions compile with the command above, while `coursework/MARP2/src/judge/juez16.cpp` currently contains a type-mismatch error. The incomplete scratch file is preserved under `archive/` and is not part of the supported source collection. These limitations are documented rather than hidden; solution code and historical artifacts are preserved as committed.

## Contributing

Keep new exercises self-contained, document the source and compiler assumptions when they matter, and avoid replacing the original solutions with generated binaries. If a problem statement is added, link it to the corresponding source file without assuming that filenames alone identify the exercise.
