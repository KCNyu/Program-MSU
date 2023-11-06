#!/bin/bash

DIR=$1

cd $DIR
cat * | grep -o -P '{"threads": .*}' | sort -t ':' -k 2 -n
