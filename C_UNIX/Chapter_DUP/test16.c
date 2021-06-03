/*================================================================
* Filename:test16.c
* Author: KCN_yu
* Createtime:Tue 27 Oct 2020 07:26:12 PM CST
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
        execlp("ls","ls",NULL);
        perror("ls");exit(1);
    }
    else{
        dup2(fd[0],0);
        close(fd[0]);close(fd[1]);
        int f = open("res.txt",O_RDWR|O_CREAT);
        dup2(f,1);
        close(f);
        execlp("cat","cat",NULL);
        perror("cat");exit(1);
    }
    return 0;
}

