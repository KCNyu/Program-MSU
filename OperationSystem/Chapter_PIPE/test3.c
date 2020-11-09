/*================================================================
* Filename:test3.c
* Author: KCN_yu
* Createtime:Mon 02 Nov 2020 10:55:46 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/prctl.h>

bool Equal(char* str1, char* str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 != len2) return false;
    for(int i = 0; i < len1; i++)
        if(str1[i] != str2[i]) return false;
    return true;
}
void SigHndlr(int s){
    prctl(PR_SET_PDEATHSIG,SIGKILL);
}
int main(int argc, char *argv[])
{
    int Fd[argc];
    int len = strlen(argv[1]);
    int status;
    for(int i = 2; i < argc; i++){
        if(fork() == 0){
            if((Fd[i] = open(argv[i],O_RDONLY)) == -1) perror("Error open file");
            int n;
            char temp[len+1];
            temp[len] = '\0';
            int off_set = 0;
            while((n = read(Fd[i],temp,len)) > 0){
                if(n != len) break;
                puts(temp);
                if(Equal(argv[1],temp)){
                    printf("success! In FILE %s\n",argv[i]);
                    kill(getppid(),SIGUSR1);
                    break;
                    //exit(1);
                }
                else lseek(Fd[i],++off_set,SEEK_SET);
            }
        }
    }
    signal(SIGUSR1,SigHndlr);
    for(int i = 2; i < argc; i++){
        wait(&status);
    }
    /*
    printf("process %d finished\n",pid);
    if(WEXITSTATUS(status)) return 1;
    */
    return 0;
}
