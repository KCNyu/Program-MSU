/*================================================================
* Filename:1.5.cpp
* Author: KCN_yu
* Createtime:Mon 17 May 2021 10:59:25 PM CST
================================================================*/

#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#define MAXLINE 255
#define LISTENQ 5
using namespace std;

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    bind(listenfd, (sockaddr*) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    while(true){
        connfd = accept(listenfd, (sockaddr*)nullptr, nullptr);
        ticks = time(nullptr);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
    return 0;
}

