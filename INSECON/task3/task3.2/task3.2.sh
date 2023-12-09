#!/bin/bash

NAME=lisy
GROUP=628
EMAIL=shengyu.li@ispras.ru

BUMP_NAME=$NAME-$GROUP-bump
ROOT_CA_NAME=$NAME-$GROUP-ca

CHAIN_CA_NAME=$NAME-$GROUP-chain

CA_CONFIG="ca.conf"

cp ../../task1/task1.1/$ROOT_CA_NAME.crt ./
cp ../../task1/task1.1/$ROOT_CA_NAME.key ./


# Generate Bump CA Key
openssl genrsa -out $BUMP_NAME.key 4096

# Create Bump CA Certificate
openssl req \
    -new \
    -key $BUMP_NAME.key \
    -out $BUMP_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P3_2/CN=$NAME Squid CA/emailAddress=$EMAIL"

# Sign Bump Certificate
openssl x509 -req \
    -days 365 \
    -passin pass:$NAME \
    -CA $ROOT_CA_NAME.crt \
    -CAkey $ROOT_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $BUMP_NAME.csr \
    -out $BUMP_NAME.crt \
    -extfile <(printf "basicConstraints=critical,pathlen:0,CA:TRUE\nkeyUsage=critical,digitalSignature,keyCertSign,cRLSign")

echo "BUMP CERTIFICATE: "
openssl x509 -text -in $BUMP_NAME.crt

echo "VERIFY BUMP CERTIFICATE: "
openssl verify -CAfile $ROOT_CA_NAME.crt $BUMP_NAME.crt
cat $BUMP_NAME.crt $ROOT_CA_NAME.crt > $CHAIN_CA_NAME.crt
