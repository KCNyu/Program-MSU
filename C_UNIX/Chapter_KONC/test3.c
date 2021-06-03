/*================================================================
* Filename:test3.c
* Author: KCN_yu
* Createtime:Tue 17 Nov 2020 10:07:26 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    char d;
    d = '1';
    if(fork() == 0){
        write(1,&d,1);
    }
    else{
        int status;
        wait(&status);
        d = '2';
        write(1,&d,1);
    }
    return 0;
}
