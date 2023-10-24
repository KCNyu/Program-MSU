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

VALID_SITE_NAME=ocsp.valid.$NAME.ru
REVOKED_SITE_NAME=ocsp.revoked.$NAME.ru
OCSP_SITE_NAME=ocsp.$NAME.ru

cd $OUTPUT_DIR

openssl ocsp \
	-url http://$OCSP_SITE_NAME:2560 \
	-CAfile $CHAIN_CA_NAME.crt \
	-issuer $INTR_CA_NAME.crt \
	-cert $REVOKED_CA_NAME.crt

openssl ocsp \
	-url http://$OCSP_SITE_NAME:2560 \
	-CAfile $CHAIN_CA_NAME.crt \
	-issuer $INTR_CA_NAME.crt \
	-cert $VALID_CA_NAME.crt

# Zip files
zip -r $NAME-$GROUP-p1_3.zip \
	$VALID_CA_NAME.key $VALID_CA_NAME.crt $VALID_CA_NAME.log $VALID_CA_NAME.pcapng \
	$REVOKED_CA_NAME.key $REVOKED_CA_NAME.crt $REVOKED_CA_NAME.log $REVOKED_CA_NAME.pcapng \
	$OCSP_NAME.key $OCSP_NAME.crt \
	$CHAIN_CA_NAME.crt
