/*================================================================
* Filename:test5.c
* Author: KCN_yu
* Createtime:Wed 18 Nov 2020 03:13:36 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(int argc,char **argv)
{
    int i;
    int procs;
    int fd[2];
    int fd_tmp[2];
    pipe(fd);
    pipe (fd_tmp);
    if(argc<2){
        printf("num procs need\n");
        return 1;
    }
    procs = atoi(argv[1]);
    for(i=0; i<procs; i++){
        if(fork()==0){
            //dup2(fd[1],STDOUT_FILENO);
            //close(fd[0]);close(fd[1]);
            //sleep(procs-i);
            printf("son %d\n",i);
            return 0;
        }
        /*
        else{
            int status;
            wait(&status);
            char* s = (char*)calloc(sizeof(char),12);
            read(fd[0],s,12);
            write(fd_tmp[1],s,12);
        }*/
    }
    wait(NULL);
    for(i=0;i<procs;i++){
        wait(NULL);
    }
    /*
    for(i = 0; i < procs; i++){
        char* s = (char*)calloc(sizeof(char),12);
        read(fd_tmp[0],s,12);
        puts(s);
    }*/
    printf("Father!\n");

    return 0;
}
