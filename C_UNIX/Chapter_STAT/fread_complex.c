/*================================================================
* Filename:fread_complex.c
* Author: KCN_yu
* Createtime:Mon 05 Oct 2020 03:33:11 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int f = open(argv[1],O_RDONLY);
    double buf[2];
    int n;
    while((n = read(f,buf,sizeof(double)*2)) > 0) printf("%f+%lfI\n",buf[0],buf[1]);
    close(f);
    return 0;
}