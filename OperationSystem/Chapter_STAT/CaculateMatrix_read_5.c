/*================================================================
* Filename:CaculateMatrix_read_5.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 04:56:51 PM CST
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

int main(int argc, char *argv[])
{
    struct stat sb;
    int fd;
    if((fd = open(argv[1],O_RDONLY)) < 0 ) perror("open");
    int buf;
    int sum = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            read(fd,&buf,sizeof(int));
            if(i == j) sum += buf;
        }
    }
    printf("sum = %d\n",sum);
    close(fd);
    return 0;
}