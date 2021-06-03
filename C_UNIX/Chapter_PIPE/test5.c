/*================================================================
* Filename:test5.c
* Author: KCN_yu
* Createtime:Tue 03 Nov 2020 01:05:30 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

char cmd;
int cnt = 0;
int fd, fd_res, N;

int fd_p[2];

void SigHndlr(int s){
    signal(SIGUSR1,SigHndlr);
    printf("input cmd: ");
    fgets(&cmd,1,stdin);
    write(fd_p[1],&cmd,1);
}
int main(int argc, char *argv[])
{
    pipe(fd_p);
    fd = open(argv[1],O_RDONLY);
    fd_res = open(argv[2],O_RDWR|O_CREAT);
    N = atoi(argv[3]);
    int n, status;
    char temp[N];
    if(fork() == 0){
        char buf;
        while((n = read(fd,&buf,1)) > 0){
            temp[cnt++] = buf;
            if(cnt <= N && buf == '\n'){
                write(fd_res,temp,cnt);
                cnt = 0;
            }
            else if(cnt > N){
                kill(getppid(),SIGUSR1);
                sleep(2);
                read(fd_p[0],temp,N);
                if(cmd == 'D'){
                    while((n = read(fd,&buf,1)) > 0 && buf != '\n');
                }
                if(cmd == 'C'){
                    write(fd_res,temp,N);
                }
                if(cmd == 'A') exit(0);
                cnt = 0;
            }
        }
    }
    else{
        signal(SIGUSR1,SigHndlr);
        wait(&status);
    }
    return 0;
}
