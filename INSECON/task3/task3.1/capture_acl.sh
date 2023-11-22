#!/bin/bash

NAME=lisy
GROUP=628

sudo tcpdump \
    -i any \
    -w $NAME-$GROUP-acl.pcapng \
    -n tcp \
