/*================================================================
* Filename:Delete_mmap_1.c
* Author: KCN_yu
* Createtime:Sun 04 Oct 2020 06:01:17 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

int main(int argc, char *argv[])
{

    struct stat sb;
    int fd;
    int *mapped;

    if((fd = open(argv[1],O_RDWR)) < 0 ) perror("open");
    if(fstat(fd,&sb) == -1) perror("fstat");
    if((mapped = (int*)mmap(NULL,sb.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
    close(fd);

    int size = sb.st_size/sizeof(int);
    int length = 0;
    for(int i = 0; i < size; i++){
        if(mapped[i]%2 != 0) length++;
    }
    int *temp = (int*)malloc(sizeof(int)*length);
    int j = 0;
    for(int i = 0; i < sb.st_size; i++){
        if(mapped[i]%2 != 0) temp[j++] = mapped[i];
    }

    if((munmap((void*)mapped,sb.st_size) == -1)) perror("munmap");
    remove(argv[1]);

    fd = open(argv[1],O_RDWR|O_CREAT);
    lseek(fd,(length-1)*sizeof(int),SEEK_END);
    write(fd,"",1);
    int length_int = length*sizeof(int);
    if((mapped = (int*)mmap(NULL,length_int,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
    close(fd);

    //for(int i = 0; i < length; i++) mapped[i] = temp[i];
    memcpy(mapped,temp,length_int);
    free(temp);
    if((msync((void*)mapped,length_int,MS_SYNC)) == -1) perror("mysnc");
    if((munmap((void*)mapped,length_int) == -1)) perror("munmap");
    return 0;
}
