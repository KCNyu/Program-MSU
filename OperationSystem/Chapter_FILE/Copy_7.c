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
    int f1,f2,n;
    char* file1 = argv[1];
    char file2[] = "./temp.txt";
    if((f1 = open(file1, O_RDWR)) == -1) error("Error open file %s", file1);
    if((f2 = open(file2, O_RDWR|O_CREAT)) == -1) error("Error open file %s", file2);
    char buf[1024];
    while((n = read(f1,buf,4)) > 0){
        write(f2,buf,n); write(f2,buf,n);
    }
    remove(file1);
    rename(file2,file1);
    close(f1); close(f2);
    return 0;
}

