#!/bin/bash

USER="edu-cmc-skmodel23-628-06"
HOST="polus.hpc.cs.msu.ru"

scp $USER@$HOST:~/task2/task2_L1/task_N128.json task_N128.json
scp $USER@$HOST:~/task2/task2_L2/task_N256.json task_N256.json
