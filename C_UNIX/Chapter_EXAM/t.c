/*================================================================
* Filename:t.c
* Author: KCN_yu
* Createtime:Mon 31 May 2021 07:09:01 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void SigHandlr(int s){
    printf("world!\n");
}
int main(int argc, char *argv[])
{
    signal(SIGALRM,SigHandlr);
    alarm(1);
    sleep(10);
    printf("hello\n");
    return 0;
}
