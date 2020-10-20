/*================================================================
* Filename:test1.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 05:52:38 PM CST
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
    int f_output = open(argv[1],O_RDWR|O_CREAT);
    int size_output = 0;
    int off_set = 0;
    char* mapped_output;
    for(int i = 2; i < argc; i++){
        int fd;
        struct stat sb;
        if((fd = open(argv[i],O_RDWR)) < 0 ) perror("open");
        if(fstat(fd,&sb) == -1) perror("fstat");
        close(fd);
        size_output += sb.st_size;
    }
    lseek(f_output,size_output-1,SEEK_END);
    write(f_output,"",1);
    if((mapped_output = (char*)mmap(NULL,size_output,PROT_READ|PROT_WRITE,MAP_SHARED,f_output,off_set)) == (void*)-1) perror("mmap");
    for(int i = 2; i < argc; i++){
        int fd;
        struct stat sb;
        char* mapped;
        if((fd = open(argv[i],O_RDWR)) < 0 ) perror("open");
        if(fstat(fd,&sb) == -1) perror("fstat");
        if((mapped = (char*)mmap(NULL,sb.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
        close(fd);
        for(int i = 0; i < sb.st_size; i++) mapped_output[i+off_set] = mapped[i];
        off_set += sb.st_size;
        if((munmap((void*)mapped,sb.st_size) == -1)) perror("munmap");
    }
    if((munmap((void*)mapped_output,size_output) == -1)) perror("munmap");
    return 0;
}
