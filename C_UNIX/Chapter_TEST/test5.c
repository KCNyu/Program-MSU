/*================================================================
* Filename:test5.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 07:15:55 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <error.h>

int main(int argc, char *argv[])
{
    int f1, f2, n;
    if((f1 = open(argv[1], O_RDWR|O_CREAT)) == -1) perror("Error open file");
    if((f2 = open(argv[2], O_RDWR|O_APPEND|O_CREAT)) == -1) perror("Error open File");
    char buf;
    while((n = read(f1,&buf,1)) > 0) write(f2,&buf,n);
    close(f1); close(f2);
    struct passwd *pw;
    int ret;
    pw = getpwnam("Stud");
    if(!pw){
        perror("getpwname");
        return 1;
    }
    ret = chown(argv[2],pw->pw_uid,-1);
    if(ret){
        perror("chown");
        return 0;
    }
    return 0;
}
