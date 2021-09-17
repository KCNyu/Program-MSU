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

int main(int argc, char *argv[])
{
    int fd_pipe[2];
    pipe(fd_pipe);
    if(fork() == 0){
        dup2(fd_pipe[1],STDOUT_FILENO);
        close(fd_pipe[0]);close(fd_pipe[1]);
        //execlp(argv[1],argv[1],NULL);
        execlp("ls","ls",NULL);
        exit(0);
    }
    else{
        int status;
        wait(&status);

        //execlp(argv[3],argv[3],NULL);
        if(WIFEXITED(status)){
            dup2(fd_pipe[0],STDIN_FILENO);
            close(fd_pipe[0]);close(fd_pipe[1]);
            execlp("grep","grep",".txt",NULL);
        }
        exit(0);
    }
    return 0;
}
