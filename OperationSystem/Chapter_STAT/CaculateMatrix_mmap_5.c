/*================================================================
* Filename:CaculateMatrix_mmap_5.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 04:51:16 PM CST
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
    int fd;
    int *mapped;

    if((fd = open(argv[1],O_RDONLY)) < 0 ) perror("open");
    if(fstat(fd,&sb) == -1) perror("fstat");
    if((mapped = (int*)mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
    close(fd);
    int sum = 0;
    int num = row ? col : row >= col;
    for(int i = 0; i < num; i++) sum += mapped[(Get(i,i))];
    if((munmap((void*)mapped,sb.st_size) == -1)) perror("munmap");

    printf("sum = %d\n",sum);
    return 0;
}