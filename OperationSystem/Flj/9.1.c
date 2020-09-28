#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

void error(char *str, char *filename){
        printf(str, filename); exit(-1);
}

int main(int argc, char* argv[]){
        int f1, f2,n;
        char buf,file2 = *++argv;

        f2 = open(file2, O_CREAT|O_WRONLY|O_TRUNC|O_APPEND);
        while ((n = read(0, &buf, 1)) > 0) // 调用read，一个一个字符读
                write(f2, &buf, n);
        if(n < 0) printf("error read from file");
        close(f2);

        return 0;

}
