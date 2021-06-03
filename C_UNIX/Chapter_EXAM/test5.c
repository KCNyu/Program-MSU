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
int main(int argc,char **argv)
{
    int i;
    int procs;
    int fd[2];
    pipe(fd);
    if(argc<2){
        printf("num procs need\n");
        return 1;
    }
    procs = atoi(argv[1]);
    char* res[procs];
    for(i=0; i<procs; i++){
        if(fork()==0){
            dup2(fd[1],STDOUT_FILENO);
            close(fd[0]);close(fd[1]);
            //sleep(procs-i);
            printf("son %d\n",i);
            return 0;
        }
        else{
            int status;
            wait(&status);
        }
    }
    for(i=1;i<=procs;i++){
        if(i <= 10){
            res[procs-i] =  (char*)calloc(sizeof(char),6);
            read(fd[0],res[procs-i],6);
        }
        else{
            res[procs-i] =  (char*)calloc(sizeof(char),7);
            read(fd[0],res[procs-i],7);
        }
        wait(NULL);
    }
    close(fd[0]);close(fd[1]);
    for(i = 0; i < procs; i++){
        printf("%s",res[i]);
    }
    printf("Father!\n");

    return 0;
}
