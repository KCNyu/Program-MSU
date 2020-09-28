#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>


int main(){
        int f1, f2,n;
        char buf;
        while ((n = read(0, &buf, 1)) > 0) // 调用read，一个一个字符读
                if(write(1, &buf, n) != n)  printf("error write");
        if(n < 0) printf("error read from file ");

        return 0;

}
