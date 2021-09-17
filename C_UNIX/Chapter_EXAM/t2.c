/*================================================================
* Filename:t2.c
* Author: KCN_yu
* Createtime:Sat 11 Sep 2021 09:36:14 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
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

int count = 0;

void SigHandlr(int s){
    printf("pid = %d count = %d\n",getpid(), count);
    alarm(2);
}

int main(int argc, char *argv[])
{
    signal(SIGALRM,SigHandlr);
    alarm(2);
    while(1){
        char t;
        read(STDIN_FILENO,&t,sizeof(char));
        if(t == 'a') count++;
    }
    return 0;
}
