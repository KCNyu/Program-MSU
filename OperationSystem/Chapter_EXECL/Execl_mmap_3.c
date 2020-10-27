/*================================================================
* Filename:Execl_mmap_3.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 01:34:16 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SIZE_LETTER 26

int main(int argc, char *argv[])
{
    int status, pid;
    if(fork() > 0){
        pid = wait(&status);
        char upper[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        int fd = open("3.txt",O_RDWR|O_CREAT);
        lseek(fd,SIZE_LETTER-1,SEEK_END);
        write(fd,"",1);
        char* mapped;
        if((mapped = (char*)mmap(NULL,SIZE_LETTER,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
        //if((mapped = (char*)mmap(NULL,SIZE_LETTER,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,fd,0)) == (void*)-1) perror("mmap");
        //if((mapped = (char*)mmap(NULL,SIZE_LETTER,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0)) == (void*)-1) perror("mmap");
        close(fd);
        for(int i = 0; i < 26; i++) mapped[i] = upper[i];
        if((munmap((void*)mapped,SIZE_LETTER) == -1)) perror("munmap");
    }
    else{
        char lower[] = {"abcdefghijklmnopqrstuvwxyz"};
        int fd = open("3.txt",O_RDWR|O_CREAT);
        lseek(fd,SIZE_LETTER,SEEK_END);
        write(fd,"",1);
        char* mapped;
        if((mapped = (char*)mmap(NULL,SIZE_LETTER,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
        //if((mapped = (char*)mmap(NULL,SIZE_LETTER,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,fd,0)) == (void*)-1) perror("mmap");
        //if((mapped = (char*)mmap(NULL,SIZE_LETTER,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0)) == (void*)-1) perror("mmap");
        close(fd);
        for(int i = 0; i < 26; i++) mapped[i+26] = lower[i];
        if((munmap((void*)mapped,SIZE_LETTER) == -1)) perror("munmap");
        return -1;
    }
    return 0;
}
