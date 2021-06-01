/*================================================================
* Filename:test5.c
* Author: KCN_yu
* Createtime:Wed 18 Nov 2020 03:13:36 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <signal.h>
void SigHandlr(int s){
    //printf("get alarm!\n");
}
int main(int argc,char **argv)
{
    int i;
    int procs;
    pid_t pid;
    if(argc<2){
        printf("num procs need\n");
        return 1;
    }
    procs = atoi(argv[1]);
    pid_t childPid[procs];
    for(i=0; i<procs; i++){
        if((pid = fork())==0){
            signal(SIGALRM,SigHandlr);
            //printf("i am %d-th and have benn created!\n",i);
            sleep(100);
            printf("son %d\n",i);
            return 0;
        }
        else{
            childPid[i] = pid;
            //printf("i am %dth %d\n",i,pid);
        }
    }
    sleep(1); // give the time for the child processes have been created
    for(i = 0; i < procs; i++){
        //printf("i am %dth %d\n",procs-i-1,childPid[procs-i-1]);
        kill(childPid[procs-i-1],SIGALRM);
        wait(NULL);
    }
    printf("Father!\n");

    return 0;
}
