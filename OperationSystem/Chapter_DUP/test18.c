/*================================================================
* Filename:test18.c
* Author: KCN_yu
* Createtime:Mon 02 Nov 2020 06:17:41 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

#define MAX_CNT 100

int target_pid;
int cnt = 0;
int fd1[2],fd2[2];
int status;


void SigHndlr(int s){
    signal(SIGUSR1,SigHndlr);
    if(cnt < MAX_CNT){
        read(fd2[0],&cnt,sizeof(int));
        printf("cnt = %d\n",cnt);
        cnt++;
        write(fd1[1],&cnt,sizeof(int));
        kill(target_pid,SIGUSR1);
    }
}
int main(int argc, char *argv[])
{
    pipe(fd1); pipe(fd2);
    signal(SIGINT,SigHndlr);
    if(fork() == target_pid){
        while(wait(&status) == -1){
            close(fd1[1]);
            close(fd2[0]);
            return 0;
        }
    }
    else{
        target_pid = getppid();
        write(fd2[1],&cnt,sizeof(int));
        kill(target_pid,SIGUSR1);
    }
    return 0;
}
