/*================================================================
* Filename:test2.c
* Author: KCN_yu
* Createtime:Tue 20 Oct 2020 06:23:09 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

    int fres;
    char *fres_name = argv[1];
    if((fres = open(fres_name,O_RDWR|O_CREAT)) == -1) perror("Error open file");

    int File[argc];
    for(int i = 2; i < argc-1; i++)
        if((File[i] = open(argv[i],O_RDONLY)) == -1) perror("Error open file");

    int N = atoi(argv[argc-1]);

    int n;
    char buf;
    struct stat sb;
    for(int i = 2; i < argc-1; i++){
            if(fstat(File[i],&sb) == -1) perror("fstat");
            int FileSize = sb.st_size;
            if(FileSize <= N){
                while((n = read(File[i],&buf,1)) > 0) write(fres,&buf,n);
                remove(argv[i]);
            }
        }
    for(int i = 2; i < argc; i++) close(File[i]);
    close(fres);
    return 0;
}
