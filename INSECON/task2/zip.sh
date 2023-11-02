#!/bin/bash
NAME=lisy
GROUP=628

zip -r $NAME-$GROUP-p2.zip \
	$NAME-ci.pcap \
    $NAME-sqli.pcap
    