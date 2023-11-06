#!/bin/bash

DIR=$1

if [ $DIR == "task2_L1" ]; then
    RESULT="task_N128.json"
elif [ $DIR == "task2_L2" ]; then
    RESULT="task_N256.json"
else
    echo "Wrong directory name"
    exit 1
fi

cd $DIR

TMP="tmp.json"

cat *.out | grep -o -P '{"threads": .*}' | sort -t ':' -k 2 -n > $TMP
cat $TMP

echo "[" > $RESULT

while read line; do
    echo "  $line," >> $RESULT
done < $TMP

# Remove the trailing comma from the last line
sed -i '$ s/,$//' $RESULT
echo "]" >> $RESULT

rm $TMP