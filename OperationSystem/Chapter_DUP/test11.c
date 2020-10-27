/*================================================================
* Filename:test11.c
* Author: KCN_yu
* Createtime:Mon 26 Oct 2020 10:38:21 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <error.h>

int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++){
        int status;
        if(fork() == 0){
            if(execlp(argv[i],argv[i],NULL) < 0){
                fprintf(stderr,"We can not create the program '%s'\n",argv[i]);
                exit(1);
            }
        }
        else{
            wait(&status);
            if(WEXITSTATUS(status) != 1) return 1;
        }
    }
    return 0;
}
