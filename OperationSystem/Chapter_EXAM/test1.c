/*================================================================
* Filename:test1.c
* Author: KCN_yu
* Createtime:Tue 17 Nov 2020 01:59:15 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <wait.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
/*
#define MAX 128

char cmd[MAX][MAX];
int cmd_count;
char space[2] =  " ";

void Input_command(){
    char* input = (char*)calloc(MAX,sizeof(char));
    char** cmd_tmp = (char**)calloc(sizeof(char*),MAX);
    if(fgets(input,MAX,stdin) != NULL){
        cmd_tmp[cmd_count++] = strtok(input,space);
        while((cmd_tmp[cmd_count] = strtok(NULL,space)) != NULL) cmd_count++;
        cmd_tmp[cmd_count-1][strlen(cmd_tmp[cmd_count-1])-1] = '\0';
    }
    for(int i = 0; i < cmd_count; i++) strcpy(cmd[i],cmd_tmp[i]);
}
*/

int main(int argc, char *argv[])
{
    int fd_pipe[2];
    pipe(fd_pipe);
    int fd;
    if(fork() == 0){
        if(fork() == 0){
            if(fork() == 0){
                dup2(fd_pipe[1],STDOUT_FILENO);
                //close(fd_pipe[1]);close(fd_pipe[0]);
                execlp(argv[1],argv[1],argv[2],NULL);
                exit(0);
            }
            else{
                int status;
                wait(&status);
                dup2(fd_pipe[1],STDOUT_FILENO);
                //close(fd_pipe[1]);close(fd_pipe[0]);
                execlp(argv[3],argv[3],NULL);
                exit(0);
            }
        }
        else{
            //int status;
            //wait(&status);
            dup2(fd_pipe[0],STDIN_FILENO);
            close(fd_pipe[1]);close(fd_pipe[0]);
            fd = open("log",O_WRONLY|O_APPEND|O_CREAT);
            dup2(fd,STDOUT_FILENO);
            execlp(argv[4],argv[4],NULL);
            exit(0);
        }
    }
    else{
        int status;
        wait(&status);
    }
    return 0;
}
