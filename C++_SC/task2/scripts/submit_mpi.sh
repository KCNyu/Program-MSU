#!/bin/bash

OUTPUT_DIR="task2_L1"
rm -rf $OUTPUT_DIR
mkdir $OUTPUT_DIR

if [ "$1" = "mpi" ]; then

    # Lx = Ly = Lz = 1 or π
    # N = 128
    for p in 1 2 4; do
        for t in 1 2 4 8; do
            mpisubmit.pl -p $p \
                -W 00:10 \
                --stdout $OUTPUT_DIR/task2_thread${t}_mpi${p}.out \
                --stderr $OUTPUT_DIR/task2_thread${t}_mpi${p}.err \
                -t $t \
                ./main -- -L 1.0

            mpisubmit.pl -p $p \
                -W 00:10 \
                --stdout $OUTPUT_DIR/task2_thread${t}_mpi${p}_pi.out \
                --stderr $OUTPUT_DIR/task2_thread${t}_mpi${p}_pi.err \
                -t $t \
                ./main
        done
    done

    OUTPUT_DIR="task2_L2"
    rm -rf $OUTPUT_DIR
    mkdir $OUTPUT_DIR

    # Lx = Ly = Lz = 1 or π
    # N = 256
    for p in 1 2 4; do
        for t in 1 2 4 8; do
            mpisubmit.pl -p $p \
                -W 00:10 \
                --stdout $OUTPUT_DIR/task2_thread${t}_mpi${p}.out \
                --stderr $OUTPUT_DIR/task2_thread${t}_mpi${p}.err \
                -t $t \
                ./main -- -L 1.0 -N 256

            mpisubmit.pl -p $p \
                -W 00:10 \
                --stdout $OUTPUT_DIR/task2_thread${t}_mpi${p}_pi.out \
                --stderr $OUTPUT_DIR/task2_thread${t}_mpi${p}_pi.err \
                -t $t \
                ./main -- -N 256
        done
    done

else
    # Lx = Ly = Lz = 1 or π
    # N = 128
    for t in 1 2 4 8 16; do
        bsub -n 1 \
            -q normal \
            -W 00:10 \
            -o $OUTPUT_DIR/task2_thread$t.out \
            -e $OUTPUT_DIR/task2_thread$t.err \
            -R "affinity[core(10,same=socket,exclusive=(socket,alljobs)):membind=localonly:distribute=pack(socket=1)]" \
            OMP_NUM_THREADS=$t \
            ./main -L 1.0

        bsub -n 1 \
            -q normal \
            -W 00:10 \
            -o $OUTPUT_DIR/task2_thread${t}_pi.out \
            -e $OUTPUT_DIR/task2_thread${t}_pi.err \
            -R "affinity[core(10,same=socket,exclusive=(socket,alljobs)):membind=localonly:distribute=pack(socket=1)]" \
            OMP_NUM_THREADS=$t \
            ./main
    done

    OUTPUT_DIR="task2_L2"
    rm -rf $OUTPUT_DIR
    mkdir $OUTPUT_DIR

    # Lx = Ly = Lz = 1 or π
    # N = 256
    for t in 1 4 8 16 32; do
        bsub -n 1 \
            -q normal \
            -W 00:10 \
            -o $OUTPUT_DIR/task2_thread$t.out \
            -e $OUTPUT_DIR/task2_thread$t.err \
            -R "affinity[core(10,same=socket,exclusive=(socket,alljobs)):membind=localonly:distribute=pack(socket=1)]" \
            OMP_NUM_THREADS=$t \
            ./main -L 1.0 -N 256

        bsub -n 1 \
            -q normal \
            -W 00:10 \
            -o $OUTPUT_DIR/task2_thread${t}_pi.out \
            -e $OUTPUT_DIR/task2_thread${t}_pi.err \
            -R "affinity[core(10,same=socket,exclusive=(socket,alljobs)):membind=localonly:distribute=pack(socket=1)]" \
            OMP_NUM_THREADS=$t \
            ./main -N 256
    done
fi
