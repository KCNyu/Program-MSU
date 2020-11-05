/*================================================================
* Filename:main.c
* Author: KCN_yu
* Createtime:Thu 05 Nov 2020 10:46:46 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdbool.h>
#include <string.h>

#define MAX 256
const char space[2] = " ";

int main(int argc, char *argv[])
{
    while(1){
        int status;

        if(fork() == 0){
            printf("$");

            int i = 0;
            char *input = (char*)calloc(MAX,sizeof(char));
            char** cmd = (char**)calloc(MAX,sizeof(char));

            if(fgets(input,MAX,stdin) != NULL){
                cmd[i++] = strtok(input,space);
                while((cmd[i] = strtok(NULL,space)) != NULL) i++;
                cmd[i-1][strlen(cmd[i-1])-1] = '\0';
                if(execvp(cmd[0],cmd) < 0){
                        fprintf(stderr,"%s: command not found\n",cmd[0]);
                        exit(1);
                }
            }
        }
        else{
            wait(&status);
            if(WEXITSTATUS(status)) continue;
        }
    }
    return 0;
}
