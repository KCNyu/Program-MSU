/*================================================================
* Filename:Execl_lm_execl_1.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 01:05:03 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    int p, status;
    p = fork();
    if(p == 0){
        execlp("gcc","gcc","1.c","-o","1.exe","-lm",NULL);
        perror("exec");
        return 1;
    }
    else{
        wait(&status);
        if(WIFEXITED(status)){
            execl("./1.exe","1.exe",NULL);
        }
        return 1;
    }
    return 0;
}
