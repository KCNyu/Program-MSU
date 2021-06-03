/*================================================================
* Filename:Chown_group.c
* Author: KCN_yu
* Createtime:Mon 12 Oct 2020 06:39:40 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <error.h>

int main(int argc, char *argv[])
{
    struct group *gr;
    int ret;
    gr = getgrnam("usrivan");
    if(!gr){
        perror("getgrname");
        return 1;
    }
    ret = chown("Hello.c",-1,gr->gr_gid);
    if(ret){
        perror("chown");
        return 0;
    }
}
