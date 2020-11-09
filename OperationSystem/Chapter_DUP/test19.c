/*================================================================
* Filename:test19.c
* Author: KCN_yu
* Createtime:Mon 02 Nov 2020 07:07:34 PM CST
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
int fd[2];
int status;

void SigHndlr(int s){
    signal(SIGUSR1,SigHndlr);
    if(cnt < MAX_CNT){
        read(fd[0],&cnt,sizeof(int));
        printf("pid = %d\n",getpid());
        printf("%d\n",cnt);
        cnt++;
        write(fd[1],&cnt,sizeof(int));
        kill(target_pid,SIGUSR1);
    }
    else{
        if(target_pid == getppid()){
            printf("child is going to be terminated\n");
            close(fd[1]); close(fd[0]);
            exit(0);
        }
        else{
            kill(target_pid, SIGUSR1);
        }
    }
}
int main(int argc, char *argv[])
{
    pipe(fd);
    signal(SIGUSR1, SigHndlr);
    cnt = 0;
    if((target_pid = fork()) > 0){
        /*
        while(wait(&status)){
            printf("parent is going to be terminated\n");
            close(fd[1]); close(fd[0]);
            return 0;
        }
        */
        wait(&status);
        printf("parent is going to be terminated\n");
        close(fd[1]); close(fd[0]);
        return 0;
    }
    else{
        target_pid = getppid();
        write(fd[1],&cnt,sizeof(int));
        kill(target_pid, SIGUSR1);
        while(1);
    }
    return 0;
}

