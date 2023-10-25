#!/bin/sh

NAME=lisy
GROUP=628
EMAIL=shengyu.li@ispras.ru

VALID_CA_NAME=$NAME-$GROUP-ocsp-valid
REVOKED_CA_NAME=$NAME-$GROUP-ocsp-revoked
CHAIN_CA_NAME=$NAME-$GROUP-chain
OCSP_NAME=$NAME-$GROUP-ocsp-resp

ROOT_CA_NAME=$NAME-$GROUP-ca
INTR_CA_NAME=$NAME-$GROUP-intr
OUTPUT_DIR="task1.3"
CA_CONFIG="ca.conf"

VALID_HTML=../nginx/html/valid/index.html
REVOKED_HTML=../nginx/html/revoked/index.html

VALID_CONFIG=../nginx/conf.d/valid.conf
REVOKED_CONFIG=../nginx/conf.d/revoked.conf
OCSP_CONFIG=../nginx/conf.d/ocsp.conf

VALID_SITE_NAME=ocsp.valid.$NAME.ru
REVOKED_SITE_NAME=ocsp.revoked.$NAME.ru
OCSP_SITE_NAME=ocsp.$NAME.ru

VALID_CHAIN=$VALID_CA_NAME-chain
REVOKED_CHAIN=$REVOKED_CA_NAME-chain

mkdir -p $OUTPUT_DIR

cd $OUTPUT_DIR

# Create OCSP responder
openssl ocsp -port 2560 \
    -passin pass:$NAME \
    -index index.txt \
    -CA $CHAIN_CA_NAME.crt \
    -rkey $OCSP_NAME.key \
    -rsigner $OCSP_NAME.crt
