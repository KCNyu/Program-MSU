/*================================================================
 * Filename:server.cpp
 * Author: KCN_yu
 * Createtime:Tue 01 Jun 2021 05:25:28 PM CST
 ================================================================*/

#include <iostream>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

#define SRV_PORT 9999
#define MAXLINE 8192

using namespace std;

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int n;

again:
    if ((n = accept(sockfd, addr, addrlen)) < 0) {
        if ((errno == ECONNABORTED) || (errno == EINTR))
            goto again;
        else {
            cerr << "accept error" << endl;
            exit(1);
        }
    }
    return n;
}
void AvoidBindError(int &server_socket) {
    int on = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&on), sizeof(on));
}
int main(int argc, char *argv[])
{

    int listenfd, connfd;
    int n;
    char buf[BUFSIZ];

    struct sockaddr_in srv_addr, clt_addr;

    bzero(&srv_addr, sizeof(srv_addr));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    AvoidBindError(listenfd);

    bind(listenfd, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr));

    listen(listenfd, 128);

    cout << "Accepting client connect ..." << endl;

    fd_set rset, allset;

    int maxfd = listenfd;
    int nready;

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1){
        rset = allset;
        nready = select(maxfd+1, &rset, nullptr, nullptr, nullptr);
        if(nready < 0){
            cerr << "select error" << endl;
            exit(1);
        }
        if(FD_ISSET(listenfd, &rset)){
            socklen_t clt_addr_len = sizeof(clt_addr);
            connfd = Accept(listenfd, reinterpret_cast<sockaddr*>(&clt_addr), &clt_addr_len);

            FD_SET(connfd, &allset);

            if(maxfd < connfd){
                maxfd = connfd;
            }
            if(nready == 1){
                continue;
            }
        }
        for(int i = listenfd+1; i <= maxfd; i++){
            if(FD_ISSET(i, &rset)){
                if((n = read(i, buf, sizeof(buf))) == 0){
                    close(i);
                    FD_CLR(i, &allset);
                }
                else if(n > 0){
                    for(int j = 0; j < n; j++){
                        buf[j] = toupper(buf[j]);
                    }
                    write(i, buf, n);
                }
            }
        }
    }
    close(listenfd);
    return 0;
}
