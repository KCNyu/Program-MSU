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

# Generate OCSP responder key
openssl genrsa -aes256 -passout pass:$NAME -out $OCSP_NAME.key 4096

# Create OCSP responder Certificate
openssl req \
    -new \
    -passin pass:$NAME \
    -key $OCSP_NAME.key \
    -out $OCSP_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_3/CN=$NAME OCSP Responder/emailAddress=$EMAIL"

# Sign OCSP responder Certificate
openssl x509 -req \
    -days 365 \
    -passin pass:$NAME \
    -CA $INTR_CA_NAME.crt \
    -CAkey $INTR_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $OCSP_NAME.csr \
    -out $OCSP_NAME.crt \
    -extfile <(printf "basicConstraints=CA:FALSE\nkeyUsage=critical,digitalSignature\nextendedKeyUsage=OCSPSigning")

echo "OCSP CERTIFICATE: "
openssl x509 -text -in $OCSP_NAME.crt

echo "OCSP CERTIFICATE: "
# need to create chain certificate
cat $INTR_CA_NAME.crt $ROOT_CA_NAME.crt > $INTR_CA_NAME-chain.crt
openssl verify -CAfile $INTR_CA_NAME-chain.crt $OCSP_NAME.crt
rm $INTR_CA_NAME-chain.crt

# ------------------------------------------------------------

# Generate Valid CA Key
openssl genrsa -out $VALID_CA_NAME.key 2048

# Create Valid CA Certificate
openssl req \
    -new \
    -key $VALID_CA_NAME.key \
    -out $VALID_CA_NAME.csr \
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_3/CN=$NAME OCSP Valid/emailAddress=$EMAIL"

# Sign Valid Certificate
openssl x509 -req \
    -days 90 \
    -passin pass:$NAME \
    -CA $INTR_CA_NAME.crt \
    -CAkey $INTR_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $VALID_CA_NAME.csr \
    -out $VALID_CA_NAME.crt \
    -extfile <(printf "basicConstraints=CA:FALSE\nkeyUsage=critical,digitalSignature\nextendedKeyUsage=critical,serverAuth,clientAuth\nsubjectAltName=DNS:ocsp.valid.$NAME.ru\nauthorityInfoAccess=OCSP;URI:http://ocsp.$NAME.ru")

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
    -subj "/C=RU/ST=Moscow/L=Moscow/O=$NAME/OU=$NAME P1_3/CN=$NAME OCSP Revoked/emailAddress=$EMAIL"

# Sign Revoked Certificate
openssl x509 -req \
    -days 90 \
    -passin pass:$NAME \
    -CA $INTR_CA_NAME.crt \
    -CAkey $INTR_CA_NAME.key \
    -CAcreateserial -CAserial serial \
    -in $REVOKED_CA_NAME.csr \
    -out $REVOKED_CA_NAME.crt \
    -extfile <(printf "basicConstraints=CA:FALSE\nkeyUsage=critical,digitalSignature\nextendedKeyUsage=critical,serverAuth,clientAuth\nsubjectAltName=DNS:ocsp.revoked.$NAME.ru\nauthorityInfoAccess=OCSP;URI:http://ocsp.$NAME.ru")

echo "REVOKED CERTIFICATE: "
openssl x509 -text -in $REVOKED_CA_NAME.crt

echo "VERIFY REVOKED CERTIFICATE: "
# need to create chain certificate
cat $INTR_CA_NAME.crt $ROOT_CA_NAME.crt > $INTR_CA_NAME-chain.crt
openssl verify -CAfile $INTR_CA_NAME-chain.crt $REVOKED_CA_NAME.crt
rm $INTR_CA_NAME-chain.crt

# ------------------------------------------------------------

touch index.txt

# Create configure file
cat > $CA_CONFIG <<EOL
[ ca ]
default_ca = CA_default

[ CA_default ]
database = index.txt
crl_extensions = crl_ext
private_key = $INTR_CA_NAME.key
certificate = $INTR_CA_NAME.crt

