/*================================================================
* Filename:test13.c
* Author: KCN_yu
* Createtime:Tue 27 Oct 2020 06:47:43 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    if(fork() == 0){
        dup2(fd[1],1);
        close(fd[1]);
        close(fd[0]);
        execlp("ls","ls",NULL);
        perror("exec ls"); exit(1);
    }
    else{
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        execlp("wc","wc",NULL);
        perror("exec wc"); exit(1);
    }
    return 0;
}

