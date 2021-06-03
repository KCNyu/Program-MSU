/*================================================================
* Filename:test1.c
* Author: KCN_yu
* Createtime:Fri 06 Nov 2020 03:46:55 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>

int cnt_int = 1;
int cnt_trap = 0;

void SigHndlr_trap(int s){
    cnt_trap++;
    printf("cnt_trap = %d\n",cnt_trap);
    if(cnt_trap%2 == 0){
        int status;
        if(fork() == 0){ printf("mypid = %d\n",getpid()); }
        else if(fork() == 0){ printf("mypid = %d\n",getpid()); }
        wait(&status);
        wait(&status);
    }
}
void SigHndlr_int(int s){
    cnt_int++;
    if(cnt_int == 3) signal(SIGINT,SIG_DFL);
}
int main(int argc, char *argv[])
{
    signal(SIGINT,SigHndlr_int);
    int status;
    if(fork() == 0){
        cnt_trap++;
        while(1){
            sleep(10);
            kill(getppid(),SIGTRAP);
            printf("kill trap\n");
        }
    }
    else{
        signal(SIGTRAP,SigHndlr_trap);
        wait(&status);
    }
    return 0;
}
