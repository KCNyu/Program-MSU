/*================================================================
* Filename:test3.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 06:41:13 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    struct stat sb;;
    if(argc < 2){
            fprintf(stderr,"usage:%s<file>\n",argv[1]);
            return 1;
    }
    stat(argv[1],&sb);
    printf("inode = %lu\n",sb.st_ino);
    printf("st_blocks = %ld\n",sb.st_blocks);
    return 0;
}
