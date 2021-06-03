/*================================================================
* Filename:wrap.cpp
* Author: KCN_yu
* Createtime:Tue 01 Jun 2021 04:39:21 PM CST
================================================================*/

#include "wrap.h"
using namespace std;

void sys_err(const char *str){
    cerr << str << endl;
    exit(1);
}

int Socket(int domain, int type, int protocol){
    int n;

    n = socket(domain, type, protocol);
    if(n == -1){
        sys_err("socket error");
        return n;
    }
    return 0;
}
int Listen(int sockfd, int backlog){
    int n = 0;

    n = listen(sockfd, backlog);
    if(n == -1){
        sys_err("listen error");
        return n;
    }
    return 0;
}
