/*================================================================
* Filename:test2.c
* Author: KCN_yu
* Createtime:Tue 17 Nov 2020 02:43:37 PM CST
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
#include <time.h>
int main(int argc, char *argv[])
{
    int i;
    clock_t start, end;
    bool flag = false;

    pid_t pid, wpid;
    // this is child
    for(i = 1; i < argc; i++){
        pid = fork();
        if(pid == 0){
            execlp(argv[i],argv[i],NULL);
        }
    }
    // this is parent
    if(i == argc){
        start = clock();
        while((wpid = waitpid(-1,NULL,WNOHANG)) != -1){
            if(wpid > 0){
                printf("pid = %d done!\n",wpid);
            }
            else if(wpid == 0){
                end = clock();
                double time = (double)(end - start) / CLOCKS_PER_SEC;
                if(!flag){
                    if(time > 5){
                        kill(pid,SIGTERM); // send SIGTERM to the pid which has no return
                        printf("i have sent SIGTERM to %d\n",pid);
                        //printf("i have sent SIGTERM to all child proccess\n");
                        flag = true;
                        continue;
                    }
                }
                else{
                    if(time > 10){
                        kill(0,SIGKILL);
                        //printf("i have sent SIGKILL to %d\n",pid);
                        printf("i have sent SIGKILL to all child proccess\n");
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
