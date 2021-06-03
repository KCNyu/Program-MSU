/*================================================================
* Filename:OutputMatrix_mmap_4.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 04:09:22 PM CST
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
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(j > i) printf("%2d ",mapped[Get(i,j)]);
            else printf("   ");
        }
        printf("\n");
    }
    if((munmap((void*)mapped,sb.st_size) == -1)) perror("munmap");
    return 0;
}
