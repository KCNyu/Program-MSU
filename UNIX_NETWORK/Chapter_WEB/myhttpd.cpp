/*================================================================
 * Filename:myhttpd0.cpp
 * Author: KCN_yu
 * Createtime:Fri 18 Jun 2021 04:23:39 PM CST
 ================================================================*/

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#define MAXSIZE 1024

int get_line(int cfd, char *buf, int size) {
    int i = 0;
    char c = '\0';
    int n;
    while ((i < size - 1) && (c != '\n')) {
        n = recv(cfd, &c, 1, 0);
        if (n > 0) {
            if (c == '\r') {
                n = recv(cfd, &c, 1, MSG_PEEK);
                if ((n > 0) && (c == '\n')) {
                    recv(cfd, &c, 1, 0);
                } else {
                    c = '\n';
                }
            }
            buf[i] = c;
            i++;
        } else {
            c = '\n';
        }
    }
    buf[i] = '\0';

    if (n == -1) {
        i = n;
    }
    return i;
}
int init_listen_fd(int port, int epfd) {
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        cerr << "socket error" << endl;
        exit(1);
    }

    struct sockaddr_in srv_addr;

    bzero(&srv_addr, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(port);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    int ret = bind(lfd, reinterpret_cast<struct sockaddr *>(&srv_addr),
            sizeof(srv_addr));
    if (ret == -1) {
        cerr << "bind error" << endl;
        exit(1);
    }

    ret = listen(lfd, 128);

    if (ret == -1) {
        cerr << "listen error" << endl;
        exit(1);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    if (ret == -1) {
        cerr << "epoll_ctl add lfd error" << endl;
        exit(1);
    }

    return lfd;
}
void do_accept(int lfd, int epfd) {
    struct sockaddr_in clt_addr;
    socklen_t clt_addr_len = sizeof(clt_addr);

    int cfd = accept(lfd, reinterpret_cast<struct sockaddr *>(&clt_addr),
            &clt_addr_len);
    if (cfd == -1) {
        cerr << "accpet error" << endl;
        exit(1);
    }

    char client_ip[64] = {0};
    printf("New Client IP: %s, Port: %d, cfd = %d\n",
            inet_ntop(AF_INET, &clt_addr.sin_addr.s_addr, client_ip,
                sizeof(client_ip)),
            ntohs(clt_addr.sin_port), cfd);

    struct epoll_event ev;
    ev.data.fd = cfd;

    ev.events = EPOLLIN | EPOLLET;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
    if (ret == -1) {
        cerr << "epoll_etl add cfd error" << endl;
        exit(1);
    }
}
void disconnect(int cfd, int epfd){
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
    if (ret != 0) {
        cerr << "epoll_ctl error" << endl;
        exit(1);
    }
    close(cfd);
}
void send_respond(int cfd, int no, const char *disp, const char *type, int len){
    char buf[1024] = {0};
    sprintf(buf, "HTTP/1.1 %d %s\r\n",no, disp);
    send(cfd, buf, strlen(buf), 0);
    sprintf(buf+strlen(buf), "%s\r\n", type);
    sprintf(buf+strlen(buf), "Content-Length:%d\r\n", len);
    send(cfd, "\r\n", 2, 0);
}
void send_file(int cfd, const char* file){
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        cerr << "open error" << endl;
        exit(1);
    }
    int n;
    char buf[1024];
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        send(cfd,buf, n, 0);
    }
    close(fd);

}
void http_request(int cfd, const char* file){
    struct stat sbuf;

    int ret = stat(file, &sbuf);
    if (ret != 0) {
        cerr << "stat error" << endl;
        exit(1);
    }

    if(S_ISREG(sbuf.st_mode)){
        send_respond(cfd, 200, "OK", "Content-Type: text/plain; charset=ios-8859-1", sbuf.st_size);
        cout << "is a regular file" << endl;
        send_file(cfd,file);
    }
}
void do_read(int cfd, int epfd){
    char line[1024] = { 0 };
    int len = get_line(cfd, line, sizeof(line));
    if (len == 0) {
        cerr << "server check the client closed" << endl;
        disconnect(cfd, epfd);
    } else {
        char method[16], path[256], protocol[16];
        sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol);
        printf("method=%s, path=%s, protocol=%s\n",method,path,protocol);
        while(1){
            char buf[1024] = {0};
            len = get_line(cfd, buf, sizeof(buf));
            if (len == 1){
                break;
            }
        }
        if (strncasecmp(method, "GET", 3) == 0){
            char *file = path+1;
            http_request(cfd, file);
        }
    }
}
void epoll_run(int port) {
    int i = 0;
    struct epoll_event all_events[MAXSIZE];

    int epfd = epoll_create(MAXSIZE);
    if (epfd == -1) {
        cerr << "epoll_create error" << endl;
        exit(1);
    }

    int lfd = init_listen_fd(port, epfd);

    while (1) {
        int ret = epoll_wait(epfd, all_events, MAXSIZE, -1);
        if (ret == -1) {
            cerr << "epoll_wait error" << endl;
            exit(1);
        }
        for (i = 0; i < ret; ++i) {
            struct epoll_event *pev = &all_events[i];

            if (!(pev->events & EPOLLIN)) {
                continue;
            }
            if (pev->data.fd == lfd) {
                do_accept(lfd, epfd);
            } else {
                do_read(pev->data.fd, epfd);
            }
        }
    }
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "./a.out port path" << endl;
    }

    int port = atoi(argv[1]);

    int ret = chdir(argv[2]);

    if (ret != 0) {
        cerr << "chdir error" << endl;
        exit(1);
    }

    epoll_run(port);

    return 0;
}
