/*================================================================
* Filename:Stat_modify.c
* Author: KCN_yu
* Createtime:Tue 13 Oct 2020 12:21:44 AM CST
================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat sb;;
    int ret;
    ret = stat("Hello.c",&sb);
    if(ret){
        perror("stat");
        return 1;
    }
    printf("st_mtime = %ld\n", sb.st_mtime);
    struct tm *t = localtime(&(sb.st_mtim));
    printf("localtime:\n");
    printf("%d-%d-%d ", (t->tm_year+1900), (t->tm_mon+1), t->tm_mday);  
    printf("%d:%d:%d\n",t->tm_hour, t->tm_min, t->tm_sec);
    
    return 0;
}
 