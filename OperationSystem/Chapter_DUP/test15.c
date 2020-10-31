/*================================================================
* Filename:test15.c
* Author: KCN_yu
* Createtime:Tue 27 Oct 2020 07:14:21 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1[2],fd2[2];
    pipe(fd2);
    if(fork() == 0){
        pipe(fd1);
        if(fork() == 0){
            dup2(fd1[1],1);
            close(fd1[0]);close(fd1[1]);
            execlp("ls","ls",NULL);
            perror("exec ls"); exit(1);
        }
        else{
            dup2(fd1[0],0);
            close(fd1[0]);
            close(fd1[1]);
            dup2(fd2[1],1);
            close(fd2[0]);close(fd2[1]);
            execlp("cat","cat",NULL);
            perror("exec cat"); exit(1);
        }
    }
    else{
        dup2(fd2[0],0);
        close(fd2[0]);close(fd2[1]);
        execlp("wc","wc",NULL);
        perror("exec wc"); exit(1);
    }
    return 0;
}
