/*================================================================
* Filename:Append_9.c
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
    int f, n;
    if((f = open(argv[1], O_RDWR|O_APPEND|O_CREAT)) == -1) error("Error open file %s", argv[1]);
    char buf;
    write(f,"1234",4);
    return 0;
}
