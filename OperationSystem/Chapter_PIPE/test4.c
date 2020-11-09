/*================================================================
* Filename:test4.c
* Author: KCN_yu
* Createtime:Tue 03 Nov 2020 01:34:02 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int target_pid;
int child_pid,parent_pid;
int fd1,fd2,fd_res,N;

void SigHndlr(int s){
    signal(SIGUSR1,SigHndlr);
    char buf[N];
    int n;
    /*
    printf("pid = %d\n",getpid());
    printf("ppid = %d\n",getppid());
    printf("target_pid = %d\n",target_pid);
    printf("child_pid = %d\n",child_pid);
    printf("parent_pid = %d\n",parent_pid);
    */
    if(child_pid != 0 && ((n = read(fd1,buf,N)) == N)){
        printf("i am child\n");
        write(fd_res,&buf,N);
        kill(target_pid,SIGUSR1);
    }
    else if(child_pid == 0 && ((n = read(fd2,buf,N)) == N)){
        printf("i am parent\n");
        write(fd_res,&buf,N);
        kill(target_pid,SIGUSR1);
    }
    else{
        if(parent_pid == getppid()){
            printf("child is going to be closed\n");
            close(fd1);
            exit(0);
        }
        else{
            kill(target_pid,SIGUSR1);
        }
    }
}
int main(int argc, char *argv[])
{
    signal(SIGUSR1,SigHndlr);
    int status;

    N = atoi(argv[4]);
    fd_res = open(argv[3],O_RDWR|O_CREAT);
    if((target_pid = fork()) > 0){
        fd2 = open(argv[2],O_RDONLY);
        wait(&status);
        printf("parent is going to be closed\n");
        close(fd2);
        return 0;
    }
    else{
        target_pid = getppid();
        parent_pid = getppid();
        child_pid = getpid();
        printf("==============================================\n");
        printf("child_pid = %d\n",child_pid);
        printf("parent_pid = %d\n",parent_pid);
        printf("==============================================\n");
        fd1 = open(argv[1],O_RDONLY);
        char buf[N];
        read(fd1,buf,N);
        write(fd_res,buf,N);
        kill(target_pid,SIGUSR1);
        while(1);
    }
    return 0;
}
