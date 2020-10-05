/*================================================================
* Filename:InputComplexMatrix_mmap_3.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 03:05:23 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <math.h>

typedef struct
{
    double re;
    double im;
}complex;

#define SIZE 100
#define SIZE_complex SIZE*sizeof(complex)
#define row 10
#define col 10

int main(int argc, char *argv[])
{
    int fd;
    complex *mapped;

    fd = open(argv[1],O_RDWR|O_CREAT);
    lseek(fd,(SIZE-1)*sizeof(complex),SEEK_END);
    write(fd,"",1);
    if((mapped = (complex*)mmap(NULL,SIZE_complex,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == (void*)-1) perror("mmap");
    close(fd);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int m = i+1;
            int n = j+1;
            mapped[col*i+j].re = cos(M_PI/m)+cos(M_PI/n);
            mapped[col*i+j].im = sin(M_PI/m)+sin(M_PI/n);
        }
    }
    if((msync((void*)mapped,SIZE_complex,MS_SYNC)) == -1) perror("mysnc");
    if((munmap((void*)mapped,SIZE_complex) == -1)) perror("munmap");   
    return 0;
}