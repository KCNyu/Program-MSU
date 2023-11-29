#!/bin/bash

NAME=lisy
GROUP=628

PORT=3128
HOST=localhost
PROXY=$HOST:$PORT

DEFAULT_CONFIG=squid.conf.default
ACL_CONFIG=$NAME-$GROUP-acl.conf

CUR_DIR=$(pwd)
CHAIN_CA_NAME=$NAME-$GROUP-chain
BUMP_NAME=$NAME-$GROUP-bump

cp $DEFAULT_CONFIG $ACL_CONFIG
cat >>$ACL_CONFIG <<EOL

http_port $PORT ssl-bump cert=$CUR_DIR/$CHAIN_CA_NAME.crt key=$CUR_DIR/$BUMP_NAME.key generate-host-certificates=on

sslcrtd_program /opt/homebrew/opt/squid/libexec/security_file_certgen -s /opt/homebrew/opt/squid/ssl_db -M 4MB

acl identme ssl::server_name ident.me
acl httpbin_ip ssl::server_name httpbin.org

http_access allow identme 
http_access allow httpbin_ip

acl sni_match at_step SslBump1
ssl_bump peek sni_match
ssl_bump splice httpbin_ip
ssl_bump terminate all

EOL

squid -f $ACL_CONFIG

sleep 3

rm $NAME-$GROUP-acl.log

export SSLKEYLOGFILE=$NAME-$GROUP-acl.log

curl https://ident.me -x $PROXY -A "$NAME" -k -v

echo ""
echo "====================================="
echo ""

curl https://httpbin.org/get?bio=$NAME -x $PROXY -k -v

squid -k shutdown
