/*================================================================
* Filename:test4_2.c
* Author: KCN_yu
* Createtime:Sat 24 Oct 2020 11:03:17 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdint.h>
#include <math.h>
#include <wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    long long int num1;
    long long int num2;
    scanf("%lld%lld",&num1,&num2);
    int fd = open("temp.py",O_RDWR|O_CREAT);
    char* buf1 = (char*)malloc(sizeof(char)*33);
    char* buf2 = (char*)malloc(sizeof(char)*33);
    sprintf(buf1,"%lld",num1);
    sprintf(buf2,"%lld",num2);
    write(fd,"print(",6);
    write(fd,buf1,strlen(buf1));
    write(fd,"+",1);
    write(fd,buf2,strlen(buf2));
    write(fd,")",1);
    close(fd);
    int p, status;
    p = fork();
    if(p == 0){
        execlp("python3","python3","temp.py",NULL);
        perror("exec");
        return 1;
    }
    else{
        wait(&status);
        if(WIFEXITED(status)){
            if(unlink("temp.py") == 0) printf("success!\n");
            else perror("remove");
        }
        return 1;
    }
    return 0;
}
