/*================================================================
 * Filename:server.cpp
 * Author: KCN_yu
 * Createtime:Tue 01 Jun 2021 05:25:28 PM CST
 ================================================================*/

#include <iostream>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <wait.h>

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

struct s_info{
    struct sockaddr_in cliaddr;
    int connfd;
};

void *do_work(void *arg){
    int n;
    struct s_info *ts = static_cast<s_info*>(arg);
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];

    while(1){
        n = read(ts->connfd, buf, MAXLINE);
        if(n == 0){
            cout << "the client " << ts->connfd << " closed..." << endl;
            break;
        }
        cout << "received from " << inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str))
        << " at PORT " << ntohs((*ts).cliaddr.sin_port) << endl;
        for(int i = 0; i < n; i++){
            buf[i] = toupper(buf[i]);
        }
        write(STDOUT_FILENO, buf, n);
        write(ts->connfd, buf, n);
    }
    close(ts->connfd);

    return (void*)0;
}
int main(int argc, char *argv[])
{
    int lfd, cfd;
    struct s_info ts[256];
    int i = 0;
    pthread_t tid;

    struct sockaddr_in srv_addr, clt_addr;

    bzero(&srv_addr, sizeof(srv_addr));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(lfd, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr));

    listen(lfd, 128);


    cout << "Accepting client connect ..." << endl;

    while(1){
        socklen_t clt_addr_len = sizeof(clt_addr);
        cfd = Accept(lfd, reinterpret_cast<sockaddr*>(&clt_addr), &clt_addr_len);
        ts[i].cliaddr = clt_addr;
        ts[i].connfd = cfd;

        pthread_create(&tid, NULL, do_work, static_cast<void*>(&ts[i]));
        pthread_detach(tid);
        i++;
    }
    return 0;
}
