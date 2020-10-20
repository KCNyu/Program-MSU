/*================================================================
* Filename:Execl_run_2.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 01:24:52 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++){
        int status, pid;
        if(fork() > 0){
            pid = wait(&status);
            printf("process %d finished\n",pid);
            continue;
        }
        char str[] = "./";
        strcat(str,argv[i]);
        execlp(str,argv[i],NULL);
        return -1;
    }
    return 0;
}
