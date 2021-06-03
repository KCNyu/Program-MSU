/*================================================================
* Filename:test2.c
* Author: KCN_yu
* Createtime:Fri 06 Nov 2020 04:57:27 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int cnt_int = 0;
int cnt_trap = 0;
int cnt_2,cnt_4;

void SigHndlr_trap(int s){
    cnt_trap++;
}
void SigHndlr_int(int s){
    cnt_int++;
    if(cnt_int == 2) cnt_2 = cnt_trap;
    else if(cnt_int == 4){
        cnt_4 = cnt_trap;
        printf("\ncount = %d\n",cnt_4-cnt_2);
    }
    else if(cnt_int == 6) signal(SIGINT,SIG_DFL);
}

int main(int argc, char *argv[])
{
    signal(SIGINT,SigHndlr_int);
    int status;
    if(fork() == 0){
        while(1){
            sleep(1);
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
