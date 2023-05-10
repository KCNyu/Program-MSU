## Prerequisites

- GCC compiler (or any C compiler)
- Make
- Valgrind (for memory leak checks)
- lcov and gcov (for test coverage report)
- cppcheck (for static code analysis)

## Building

To build the project, run:

```bash
make
```

## Running

To run the project, run:

```bash
./main
```

## Memory Leak Checks

To run memory leak checks, run:

```bash
make memcheck
```

## Test Coverage Report

To generate test coverage report, run:

```bash
make report
```

## Static Code Analysis

To run static code analysis, run:

```bash
make analyze
```
