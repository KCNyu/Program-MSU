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
#include <poll.h>

#define SRV_PORT 9999
#define MAXLINE 8196
#define OPEN_MAX 1024

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
    ssize_t n;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];

    struct sockaddr_in srv_addr, clt_addr;
    struct pollfd client[OPEN_MAX];

    bzero(&srv_addr, sizeof(srv_addr));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    AvoidBindError(listenfd);

    bind(listenfd, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr));

    listen(listenfd, 128);


    cout << "Accepting client connect ..." << endl;


    int nready;

    client[0].fd = listenfd;
    client[0].events = POLLIN;

    for(int i = 1; i < OPEN_MAX; i++){
        client[i].fd = -1;
    }

    int maxi = 0, tmp_index;


    while(1){
        nready = poll(client, maxi+1, -1);
        if(nready < 0){
            cerr << "select error" << endl;
            exit(1);
        }
        if(client[0].revents & POLLIN){
            socklen_t clt_addr_len = sizeof(clt_addr);
            connfd = Accept(listenfd, reinterpret_cast<sockaddr*>(&clt_addr), &clt_addr_len);
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &clt_addr.sin_addr, str, sizeof(str)),
                    ntohs(clt_addr.sin_port));
            for(int i = 1; i < OPEN_MAX; i++){
                if(client[i].fd < 0){
                    client[i].fd = connfd;
                    client[i].events = POLLIN;
                    tmp_index = i;
                    break;
                }
            }
            if(maxi < tmp_index){
                maxi = tmp_index;
            }
            if(nready == 1){
                continue;
            }
        }
        for(int i = 1; i <= maxi; i++){
            int sockfd;
            if((sockfd = client[i].fd) < 0){
                continue;
            }
            if(client[i].revents & POLLIN){
                if((n = read(sockfd, buf, sizeof(buf))) == 0){
                    printf("client[%d] closed connection\n", i);
                    close(sockfd);
                    client[i].fd = -1;
                }
                else if(n < 0){
                    if(errno == ECONNRESET){
                        printf("client[%d] aborted connection\n", i);
                        close(sockfd);
                        client[i].fd = -1;
                    }

                }
                else if(n > 0){
                    for(int j = 0; j < n; j++){
                        buf[j] = toupper(buf[j]);
                    }
                    write(sockfd, buf, n);
                    write(STDOUT_FILENO, buf, n);
                }
                if(--nready == 0){
                    break;
                }
            }
        }
    }
    close(listenfd);
    return 0;
}
