/*================================================================
* Filename:test2.c
* Author: KCN_yu
* Createtime:Tue 17 Nov 2020 09:58:33 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("abc");
    fflush(stdout);
    fork();
    printf("bcd\n");
    return 0;
}
