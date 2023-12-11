#!/bin/bash

DIR="../image"

PROG="graph.py"

if [ $1 == "mpi" ]; then
    python3 $PROG task_N128.json $DIR/task_N128_mpi_1.png mpi 1
    python3 $PROG task_N128.json $DIR/task_N128_mpi_2.png mpi 2
    python3 $PROG task_N128.json $DIR/task_N128_mpi_4.png mpi 4

    python3 $PROG task_N256.json $DIR/task_N256_mpi_1.png mpi 1
    python3 $PROG task_N256.json $DIR/task_N256_mpi_2.png mpi 2
    python3 $PROG task_N256.json $DIR/task_N256_mpi_4.png mpi 4

else
    python3 $PROG task_N128.json $DIR/task_N128.png
    python3 $PROG task_N256.json $DIR/task_N256.png
    python3 graph_3d.py ../numerical.csv $DIR/numerical.png
    python3 graph_3d.py ../analytical.csv $DIR/analytical.png
    python3 graph_3d.py ../error.csv $DIR/error.png
fi
