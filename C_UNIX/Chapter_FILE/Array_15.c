/*================================================================
* Filename:Array_15.c
* Author: KCN_yu
* Createtime:Mon 28 Sep 2020 11:53:31 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int f_input = open("15_input.txt",O_RDWR|O_CREAT);
    int buf;
    for(int i = 0; i < 10; i++){
        buf = rand()%20;
        write(f_input,&buf,sizeof(int));
        printf("buf = %d\n",buf);
    }
    int f_output = open(argv[1],O_RDWR|O_CREAT);
    int N = atoi(argv[2]);

    int n;
    lseek(f_input,0,SEEK_SET);
    while((n = read(f_input,&buf,sizeof(int))) > 0){
        if(buf < N) write(f_output,&buf,n);
    }
    close(f_input);close(f_output);
    return 0;
}
