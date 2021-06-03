/*================================================================
* Filename:GetPid.c
* Author: KCN_yu
* Createtime:Tue 13 Oct 2020 06:27:58 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    pid_t pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("Pid: %d\n", pid);
    printf("PPid: %d\n", ppid);
    pid_t fpid;
    fpid = fork();
    if(fpid == -1) perror("fork");
    if(fpid == 0){
        pid = getpid();
        ppid = getppid();
        printf("Pid: %d\n", pid);
        printf("PPid: %d\n", ppid);
        printf("i am the son my pid is %d",getpid());
        int fd = open(argv[1],O_RDONLY);
        char buf;
        int count = 0, n;
        while((n = read(fd,&buf,1) > 0)){
            if(buf == 'b') count++;
        }
        printf("count_b = %d\n",count);
    }
    else{
        pid = getpid();
        ppid = getppid();
        printf("Pid: %d\n", pid);
        printf("PPid: %d\n", ppid);
        printf("i am the parent my pid is %d\n",getpid());
        int fd = open(argv[1],O_RDONLY);
        char buf;
        int count = 0, n;
        while((n = read(fd,&buf,1) > 0)){
            if(buf == 'a') count++;
        }
        printf("count_a = %d\n",count);
    }
    return 0;
}

