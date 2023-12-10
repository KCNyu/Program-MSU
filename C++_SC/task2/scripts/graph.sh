#!/bin/bash

DIR="../image"

PROG="graph.py"

if [ $1 == "mpi" ]; then
    python3 $PROG task_N128.json $DIR/task_N128.png mpi
    python3 $PROG task_N256.json $DIR/task_N256.png mpi
else
    python3 $PROG task_N128.json $DIR/task_N128.png
    python3 $PROG task_N256.json $DIR/task_N256.png
    python3 graph_3d.py ../numerical.csv $DIR/numerical.png
    python3 graph_3d.py ../analytical.csv $DIR/analytical.png
    python3 graph_3d.py ../error.csv $DIR/error.png
fi
