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
#include <sys/epoll.h>

#define SRV_PORT 9999
#define MAXLINE 8196
#define OPEN_MAX 1024

using namespace std;

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int n;

again:
    if ((n = accept(sockfd, addr, addrlen)) < 0)
    {
        if ((errno == ECONNABORTED) || (errno == EINTR))
            goto again;
        else
        {
            cerr << "accept error" << endl;
            exit(1);
        }
    }
    return n;
}
void AvoidBindError(int &server_socket)
{
    int on = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, static_cast<void *>(&on), sizeof(on));
}
int main(int argc, char *argv[])
{

    int listenfd, connfd, sockfd;
    int n, num = 0;
    ssize_t nready, efd, res;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];

    struct sockaddr_in srv_addr, clt_addr;

    struct epoll_event tep, ep[OPEN_MAX];

    bzero(&srv_addr, sizeof(srv_addr));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    AvoidBindError(listenfd);

    bind(listenfd, reinterpret_cast<sockaddr *>(&srv_addr), sizeof(srv_addr));

    listen(listenfd, 128);

    efd = epoll_create(OPEN_MAX);
    if (efd == -1)
    {
        cerr << "epoll_create error" << endl;
        exit(1);
    }
    tep.events = EPOLLIN;
    tep.data.fd = listenfd;
    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);
    if (res == -1)
    {
        cerr << "epoll_ctl error" << endl;
        exit(1);
    }
    cout << "Accepting client connect ..." << endl;

    while (1)
    {
        nready = epoll_wait(efd, ep, OPEN_MAX, -1);
        if (nready < 0)
        {
            cerr << "epoll error" << endl;
            exit(1);
        }
        for (int i = 0; i < nready; i++)
        {
            if (!(ep[i].events & EPOLLIN))
            {
                continue;
            }
            if (ep[i].data.fd == listenfd)
            {
                socklen_t clt_addr_len = sizeof(clt_addr);
                connfd = Accept(listenfd, reinterpret_cast<sockaddr *>(&clt_addr), &clt_addr_len);
                printf("received from %s at PORT %d\n",
                       inet_ntop(AF_INET, &clt_addr.sin_addr, str, sizeof(str)),
                       ntohs(clt_addr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                tep.events = EPOLLIN;
                tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);
                if (res == -1)
                {
                    cerr << "epoll_ctl error" << endl;
                    exit(1);
                }
            }
            else
            {
                sockfd = ep[i].data.fd;
                n = read(sockfd, buf, MAXLINE);

                if (n == 0)
                {
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
                    if (res == -1)
                    {
                        cerr << "epoll_ctl error" << endl;
                        exit(1);
                    }
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                }
                else if (n < 0)
                {
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
                    if (res == -1)
                    {
                        cerr << "epoll_ctl error" << endl;
                        exit(1);
                    }
                    if (errno == ECONNRESET)
                    {
                        printf("client[%d] aborted connection\n", i);
                        close(sockfd);
                    }
                }
                else
                {
                    for (int k = 0; k < n; k++)
                    {
                        buf[k] = toupper(buf[k]);
                    }
                    write(sockfd, buf, n);
                    write(STDOUT_FILENO, buf, n);
                }
            }
        }
    }
    close(listenfd);
    close(efd);
    return 0;
}
