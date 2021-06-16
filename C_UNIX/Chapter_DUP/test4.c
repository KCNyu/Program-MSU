/*================================================================
* Filename:test4.c
* Author: KCN_yu
* Createtime:Mon 26 Oct 2020 06:40:02 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if(argc < 2) return 1;
    int fd = open(argv[2],O_RDWR|O_CREAT|O_APPEND);
    int p, status;
    p = fork();
    if(p == 0){
        close(1);
        dup2(fd,1);
        close(fd);
        execlp("cat","cat",argv[1],NULL);
        perror("exec");
        return 1;
    }
    else{
        wait(&status);
        if(WIFEXITED(status)){
        }
        return 1;
    }
    return 0;
}