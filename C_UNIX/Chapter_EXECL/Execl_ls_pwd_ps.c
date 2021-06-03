/*================================================================
* Filename:Execl_ls_pwd_ps.c
* Author: KCN_yu
* Createtime:Mon 19 Oct 2020 06:42:40 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid;
    if((pid = fork()) == 0){
        pid = fork();
        if(pid == 0) execlp("ls","ls","-l",NULL);
        if(pid > 0) execlp("ps","ps",NULL);
    }
    if(pid > 0) execlp("pwd","pwd",NULL);
    return 0;
}
