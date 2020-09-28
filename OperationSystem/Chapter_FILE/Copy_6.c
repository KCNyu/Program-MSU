/*================================================================
* Filename:Copy_6.c
* Author: KCN_yu
* Createtime:Tue 22 Sep 2020 11:00:01 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void error(char *str, char*filename){
    printf(str,filename); exit(-1);
}
int main(int argc, char *argv[])
{
    int File[argc];
    for(int i = 1; i < argc; i++)
        if((File[i] = open(argv[i],O_RDONLY)) == -1) error("Error open file %s\n",argv[i]);

    int F;
    char F_name[] = "6.txt";
    if((F = open(F_name,O_RDWR|O_CREAT)) == -1) error("Error open file %s\n",F_name);

    for(int i = 1; i < argc; i++){
        int n;
        char buf;
        while((n = read(File[i],&buf,1)) > 0) write(F,&buf,n);
    }
    for(int i = 1; i < argc; i++) close(File[i]);
    close(F);
    return 0;
}
