CC := clang++
CFLAGS := -Xclang\
		-fopenmp \
		-std=c++11 -O3 \
		-L/opt/homebrew/opt/libomp/lib \
		-I/opt/homebrew/opt/libomp/include \
		-lomp

ifeq ($(FLAG),mpi)
    CFLAGS += -DUSE_MPI
	CC := mpic++
endif

SRC := main.cpp
INC := include
OBJ := $(SRC:.cpp=.o)
DEPS := $(wildcard include/*.hpp)

CFLAGS += -I$(INC)

.PHONY: all clean

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) main
