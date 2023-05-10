CC=gcc
CFLAGS=-I. -fprofile-arcs -ftest-coverage -g

_OBJ = map.o main.o
OBJ = $(patsubst %,%,$(_OBJ))

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

default: main

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

report: main
	./main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

check: main
	valgrind --leak-check=full ./main

.PHONY: clean report

clean:
	rm -rf *.o *.gcov *.gcno *.info *.gcda main out/
