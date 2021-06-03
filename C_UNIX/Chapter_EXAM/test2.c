/*================================================================
* Filename:test2.c
* Author: KCN_yu
* Createtime:Tue 17 Nov 2020 02:43:37 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <wait.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
/*
int tmp[100];
int fd_pid[2];
int i;
void SigHndlr(int s){
    printf("i = %d\n",i);
    int pid;
    read(fd_pid[0],&pid,sizeof(int));
    printf("pid: %d\n",pid);
    tmp[i] = pid;
}
*/
int main(int argc, char *argv[])
{
    int status;
    int fd_pid[2];
    int tmp[100];
    pipe(fd_pid);
    for(int i = 1; i < argc; i++){
        if(fork() == 0){
            if(fork() == 0){
                int pid = getpid();
                write(fd_pid[1],&pid,sizeof(int));
                execlp(argv[i],argv[i],NULL);
                exit(0);
            }
            else{
                /*
                if(WIFEXITED(status) == 0){
                    int pid;
                    read(fd_pid[0],&pid,sizeof(int));
                    tmp[i] = pid;
                    printf("name: %s\npid: %d\n",argv[i],tmp[i]);
                }
                */
                signal(SIGCHLD,SigHndlr);
            }
        }
        else{
            wait(&status);
        }
    }
    sleep(15);
    for(int i = 1; i < argc; i++){
        int ret;
        if((ret = kill(tmp[i],0)) == 0) kill(SIGTERM,tmp[i]);
    }
    sleep(5);
    for(int i = 1; i < argc; i++){
        int ret;
        if((ret = kill(tmp[i],0)) == 0) kill(SIGKILL,tmp[i]);
    }
    return 0;
}
