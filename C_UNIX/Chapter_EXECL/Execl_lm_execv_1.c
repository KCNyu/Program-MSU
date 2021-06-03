/*================================================================
* Filename:Execl_lm_execv_1.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 01:10:40 AM CST
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
        char *a[] = {"gcc","1.c","-o","1.exe","-lm",NULL};
        execvp("gcc",a);
        perror("exec");
        return 1;
    }
    else{
        wait(&status);
        if(WIFEXITED(status)){
            char *b[] = {"1.exe",NULL};
            execv("./1.exe",b);
        }
        return 1;
    }
    return 0;
}
