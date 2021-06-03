/*================================================================
* Filename:Copy.c
* Author: KCN_yu
* Createtime:Tue 22 Sep 2020 06:27:54 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

void error(char *str, char*filename){
    printf(str,filename); exit(-1);
}
int main(int argc, char *argv[])
{
    char s = argv[2][0];
    int N = atoi(argv[3]);

    int f1,f2,n;
    char *file1 = argv[1];
    char file2[] = "./temp.txt";
    if((f1 = open(file1, O_RDWR)) == -1) error("Error open file %s", file1);
    if((f2 = open(file2, O_RDWR|O_CREAT)) == -1) error("Error open file %s", file2);
    char buf;

    _Bool flag = true;
    /*
    _Bool flag_first = true;
    while((n = read(f1,&buf,1)) > 0){
        if(s == buf && flag_first){
            flag = false;
            flag_first = false;
            continue;
        }
        if(flag){
            write(f2,&buf,n);
            continue;
        }
        if(!flag) N--;
        if(N == 1) flag = true;
    }
    */
    while((n = read(f1,&buf,1)) > 0){
        if(s == buf && flag){
            lseek(f1,N-1,SEEK_CUR);
            flag = false;
            continue;
        }
        write(f2,&buf,n);
    }
    remove(file1);
    rename(file2,file1);
    close(f1); close(f2);
    return 0;
}

