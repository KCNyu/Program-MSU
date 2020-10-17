/*================================================================
* Filename:OutputMatrix_read_4.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 04:46:18 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>

#define row 10
#define col 10

int Get(int i, int j){
    return i*col+j;
}
int main(int argc, char *argv[])
{
    struct stat sb;
    int fd, fd_out;
    if((fd = open(argv[1],O_RDONLY)) < 0 ) perror("open");
    //if((fd_ = open("out.txt",O_RDWR|O_CREAT)) < 0 ) perror("open");
    int buf;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            read(fd,&buf,sizeof(int));
            if(j > i) write(1,&buf,sizeof(int));
            else write(1,"  ",2);
        }
        write(1,"\n",1);
    }
    return 0;
}
