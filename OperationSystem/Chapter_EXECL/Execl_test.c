/*================================================================
* Filename:Execl_test.c
* Author: KCN_yu
* Createtime:Mon 19 Oct 2020 07:12:12 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[])
{
    int p, status;
    if(argc < 2) return 1;
    p = fork();
    if(p == 0){
        execlp("gcc","gcc",argv[1],"-o","res",NULL);
        perror("exec");
        return 1;
    }
    else{
        wait(&status);
        printf("%d\n",WIFEXITED(status));
        printf("%d\n",WEXITSTATUS(status));
        if(WIFEXITED(status)){
            printf("work2\n");
            execl("./res","res",NULL);
        }
        return 1;
    }
    return 0;
}
