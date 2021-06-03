/*================================================================
* Filename:Chown_usr.c
* Author: KCN_yu
* Createtime:Mon 12 Oct 2020 07:04:48 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <error.h>

int main(int argc, char *argv[])
{
    struct passwd *pw;
    int ret;
    pw = getpwnam("usrivan");
    if(!pw){
        perror("getpwname");
        return 1;
    }
    ret = chown("Hello.c",pw->pw_uid,-1);
    if(ret){
        perror("chown");
        return 0;
    }
}
