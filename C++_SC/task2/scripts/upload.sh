#!/bin/bash

USER="edu-cmc-skmodel23-628-06"
HOST="polus.hpc.cs.msu.ru"

cd ..

rm task2.zip

zip -r task2.zip task2/include task2/main.cpp task2/Makefile task2/scripts

scp task2.zip $USER@$HOST:~
