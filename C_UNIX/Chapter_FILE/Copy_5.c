/*================================================================
* Filename:Copy.c
* Author: KCN_yu
* Createtime:Tue 22 Sep 2020 06:27:54 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void error(char *str, char*filename){
    printf(str,filename); exit(-1);
}
int main(int argc, char *argv[])
{
    int f1, f2, n;
    if((f1 = open(argv[1], O_RDWR|O_CREAT)) == -1) error("Error open file %s", argv[1]);
    if((f2 = open(argv[2], O_RDWR|O_APPEND|O_CREAT)) == -1) error("Error open file %s", argv[2]);
    char buf;
    while((n = read(f1,&buf,1)) > 0) write(f2,&buf,n);
        //if(write(f2,buf,n)) error("error write in file %s", file2);
    //if(n < 0) error("error read from file %s", file1);
    close(f1); close(f2);
    return 0;
}

