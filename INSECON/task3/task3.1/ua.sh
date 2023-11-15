#!/bin/bash

NAME=lisy

PORT=3128
HOST=localhost
PROXY=$HOST:$PORT

DEFAULT_CONFIG=squid.conf.default
UA_CONFIG=ua.conf

cp $DEFAULT_CONFIG $UA_CONFIG
cat >>$UA_CONFIG <<EOL

acl httpbin_ip dstdomain httpbin.org
request_header_access User-Agent deny httpbin_ip
request_header_replace User-Agent $NAME

EOL

squid -f $UA_CONFIG

sleep 3

curl httpbin.org/ip -x $PROXY -v

squid -k shutdown
