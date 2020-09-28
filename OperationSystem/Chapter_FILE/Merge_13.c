/*================================================================
* Filename:Merge_13.c
* Author: KCN_yu
* Createtime:Wed 23 Sep 2020 12:53:58 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void error(char *str, char*filename){
    printf(str,filename); exit(-1);
}
int main(int argc, char *argv[]){
    int f1, f2, fres;
    char *fres_name = argv[1];
    char *file1 = argv[2];
    char *file2 = argv[3];
    int N = atoi(argv[4]);

    if((fres = open(fres_name, O_RDWR|O_CREAT)) == -1) error("Error open file %s", fres_name);
    if((f1 = open(file1, O_RDONLY)) == -1) error("Error open file %s", file1);
    if((f2 = open(file2, O_RDONLY)) == -1) error("Error open file %s", file2);

    int count = 0;
    int n1 = 1,n2 = 1; char buf;
    while(n1 > 0 || n2 > 0){
            for(int i = 0; i < N; i++){
                if(count%2 == 0 && ((n1 = read(f1,&buf,1)) > 0))
                    write(fres,&buf,n1);
                if(count%2 != 0 && ((n2 = read(f2,&buf,1)) > 0))
                    write(fres,&buf,n2);
                }
        count++;
    }
    close(f1);close(f2);close(fres);
    return 0;
}
