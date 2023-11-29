#!/bin/bash

# !tcp.analysis.duplicate_ack_frame && !tcp.analysis.retransmission

NAME=lisy
GROUP=628

sudo tcpdump \
    -i any \
    -w $NAME-$GROUP-acl-unfiltered.pcapng \
    -n tcp \
