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
#include <sys/mman.h>

void fetchPid(int* ret_pid, pid_t ret, const int size){
    for(int i = 0; i < size; i++){
        if(ret_pid[i] == ret){
            ret_pid[i] = 0;
        }
    }
}
int getFirstFailPid(int* ret_pid, const int size){
    pid_t failed = -1;
    for(int i = 0; i < size; i++){
        if(ret_pid[i] != 0 && ret_pid[i] != -1){
            failed = ret_pid[i];
            ret_pid[i] = -1; // kill by SIGTERM
            return failed;
        }
    }
    return failed;
}
int main(int argc, char *argv[])
{
    int i;
    int *ret_pid; // save the pid and the reult of pid
                         // 0 means success
                         // >0 means pid which has no complete
                         // -1 initial number or pid killed by SIGTERM
    clock_t start, end;
    bool flag = false;
    int failed;

    ret_pid = (int*)mmap(NULL,sizeof(int)*(argc-1),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    // Create an anonymous mapping area to store the pid
    pid_t pid, wpid;
    // this is child
    for(i = 1; i < argc; i++){
        pid = fork();
        if(pid == 0){
            int child_pid = getpid();
            // close all child proccess read and write of pipe
            ret_pid[i-1] = child_pid;
            printf("taskname: %8s taskid: %d\n",argv[i],child_pid);
            execlp(argv[i],argv[i],NULL);
        }
    }
    // this is parent
    if(i == argc){
        start = clock();

        while((wpid = waitpid(-1,NULL,WNOHANG)) != -1){
            if(wpid > 0){
                printf("pid = %d done!\n",wpid);
                fetchPid(ret_pid,wpid,argc-1);
            }
            else if(wpid == 0){

                end = clock();
                double time = (double)(end - start) / CLOCKS_PER_SEC;

                if(!flag){
                    if(time > 5){
                        while((failed = getFirstFailPid(ret_pid,argc-1)) != -1){
                            kill((pid_t)failed, SIGTERM); // send SIGTERM to the pid which has no return
                            printf("i have sent SIGTERM to %d\n",failed);
                            //printf("i have sent SIGTERM to all child proccess\n");
                        }
                        flag = true;
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
