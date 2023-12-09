#!/bin/bash

NAME=lisy
GROUP=628

PORT=3128
HOST=localhost
PROXY=$HOST:$PORT

DEFAULT_CONFIG=squid.conf.default
BUMP_CONFIG=$NAME-$GROUP-bump.conf

CUR_DIR=`pwd`
CHAIN_CA_NAME=$NAME-$GROUP-chain
BUMP_NAME=$NAME-$GROUP-bump

cp $DEFAULT_CONFIG $BUMP_CONFIG
cat >>$BUMP_CONFIG <<EOL

http_port $PORT ssl-bump cert=$CUR_DIR/$CHAIN_CA_NAME.crt key=$CUR_DIR/$BUMP_NAME.key generate-host-certificates=on

sslcrtd_program /opt/homebrew/opt/squid/libexec/security_file_certgen -s /opt/homebrew/opt/squid/ssl_db -M 4MB

acl httpbin_ip ssl::server_name httpbin.org

http_access allow httpbin_ip

acl sni_match at_step SslBump1
ssl_bump peek sni_match
ssl_bump bump httpbin_ip

EOL

squid -f $BUMP_CONFIG

sleep 3

rm $NAME-$GROUP-bump.log

export SSLKEYLOGFILE=$NAME-$GROUP-bump.log

curl https://httpbin.org/get?bio=$NAME -x $PROXY -k -v

squid -k shutdown