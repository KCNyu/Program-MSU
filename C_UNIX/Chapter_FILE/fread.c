/*================================================================
* Filename:fread.c
* Author: KCN_yu
* Createtime:Tue 29 Sep 2020 12:17:33 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int f = open(argv[1],O_RDONLY);
    int buf;
    int n;
    while((n = read(f,&buf,sizeof(int))) > 0) printf("%d\n",buf);
    close(f);
    return 0;
}
