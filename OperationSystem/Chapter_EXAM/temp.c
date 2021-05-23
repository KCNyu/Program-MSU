/*================================================================
* Filename:temp.c
* Author: KCN_yu
* Createtime:Tue 17 Nov 2020 03:05:30 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    printf("temp pid = %d\n",getpid());
    while(1){
        sleep(1);
        printf("hello!\n");
    }
    return 0;
}
