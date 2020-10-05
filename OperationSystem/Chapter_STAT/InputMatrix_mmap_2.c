/*================================================================
* Filename:InputMatrix_mmap_2.c
* Author: KCN_yu
* Createtime:Sun 04 Oct 2020 10:32:18 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <time.h>

#define SIZE 100
#define SIZE_int SIZE*sizeof(int)

int main(int argc, char *argv[])
{

    struct stat sb;
    int fd;
    int *mapped;

    fd = open(argv[1],O_RDWR|O_CREAT);
    lseek(fd,(SIZE-1)*sizeof(int),SEEK_END);
    write(fd,"",1);
    if((mapped = (int*)mmap(NULL,SIZE_int,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
    close(fd);
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++) mapped[i] = rand()%100;
    if((msync((void*)mapped,SIZE_int,MS_SYNC)) == -1) perror("mysnc");
    if((munmap((void*)mapped,SIZE_int) == -1)) perror("munmap");   
    return 0;
}
