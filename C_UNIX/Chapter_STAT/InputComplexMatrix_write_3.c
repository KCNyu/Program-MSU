/*================================================================
* Filename:InputComplexMatrix_write_3.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 03:40:05 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
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
    complex buf;
    if((fd = open(argv[1],O_RDWR|O_CREAT)) < 0 ) perror("open");
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int m = i+1;
            int n = j+1;
            buf.re = cos(M_PI/m)+cos(M_PI/n);
            buf.im = sin(M_PI/m)+sin(M_PI/n);
            write(fd,&buf,sizeof(complex));
        }
    }
    close(fd);
    return 0;
}
