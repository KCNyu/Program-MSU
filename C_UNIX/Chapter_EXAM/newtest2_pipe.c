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
#include <string.h>
typedef struct {
    pid_t pid;
    // save the pid and the reult of pid
    int status;
    // 0 means success or success killed by SIGTERM
    // -1 initial number
    // 1 have been sent SIGTERM
} process;

void fetchPid(process* ret_pid, pid_t ret, const int size){
    for(int i = 0; i < size; i++){
        if(ret_pid[i].pid == ret){
            ret_pid[i].status = 0;
            return;
        }
    }
}
int getFirstFailPid(process* ret_pid, const int size){
    pid_t failed = -1;
    for(int i = 0; i < size; i++){
        if(ret_pid[i].status != 0 && ret_pid[i].status != 1)
        {
            failed = ret_pid[i].pid;
            ret_pid[i].status = 1;
            return failed;
        }
    }
    return failed;
}
int getKillPid(process* ret_pid, const int size){
    pid_t failed = -1;
    for(int i = 0; i < size; i++){
        if(ret_pid[i].status == 1)
        {
            failed = ret_pid[i].pid;
            ret_pid[i].status = 0;
            return failed;
        }
    }
    return failed;
}
int main(int argc, char *argv[])
{
    int i;
    int fd[2];
    int size = argc-1;
    process ret_pid[size];

    int task = 0;
    clock_t start, end;
    bool flag = false;

    pipe(fd);
    pid_t pid, wpid;
    // this is child
    for(i = 1; i < argc; i++){
        pid = fork();
        if(pid == 0){
            int child_pid = getpid();
            write(fd[1],&child_pid,sizeof(int));
            close(fd[1]); close(fd[0]);
            // close all child proccess read and write of pipe
            printf("taskname: %8s taskid: %d\n",argv[i],child_pid);
            execlp(argv[i],argv[i],NULL);
            return 0;
            // children proccesses complete
        }
    }
    // this is parent
    start = clock();

    int n;
    int tmp_pid;
    close(fd[1]);
    while((n = read(fd[0],&tmp_pid,sizeof(int))) != 0){
        ret_pid[task].pid = tmp_pid;
        ret_pid[task++].status = -1;
    }
    // when all proccesses fd[1] (write) have been closed
    // and don't have any data from pipe
    // then read from pipe will return 0
    close(fd[0]);
    // close pipe read

    while((wpid = waitpid(-1,NULL,WNOHANG)) != -1){
        if(wpid > 0){
            printf("pid = %d done!\n",wpid);
            fetchPid(ret_pid,wpid,size);
        }
        else if(wpid == 0){

            end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            int target;

            if(!flag){
                if(time > 5){
                    while((target = getFirstFailPid(ret_pid,size)) != -1){
                        kill((pid_t)target, SIGTERM); // send SIGTERM to the pid which has no return
                        printf("i have sent SIGTERM to %d\n",target);
                    }
                    flag = true;
                }
            }
            else{
                if(time > 10){
                    while((target = getKillPid(ret_pid,size)) != -1){
                        kill((pid_t)target, SIGKILL); // send SIGKILL to the pid which has no return or killed by SIGTERM
                        printf("i have sent SIGKILL to %d\n",target);
                    }
                }
            }
        }
    }
    return 0;
}
