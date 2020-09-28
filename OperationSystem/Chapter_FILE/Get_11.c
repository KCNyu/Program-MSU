/*================================================================
* Filename:Get_11.c
* Author: KCN_yu
* Createtime:Tue 22 Sep 2020 11:30:52 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX 1024

void error(char* str, char* filename){
    printf(str,filename); exit(-1);
}
char* Get(char* f, int n, int pos){
    char *result = (char*)malloc(sizeof(char)*MAX);
    int f1 = open(f,O_RDONLY);
    lseek(f1,pos,SEEK_CUR);
    int count, i = 0;
    char buf;
    while(((count = read(f1,&buf,1)) > 0) && i < n) result[i++] = buf;
    close(f1);
    return result;
}
int main(int argc, char *argv[]){
    printf("%s\n",Get(argv[1],5,2));
}
