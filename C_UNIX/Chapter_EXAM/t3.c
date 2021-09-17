/*================================================================
* Filename:t2.c
* Author: KCN_yu
* Createtime:Sat 11 Sep 2021 09:22:41 AM CST
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
#include <stdint.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1){
        perror("open file error");
    }
    uint32_t num, sum = 0;
    double avg, count = 0;
    int n;
    while((n  = read(fd,&num,sizeof(uint32_t))) != 0){
        sum += num;
        count++;
    }
    avg = sum/count;
    write(STDOUT_FILENO,&avg,sizeof(double));
    return 0;
}
