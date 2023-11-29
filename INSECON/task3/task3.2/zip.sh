#!/bin/bash
NAME=lisy
GROUP=628

mv acl.conf $NAME-$GROUP-acl.conf
mv bump.conf $NAME-$GROUP-bump.conf

zip -r $NAME-$GROUP-p3_2.zip \
	$NAME-$GROUP-acl.pcapng \
	$NAME-$GROUP-acl.log \
	$NAME-$GROUP-acl.conf \
    $NAME-$GROUP-bump.pcapng \
    $NAME-$GROUP-bump.log \
    $NAME-$GROUP-bump.conf \
    $NAME-$GROUP-bump.crt \
    $NAME-$GROUP-bump.key \
    $NAME-$GROUP-ca.crt \

    