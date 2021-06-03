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

void Alrm(int s){
    printf("\n wait cmd \n");
    alarm(5);
}
void SigHndlr(int s){
    signal(SIGALRM,Alrm);
    while(1){
        printf("please input cmd: ");
        if(fgets(&cmd,1,stdin) != NULL) break;
    }
    if(cmd == 'D'){
        int n;
        char buf;
        while((n = read(fd,&buf,1)) > 0 && buf != '\n');
    }
    if(cmd == 'C'){
        char temp[N];
        read(fd_p[0],temp,cnt);
        write(fd_res,temp,cnt);
    }
    if(cmd == 'A') return;
}
int main(int argc, char *argv[])
{
    signal(SIGALRM,Alrm);
    signal(SIGUSR1,SigHndlr);
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
                /*for(int i = 0; i < cnt; i++) putchar(temp[i]);
                putchar('\n');*/
                cnt = 0;
            }
            else if(cnt > N){
                for(int i = 0; i < N; i++) putchar(temp[i]);
                putchar('\n');
                write(fd_p[1],temp,N);
                //alarm(5);
                kill(getppid(),SIGUSR1);
                alarm(5);
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
