/*================================================================
* Filename:test1.c
* Author: KCN_yu
* Createtime:Mon 26 Oct 2020 06:13:40 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int newfd,fd;
    char c[10];
    //if(argc < 2) return 1;
    //fd = open(argv[1],O_RDONLY);
    fd = open("temp.txt",O_RDONLY);
    if(fd == -1) perror("open");
    close(0);
    //newfd = dup(fd);
    newfd = dup2(fd,0);
    close(fd);
    printf("newfd = %d\n", newfd);
    read(newfd,c,10);
    printf("c = %s\n",c);
    return 0;
}
