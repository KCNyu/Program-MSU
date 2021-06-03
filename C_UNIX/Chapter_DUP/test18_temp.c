/*================================================================
* Filename:test18.c
* Author: KCN_yu
* Createtime:Mon 02 Nov 2020 06:17:41 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

void SigHndlr(int s){
}
int main(int argc, char *argv[])
{
    int cnt = 0;
    int fd1[2],fd2[2];
    int status;
    pipe(fd1);pipe(fd2);
    if(fork() == 0){
        close(fd1[0]);close(fd2[1]);
        while(1){
            write(fd1[1],&cnt,sizeof(int));
            read(fd2[0],&cnt,sizeof(int));
            printf("pid = %d    cnt = %d\n",getpid(),cnt);
            cnt++;
        }
    }
    else{
        close(fd1[1]);close(fd2[0]);
        while(1){
            read(fd1[0],&cnt,sizeof(int));
            printf("pid = %d    cnt = %d\n",getpid(),cnt);
            cnt++;
            write(fd2[1],&cnt,sizeof(int));
        }
        wait(&status);
    }
    return 0;
}
