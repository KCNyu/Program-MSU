/*================================================================
* Filename:test1.c
* Author: KCN_yu
* Createtime:Fri 13 Nov 2020 02:32:48 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void SigHndlr(int s){
    if(s == SIGALRM){
        printf("I got signal SIGALRM!\n");
        signal(SIGALRM,SigHndlr);
    }
    else if(s == SIGINT){
        printf("I got signal SIGINT!\n");
        exit(EXIT_SUCCESS);
    }
}
int main(int argc, char *argv[])
{
    signal(SIGALRM,SigHndlr);
    signal(SIGINT,SigHndlr);
    int pid = getpid();
    while(1){
        sleep(2);
        kill(pid,SIGALRM);
    }
    return 0;
}
