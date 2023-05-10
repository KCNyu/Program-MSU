CC=gcc
CFLAGS=-I.

_OBJ = map.o main.o
OBJ = $(patsubst %,%,$(_OBJ))

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

default: main

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o main
