#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

void error(char *str, char *filename){
        printf(str, filename); exit(-1);
}

int main(int argc,char *argv[]){
        int f1, f2,n;
	char buf, file2[] = "out.txt";
        if((f1 = open(argv[1], O_RDONLY)) == -1 ) printf("Error open file ");
        if((f2 = open(file2, O_CREAT|O_WRONLY|O_TRUNC)) == -1) error("Error open file %s" ,file2);
        while ((n = read(f1, &buf, 1)) > 0) // 调用read，一个一个字符读
                if(write(f2, &buf, n) != n)  error("error write in file %s", file2);
        if(n < 0) printf("error read from file");
        close(f1); close(f2);
       
        return 0;

}