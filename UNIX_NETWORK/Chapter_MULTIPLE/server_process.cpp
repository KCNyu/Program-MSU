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

using namespace std;

void catch_child(int signum){
    while(waitpid(0, nullptr, WNOHANG) > 0);
}

int main(int argc, char *argv[])
{
    int lfd, cfd;
    pid_t pid;
    char buf[BUFSIZ];

    struct sockaddr_in srv_addr, clt_addr;

    bzero(&srv_addr, sizeof(srv_addr));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(lfd, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr));

    listen(lfd, 128);

    socklen_t clt_addr_len = sizeof(clt_addr);

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    while(1){
        cfd = accept(lfd, reinterpret_cast<sockaddr*>(&clt_addr), &clt_addr_len);
        if(cfd < 0){
            cerr << "accept error!\n";
            exit(1);
        }

        pid = fork();
        if(pid < 0){
            cerr << "fork error" << endl;
        }
        else if(pid == 0){
            close(lfd);
            while(1){
                int ret = read(cfd, buf, sizeof(buf));
                if(ret == 0){
                    close(cfd);
                    exit(1);
                }
                for(int i = 0; i < ret; i++){
                    buf[i] = toupper(buf[i]);
                }
                write(cfd, buf, ret);
                write(STDOUT_FILENO, buf, ret);
            }
        }
        else{
            struct sigaction act;
            act.sa_handler = catch_child;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;

            sigaction(SIGCHLD, &act, nullptr);
            sigprocmask(SIG_UNBLOCK, &set, NULL);

            close(cfd);
        }
    }
    return 0;
}
