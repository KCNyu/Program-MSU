/*================================================================
* Filename:Delete_write_1.c
* Author: KCN_yu
* Createtime:Sun 04 Oct 2020 08:27:46 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>

int main(int argc, char *argv[])
{
    int fd,fd_temp;
    if((fd = open(argv[1],O_RDWR)) < 0 ) perror("open");
    if((fd_temp = open("temp.txt",O_RDWR|O_CREAT)) < 0) perror("open");

    int n;
    int buf;
    while((n = read(fd,&buf,sizeof(int))) > 0){
        if(buf%2 == 0) continue;
        write(fd_temp,&buf,n);
    }
    close(fd);close(fd_temp);
    remove(argv[1]);
    rename("temp.txt",argv[1]);
    return 0;
}
