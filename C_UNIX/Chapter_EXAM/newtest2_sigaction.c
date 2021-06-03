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
#include <unistd.h>
#include <sys/mman.h>
typedef struct {
    pid_t pid;
    // save the pid and the reult of pid
    int status;
    // 0 means success or success killed by SIGTERM
    // -1 initial number
    // 1 have been sent SIGTERM
} process;

bool flag = false;
process *ret_pid;
int size;

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
void SigHandlr(int s){
    alarm(5);
    int target;
    if(!flag){
        while((target = getFirstFailPid(ret_pid,size)) != -1){
            printf("i have sent SIGTERM to %d\n",target);
            kill((pid_t)target, SIGTERM); // send SIGTERM to the pid which has no return
        }
        flag = true;
    }
    else{
        while((target = getKillPid(ret_pid,size)) != -1){
            kill((pid_t)target, SIGKILL); // send SIGKILL to the pid which has no return or killed by SIGTERM
            printf("i have sent SIGKILL to %d\n",target);
        }
    }
}
void Catch_child(int s){
    pid_t wpid;
    int status;
    while((wpid = waitpid(-1,&status,WNOHANG)) != -1){
        if(wpid == 0) break;
        if(WIFEXITED(status)){
            printf("===================\n");
            printf("pid = %d done!\n",wpid);
            printf("===================\n");
        }
        else if(WIFSIGNALED(status)){
            if(WTERMSIG(status) == SIGTERM){
                printf("====================================\n");
                printf("pid = %d killed by signal SIGTERM\n",wpid);
                printf("====================================\n");
            }
        }
        fetchPid(ret_pid,wpid,size);
    }
}
int main(int argc, char *argv[])
{
    int i;
    pid_t pid;
    size = argc-1;

    ret_pid = (process*)mmap(NULL,sizeof(process)*(size),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    // Create an anonymous mapping area to store the pid

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);
    // Temporarily blocked the SIGCHLD signal
    // to prevent the signal from being delivered before the handler function is initialized

    for(i = 1; i < argc; i++){
        pid = fork();
        //this is child
        if(pid == 0){
            int child_pid = getpid();
            ret_pid[i-1].pid = child_pid;
            ret_pid[i-1].status = -1;
            printf("taskname: %8s taskid: %d\n",argv[i],child_pid);
            execlp(argv[i],argv[i],NULL);
            // children proccesses complete
        }
    }

    // this is parent
    signal(SIGALRM,SigHandlr);
    alarm(10);

    struct sigaction act;

    act.sa_handler = Catch_child;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, NULL);
    // create handler function of SIGCHLD

    sigprocmask(SIG_UNBLOCK, &set, NULL);
    // unblock SIGCHLD

    while(1){
        printf("i am parent and working now!\n");
        sleep(1);
    }
    return 0;
}
