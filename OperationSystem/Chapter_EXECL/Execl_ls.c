/*================================================================
* Filename:Execl_ls.c
* Author: KCN_yu
* Createtime:Mon 19 Oct 2020 06:25:40 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid;
    if((pid = fork()) == 0){
        //execl("/bin/ls","ls","-l",(char*)0);
        //execlp("ls","ls","-l",(char*)0);
        char* argv[] = {"ls","-l",NULL};
        //execle("/bin/ls",temp);
        execv("/bin/ls",argv);
        //execvp("ls",argv);
        //execvpe("echo",temp);
        printf("print ls doesn't work\n");
    }
    return 0;
}
