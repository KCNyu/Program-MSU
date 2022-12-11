#/bin/bash

# dowload test file
wget https://caiscourse.ru/assets/assignment_variants/30202018.zip
unzip 30202018.zip
rm -rf 30202018.zip CCA3Trace
mkdir TestResults

# run tests
python main.py PublicTests/01-copy.json PublicTests/01-copy.tests.json TestResults/01-copy.out.json
python main.py PublicTests/02-calculate.json PublicTests/02-calculate.tests.json TestResults/02-calculate.out.json
python main.py PublicTests/03-password.json PublicTests/03-password.tests.json TestResults/03-password.out.json
python main.py PublicTests/04-functions.json PublicTests/04-functions.tests.json TestResults/04-functions.out.json
python main.py PublicTests/05-encrypt.json PublicTests/05-encrypt.tests.json TestResults/05-encrypt.out.json