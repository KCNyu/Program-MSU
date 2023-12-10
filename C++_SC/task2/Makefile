CC := g++

LOCAL_CFLAGS := -Xclang \
		-fopenmp \
		-std=c++11 -O3 \
		-L/opt/homebrew/opt/libomp/lib \
		-I/opt/homebrew/opt/libomp/include \
		-lomp \
		-Iinclude

POLUS_CFLAGS := -fopenmp \
			-std=c++11 \
			-O2 \
			-Iinclude

ifeq ($(FLAG),mpi)
    LOCAL_CFLAGS += -DUSE_MPI
	POLUS_CFLAGS += -DUSE_MPI
	CC := mpic++
endif

MAIN := main

all: compile-local

compile-local:
	$(CC) $(LOCAL_CFLAGS) $(MAIN).cpp -o $(MAIN)
	
compile-polus:
	$(CC) $(POLUS_CFLAGS) $(MAIN).cpp -o $(MAIN)

upload:
	scripts/upload.sh

submit:
	scripts/submit.sh

submit-mpi:
	scripts/submit.sh mpi

show:
	scripts/show.sh task2_L1
	scripts/show.sh task2_L2

show-mpi:
	scripts/show.sh task2_L1 mpi
	scripts/show.sh task2_L2 mpi

clean:
	rm -f $(MAIN) numerical.* analytical.* error.*

.PHONY: all clean
