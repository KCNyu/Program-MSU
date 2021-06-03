/*================================================================
* Filename:fread_matrix.c
* Author: KCN_yu
* Createtime:Sat 10 Oct 2020 06:39:42 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define col 10
#define row 10

int main(int argc, char *argv[])
{
    int f = open(argv[1],O_RDONLY);
    int buf[col];
    int n;
    while((n = read(f,buf,sizeof(int)*col)) > 0){
        for(int i = 0; i < col; i++) printf("%3d ", buf[i]);
        putchar('\n');
    }
    close(f);
    return 0;
}

