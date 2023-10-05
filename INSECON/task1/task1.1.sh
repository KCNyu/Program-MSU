#!/bin/sh

NAME=li
GROUP=628
EMAIL=shengyu.li@ispras.ru

ROOT_CA_NAME=$NAME-$GROUP-ca
INTR_CA_NAME=$NAME-$GROUP-intr
BASIC_CA_NAME=$NAME-$GROUP-basic
OUTPUT_DIR="task1.1"

mkdir -p $OUTPUT_DIR
cd $OUTPUT_DIR

# ------------------------------------------------------------

# Generate Root CA Key
openssl genrsa -aes256 -passout pass:$NAME -out $ROOT_CA_NAME.key 4096

# Create Root CA Certificate
openssl req -x509 \
    -passin pass:$NAME \
    -new \
    -days 1095 \
    -key $ROOT_CA_NAME.key \
    -out $ROOT_CA_NAME.crt \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_1/CN=$NAME CA/emailAddress=$EMAIL" \
    -addext "keyUsage = critical, digitalSignature, keyCertSign, cRLSign"

echo "ROOT CERTIFICATE: "
openssl x509 -text -in $ROOT_CA_NAME.crt

echo "VERIFY ROOT CERTIFICATE: "
openssl verify -CAfile $ROOT_CA_NAME.crt $ROOT_CA_NAME.crt

# ------------------------------------------------------------

# Generate Intermediate CA Key
openssl genrsa -aes256 -passout pass:$NAME -out $INTR_CA_NAME.key 4096

# Create Intermediate CA Certificate
openssl req \
    -passin pass:$NAME \
    -new \
    -key $INTR_CA_NAME.key \
    -out $INTR_CA_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/CN=$NAME Intermediate CA/OU=$NAME P1_1/emailAddress=$EMAIL"

# Sign Intermediate Certificate
openssl x509 -req \
    -passin pass:$NAME \
    -days 365 \
    -CA $ROOT_CA_NAME.crt \
    -CAkey $ROOT_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $INTR_CA_NAME.csr \
    -out $INTR_CA_NAME.crt \
    -extfile <(printf "basicConstraints=critical,CA:TRUE,pathlen:0\nkeyUsage=critical,digitalSignature,keyCertSign,cRLSign")

echo "INTERMEDIATE CERTIFICATE: "
openssl x509 -text -in $INTR_CA_NAME.crt

echo "VERIFY INTERMEDIATE CERTIFICATE: "
openssl verify -CAfile $ROOT_CA_NAME.crt $INTR_CA_NAME.crt

# ------------------------------------------------------------

# Generate Basic CA Key
openssl genrsa -out $BASIC_CA_NAME.key 4096

# Create Basic CA Certificate
openssl req \
    -new \
    -key $BASIC_CA_NAME.key \
    -out $BASIC_CA_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_1/CN=$NAME Basic/emailAddress=$EMAIL"

# Sign Basic Certificate
openssl x509 -req \
    -days 90 \
    -passin pass:$NAME \
    -CA $INTR_CA_NAME.crt \
    -CAkey $INTR_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $BASIC_CA_NAME.csr \
    -out $BASIC_CA_NAME.crt \
    -extfile <(printf "basicConstraints=CA:FALSE\nkeyUsage=critical,digitalSignature\nextendedKeyUsage=critical,serverAuth,clientAuth\nsubjectAltName=DNS:basic.$NAME.ru,DNS:basic.$NAME.com")

echo "BASIC CERTIFICATE: "
openssl x509 -text -in $BASIC_CA_NAME.crt

echo "VERIFY BASIC CERTIFICATE: "
# need to create chain certificate
cat $INTR_CA_NAME.crt $ROOT_CA_NAME.crt > $INTR_CA_NAME-chain.crt
openssl verify -CAfile $INTR_CA_NAME-chain.crt $BASIC_CA_NAME.crt
rm $INTR_CA_NAME-chain.crt

# ------------------------------------------------------------
# Zip files
zip -r $NAME-$GROUP-p1_1.zip $ROOT_CA_NAME.key $ROOT_CA_NAME.crt $INTR_CA_NAME.key $INTR_CA_NAME.crt $BASIC_CA_NAME.key $BASIC_CA_NAME.crt
