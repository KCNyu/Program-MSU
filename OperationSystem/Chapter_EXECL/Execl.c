/*================================================================
* Filename:Execl.c
* Author: KCN_yu
* Createtime:Mon 19 Oct 2020 06:52:18 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++){
        int status, pid;
        if(fork() > 0){
            pid = wait(&status);
            printf("process %d finished\n",pid);
            continue;
        }
        execlp(argv[i],argv[i],NULL);
        return -1;
    }
    return 0;
}

