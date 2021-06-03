/*================================================================
* Filename:Append_10.c
* Author: KCN_yu
* Createtime:Tue 22 Sep 2020 09:46:05 PM CST
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
    if((f1 = open(file1, O_RDWR|O_CREAT)) == -1) error("Error open file %s", file1);
    if((f2 = open(file2, O_RDWR|O_CREAT)) == -1) error("Error open file %s", file2);
    char buf;
    while((n = read(f1,&buf,1)) > 0){
        write(f2,&buf,1);
    }
    lseek(f2,0,SEEK_SET);
    while((n = read(f2,&buf,1)) > 0){
        write(f1,&buf,1);
    }
    remove(file2);
    close(f1);close(f2);
    return 0;
}
