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

```bash
==10725== 
==10725== HEAP SUMMARY:
==10725==     in use at exit: 0 bytes in 0 blocks
==10725==   total heap usage: 6 allocs, 6 frees, 2,119 bytes allocated
==10725== 
==10725== All heap blocks were freed -- no leaks are possible
==10725== 
==10725== For lists of detected and suppressed errors, rerun with: -s
==10725== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Test Coverage Report

To generate test coverage report, run:

```bash
make report
```

```bash
Processing file TASK4/main.c
Processing file TASK4/map.c
Writing directory view page.
Overall coverage rate:
  lines......: 95.0% (95 of 100 lines)
  functions..: 100.0% (7 of 7 functions)
```

## Static Code Analysis

To run static code analysis, run:

```bash
make analyze
```

```bash
gcc -c -o map.o map.c -I. -fprofile-arcs -ftest-coverage -g
In file included from map.c:3:
In file included from ./map.h:4:
./maptypes.h:15:28: warning: unknown attribute 'noembed' ignored [-Wunknown-attributes]
    Key key __attribute__((noembed));
                           ^~~~~~~
1 warning generated.
gcc -c -o main.o main.c -I. -fprofile-arcs -ftest-coverage -g
In file included from main.c:1:
In file included from ./map.h:4:
./maptypes.h:15:28: warning: unknown attribute 'noembed' ignored [-Wunknown-attributes]
    Key key __attribute__((noembed));
                           ^~~~~~~
1 warning generated.
gcc -o main map.o main.o -I. -fprofile-arcs -ftest-coverage -g
cppcheck --enable=all --suppress=missingIncludeSystem .
Checking main.c ...
1/2 files checked 68% done
Checking map.c ...
map.c:33:31: style: Parameter 'key' can be declared as pointer to const [constParameter]
int addElement(Map *map, Key *key, Value *value)
                              ^
map.c:33:43: style: Parameter 'value' can be declared as pointer to const [constParameter]
int addElement(Map *map, Key *key, Value *value)
                                          ^
2/2 files checked 100% done
```