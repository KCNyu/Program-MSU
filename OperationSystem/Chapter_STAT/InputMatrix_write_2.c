/*================================================================
* Filename:InputMatrix_write_2.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 12:10:48 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int fd;
    if((fd = open(argv[1],O_RDWR|O_CREAT)) < 0 ) perror("open");
    srand(time(NULL));
    for(int i = 0; i < 100; i++){
        int buf = rand()%100;
        write(fd,&buf,sizeof(int));
    }
    close(fd);
    return 0;
}
