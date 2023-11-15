#!/bin/bash

NAME=lisy

PORT=3128
HOST=localhost
PROXY=$HOST:$PORT

DEFAULT_CONFIG=squid.conf.default
ACL_CONFIG=acl.conf

cp $DEFAULT_CONFIG $ACL_CONFIG
cat >>$ACL_CONFIG <<EOL

acl identme dstdomain .ident.me

http_access deny identme

EOL

squid -f $ACL_CONFIG

sleep 3

curl ident.me -x $PROXY -A "$NAME" -v

echo ""
echo "====================================="
echo ""

curl httpbin.org/get?bio=$NAME -x $PROXY -v

squid -k shutdown
