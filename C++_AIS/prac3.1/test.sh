#/bin/bash

# dowload test file
wget https://caiscourse.ru/assets/assignment_variants/30102018.zip
unzip 30102018.zip
rm -rf 30102018.zip CCA3Trace

# run tests
python3.9 main.py PublicTests/01-linear.json TestResults/01-linear.dot
python3.9 main.py PublicTests/02-bubblesort.json TestResults/02-bubblesort.dot
python3.9 main.py PublicTests/03-primes.json TestResults/03-primes.dot
python3.9 main.py PublicTests/04-indirect.json TestResults/04-indirect.dot
python3.9 main.py PublicTests/05-switch.json TestResults/05-switch.dot

# check results
cd TestResults
dot -Tpng 01-linear.dot -o 01-linear.png
dot -Tpng 02-bubblesort.dot -o 02-bubblesort.png
dot -Tpng 03-primes.dot -o 03-primes.png
dot -Tpng 04-indirect.dot -o 04-indirect.png
dot -Tpng 05-switch.dot -o 05-switch.png