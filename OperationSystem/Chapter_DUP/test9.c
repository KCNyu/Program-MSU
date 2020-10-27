/*================================================================
* Filename:test9.c
* Author: KCN_yu
* Createtime:Mon 26 Oct 2020 07:28:11 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int fd, N;

void SigHndlr(int s){
    int count = N;
    char buf;
    int n;
    printf("\n");
    while((n = read(fd,&buf,1)) > 0){
        printf("%c",buf);
        if(buf == '\n') count--;
        if(count == 0) break;
    }
    if(count == 0) signal(SIGINT,SigHndlr);
    else signal(SIGINT,SIG_DFL);
}
int main(int argc, char *argv[])
{
    fd = open(argv[1],O_RDONLY);
    N = atoi(argv[2]);
    signal(SIGINT,SigHndlr);
    while(1);
    return 0;
}


