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
    execlp("grep","grep","-r","-n","exec",NULL);
    return 0;
}
