/*================================================================
* Filename:fwrite.c
* Author: KCN_yu
* Createtime:Sun 04 Oct 2020 06:37:30 PM CST
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
    int fd = open(argv[1],O_RDWR|O_CREAT);
    int buf;
    srand(time(NULL));

    for(int i = 0; i < 10; i++){
        buf = rand()%20;
        write(fd,&buf,sizeof(int));
    }
    return 0;
}
