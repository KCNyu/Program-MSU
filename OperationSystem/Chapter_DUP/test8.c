/*================================================================
* Filename:test8.c
* Author: KCN_yu
* Createtime:Mon 26 Oct 2020 07:16:24 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int count = 1;

void SigHndlr(int s){
    printf("\nI got SIGINT %d time(s)\n",++count);
    printf("\ns = %d\n",s);
    if(count == 5) signal(SIGINT,SIG_DFL);
    else signal(SIGINT, SigHndlr);
}
int main(int argc, char *argv[])
{
    signal(SIGINT,SigHndlr);
    while(1);
    return 0;
}

