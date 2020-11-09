/*================================================================
* Filename:test17.c
* Author: KCN_yu
* Createtime:Mon 02 Nov 2020 06:11:59 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    if(fork() == 0){
        dup2(fd[1],1);
        close(fd[0]);close(fd[1]);
        execlp(argv[1],argv[1],argv[2],argv[3],NULL);
        perror(argv[1]);exit(1);
    }
    else{
        dup2(fd[0],0);
        close(fd[0]);close(fd[1]);
        int f = open("f.dat",O_RDWR|O_CREAT);
        dup2(f,1);
        close(f);
        execlp(argv[4],argv[4],argv[5],argv[6],NULL);
        perror(argv[2]);exit(1);
    }
    return 0;


