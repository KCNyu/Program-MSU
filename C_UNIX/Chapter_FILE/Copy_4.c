/*================================================================
* Filename:Copy_4.c
* Author: KCN_yu
* Createtime:Tue 22 Sep 2020 10:57:17 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    char buf;
    int n;
    while((n = read(0,&buf,1)) > 0) write(1,&buf,n);
    return 0;
}
