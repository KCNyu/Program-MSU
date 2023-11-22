#!/bin/bash

NAME=lisy
GROUP=628

sudo tcpdump \
    -i any \
    -w $NAME-$GROUP-ua.pcapng \
    -n tcp \
