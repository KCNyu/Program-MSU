/*================================================================
* Filename:test12.c
* Author: KCN_yu
* Createtime:Tue 27 Oct 2020 06:41:14 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void Alrm(int s){
    printf("\n wait name \n");
    alarm(5);
}
int main(int argc, char *argv[])
{
    char s[80];
    signal(SIGALRM,Alrm);
    alarm(5);
    printf("input name\n");
    while(1){
        printf("name:");
        if(fgets(s,80,stdin) != NULL) break;
    }
    printf("OK!\n");
    return 0;
}

