#!/bin/bash

DIR="../image"

python3 graph.py task_N128.json $DIR/task_N128.png
python3 graph.py task_N256.json $DIR/task_N256.png

python3 graph_3d.py  ../numerical.csv $DIR/numerical.png
python3 graph_3d.py  ../analytical.csv $DIR/analytical.png
python3 graph_3d.py  ../error.csv $DIR/error.png
