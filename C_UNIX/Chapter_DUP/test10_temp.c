/*================================================================
* Filename:test10.c
* Author: KCN_yu
* Createtime:Mon 26 Oct 2020 09:41:28 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <error.h>

int i;
void SigHndlr(int s){
    i++;
}
int main(int argc, char *argv[])
{
    for(i = 1; i < argc; i++){
        int status;
        if(fork() == 0){
            if(i != argc-1 && argv[i+1][0] == '-'){
                kill(getppid(),SIGUSR1);
                if(execlp(argv[i],argv[i],argv[i+1],NULL) < 0){
                    fprintf(stderr,"We can not create the program '%s'\n",argv[i]);
                    exit(1);
                }
            }
            else{
                if(execlp(argv[i],argv[i],NULL) < 0){
                    fprintf(stderr,"We can not create the program '%s'\n",argv[i]);
                    exit(1);
                }
            }
        }
        else{
            signal(SIGUSR1,SigHndlr);
            wait(&status);
            if(WEXITSTATUS(status)) return 1;
        }
    }
    return 0;
}
