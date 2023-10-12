#!/bin/sh

NAME=lisy
GROUP=628
EMAIL=shengyu.li@ispras.ru

VALID_CA_NAME=$NAME-$GROUP-crl-valid
REVOKED_CA_NAME=$NAME-$GROUP-crl-revoked
CRL_NAME=$NAME-$GROUP
CHAIN_CA_NAME=$NAME-$GROUP-chain

ROOT_CA_NAME=$NAME-$GROUP-ca
INTR_CA_NAME=$NAME-$GROUP-intr
OUTPUT_DIR="task1.2"
CA_CONFIG="ca.conf"

mkdir -p $OUTPUT_DIR
# ------------------------------------------------------------

if [ ! -d "task1.1" ]; then
    bash task1.1.sh
fi

cp task1.1/$ROOT_CA_NAME.key $OUTPUT_DIR/
cp task1.1/$ROOT_CA_NAME.crt $OUTPUT_DIR/

cp task1.1/$INTR_CA_NAME.key $OUTPUT_DIR/
cp task1.1/$INTR_CA_NAME.crt $OUTPUT_DIR/

cd $OUTPUT_DIR

# ------------------------------------------------------------

# Generate Valid CA Key
openssl genrsa -out $VALID_CA_NAME.key 2048

# Create Valid CA Certificate
openssl req \
    -new \
    -key $VALID_CA_NAME.key \
    -out $VALID_CA_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_2/CN=$NAME CRL Valid/emailAddress=$EMAIL"

# Sign Valid Certificate
openssl x509 -req \
    -days 90 \
    -passin pass:$NAME \
    -CA $INTR_CA_NAME.crt \
    -CAkey $INTR_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $VALID_CA_NAME.csr \
    -out $VALID_CA_NAME.crt \
    -extfile <(printf "basicConstraints=CA:FALSE\nkeyUsage=critical,digitalSignature\nextendedKeyUsage=critical,serverAuth,clientAuth\nsubjectAltName=DNS:crl.valid.$NAME.ru\ncrlDistributionPoints=URI:http://crl.$NAME.ru")

echo "VALID CERTIFICATE: "
openssl x509 -text -in $VALID_CA_NAME.crt

echo "VERIFY VALID CERTIFICATE: "
# need to create chain certificate
cat $INTR_CA_NAME.crt $ROOT_CA_NAME.crt > $INTR_CA_NAME-chain.crt
openssl verify -CAfile $INTR_CA_NAME-chain.crt $VALID_CA_NAME.crt
rm $INTR_CA_NAME-chain.crt

# ------------------------------------------------------------

# Generate Revoked CA Key
openssl genrsa -out $REVOKED_CA_NAME.key 2048

# Create Revoked CA Certificate
openssl req \
    -new \
    -key $REVOKED_CA_NAME.key \
    -out $REVOKED_CA_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_2/CN=$NAME CRL Revoked/emailAddress=$EMAIL"

# Sign Revoked Certificate
openssl x509 -req \
    -days 90 \
    -passin pass:$NAME \
    -CA $INTR_CA_NAME.crt \
    -CAkey $INTR_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $REVOKED_CA_NAME.csr \
    -out $REVOKED_CA_NAME.crt \
    -extfile <(printf "basicConstraints=CA:FALSE\nkeyUsage=critical,digitalSignature\nextendedKeyUsage=critical,serverAuth,clientAuth\nsubjectAltName=DNS:crl.revoked.$NAME.ru\ncrlDistributionPoints=URI:http://crl.$NAME.ru")

echo "REVOKED CERTIFICATE: "
openssl x509 -text -in $REVOKED_CA_NAME.crt

echo "VERIFY REVOKED CERTIFICATE: "
# need to create chain certificate
cat $INTR_CA_NAME.crt $ROOT_CA_NAME.crt > $INTR_CA_NAME-chain.crt
openssl verify -CAfile $INTR_CA_NAME-chain.crt $REVOKED_CA_NAME.crt
rm $INTR_CA_NAME-chain.crt

# ------------------------------------------------------------

touch index.txt
echo 1000 > crl_number

# Create configure file
cat > $CA_CONFIG <<EOL
[ ca ]
default_ca = CA_default

[ CA_default ]
database = index.txt
crlnumber = crl_number
crl_extensions = crl_ext
private_key = $INTR_CA_NAME.key
certificate = $INTR_CA_NAME.crt

default_days = 365
default_crl_days = 30
default_md = default
crlDistributionPoints = URI:http://crl.$NAME.ru

[ crl_ext ]
authorityKeyIdentifier = keyid:always
EOL

# Create CRL
openssl ca -passin pass:$NAME -config $CA_CONFIG -revoke $REVOKED_CA_NAME.crt
openssl ca -passin pass:$NAME -gencrl -config $CA_CONFIG -out $CRL_NAME.crl

echo "CREATED CRL LIST AFTER REVOKE:"
openssl crl -text -in $CRL_NAME.crl

cat $ROOT_CA_NAME.crt $INTR_CA_NAME.crt > $CHAIN_CA_NAME.crt

echo "VERIFY CRL LIST:"
openssl verify -crl_check -CRLfile $CRL_NAME.crl -CAfile $CHAIN_CA_NAME.crt $VALID_CA_NAME.crt
openssl verify -crl_check -CRLfile $CRL_NAME.crl -CAfile $CHAIN_CA_NAME.crt $REVOKED_CA_NAME.crt

# Zip files
zip -r $NAME-$GROUP-p1_2.zip $VALID_CA_NAME.key $VALID_CA_NAME.crt $REVOKED_CA_NAME.key $REVOKED_CA_NAME.crt $CRL_NAME.crl $CHAIN_CA_NAME.crt