default_days = 365
default_crl_days = 30
default_md = default
crlDistributionPoints = URI:http://crl.$NAME.ru
authorityInfoAccess = OCSP;URI:http://ocsp.$NAME.ru

EOL

# Revoke and Valid
openssl ca -passin pass:$NAME -config $CA_CONFIG -revoke $REVOKED_CA_NAME.crt
openssl ca -passin pass:$NAME -config $CA_CONFIG -valid $VALID_CA_NAME.crt

cat $INTR_CA_NAME.crt $ROOT_CA_NAME.crt > $INTR_CA_NAME-chain.crt
cat $OCSP_NAME.crt $INTR_CA_NAME-chain.crt > $CHAIN_CA_NAME.crt

# ------------------------------------------------------------

# Create Valid HTML
cat > $VALID_HTML <<EOL
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Valid Site</title>
</head>
<body style="font-family: Arial, sans-serif; margin: 0; padding: 0; background-color: #f4f4f4;">
    <header style="background-color: #333; color: #fff; text-align: center; padding: 10px;">
        <h1>Valid Site</h1>
    </header>
    <section style="padding: 20px; text-align: center;">
        <p style="font-size: 18px; line-height: 1.6; color: #333;">This is a valid site.</p>
    </section>
</body>
</html>
EOL

cat > $REVOKED_HTML <<EOL
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Revoked Site</title>
</head>
<body style="font-family: Arial, sans-serif; margin: 0; padding: 0; background-color: #f4f4f4;">
    <header style="background-color: #333; color: #fff; text-align: center; padding: 10px;">
        <h1>Revoked Site</h1>
    </header>
    <section style="padding: 20px; text-align: center;">
        <p style="font-size: 18px; line-height: 1.6; color: #333;">This is a revoked site.</p>
    </section>
</body>
</html>
EOL

# Create nginx config
mkdir -p ../nginx/$OUTPUT_DIR/
cp ./* ../nginx/$OUTPUT_DIR/ 

cat > $VALID_CONFIG <<EOL
server {
    listen 80;
    listen [::]:80;
    listen 443 ssl;
    listen [::]:443 ssl;

    server_name $VALID_SITE_NAME www.$VALID_SITE_NAME;

	ssl_certificate $OUTPUT_DIR/$VALID_CA_NAME.crt;
	ssl_certificate_key $OUTPUT_DIR/$VALID_CA_NAME.key;

    location / {
        # root   /usr/share/nginx/html;
        root /etc/nginx/html/valid;
        index  index.html index.htm;
    }
}

EOL

cat > $REVOKED_CONFIG <<EOL
server {
    listen 80;
    listen [::]:80;
    listen 443 ssl;
    listen [::]:443 ssl;

    server_name $REVOKED_SITE_NAME www.$REVOKED_SITE_NAME;

	ssl_certificate $OUTPUT_DIR/$REVOKED_CA_NAME.crt;
	ssl_certificate_key $OUTPUT_DIR/$REVOKED_CA_NAME.key;

    location / {
        # root   /usr/share/nginx/html;
        root /etc/nginx/html/revoked;
        index  index.html index.htm;
    }
}

EOL

cat > $OCSP_CONFIG <<EOL
server {
	listen 80;
    listen [::]:80;

	server_name $OCSP_SITE_NAME www.$OCSP_SITE_NAME;

	location / {
	    proxy_pass http://192.168.31.206:2560;
	}
}

EOL

# ------------------------------------------------------------

# Start nginx and wait for 2 seconds
cd .. && docker-compose up -d && cd $OUTPUT_DIR
sleep 2

# ------------------------------------------------------------

# Create OCSP responder
openssl ocsp -port 2560 \
    -passin pass:$NAME \
    -index index.txt \
    -CA $CHAIN_CA_NAME.crt \
    -rkey $OCSP_NAME.key \
    -rsigner $OCSP_NAME.crt
