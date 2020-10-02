/*================================================================
* Filename:Stat_size.c
* Author: KCN_yu
* Createtime:Tue 29 Sep 2020 06:44:47 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    struct stat sb;;
    int ret;
    if(argc < 2){
        fprintf(stderr,"usage:%s<file>\n",argv[1]);
        return 1;
    }
    ret = lstat(argv[1],&sb);
    if(ret){
        perror("stat");
        return 1;
    }
    printf("%s is %ld bytes\n",argv[1],sb.st_size);
    int temp = sb.st_mode;
    if((temp & S_IFLNK) == S_IFLNK) printf("%s is symbolic link\n",argv[1]);
    else printf("%s is hard link\n",argv[1]);
    //printf("%s is %d\n",argv[1],(sb.st_mode & S_IFLNK) == S_IFLNK);
    return 0;
}

