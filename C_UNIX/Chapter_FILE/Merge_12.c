/*================================================================
* Filename:Merge_12.c
* Author: KCN_yu
* Createtime:Wed 23 Sep 2020 12:31:42 AM CST
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

    int fres;
    char *fres_name = argv[1];
    if((fres = open(fres_name,O_RDWR|O_CREAT)) == -1) error("Error open file %s\n",fres_name);

    int File[argc];
    for(int i = 2; i < argc-1; i++)
        if((File[i] = open(argv[i],O_RDONLY)) == -1) error("Error open file %s\n",argv[i]);

    int N = atoi(argv[argc-1]);

    int n;
    char buf;
    for(int i = 2; i < argc-1; i++){
        int FileSize = lseek(File[i],0,SEEK_END);
        if(FileSize >= N){
            lseek(File[i],0,SEEK_SET);
            while((n = read(File[i],&buf,1)) > 0) write(fres,&buf,n);
        }
    }
    for(int i = 2; i < argc; i++) close(File[i]);
    close(fres);
    return 0;
}
