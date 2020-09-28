/*================================================================
* Filename:Array_16.c
* Author: KCN_yu
* Createtime:Tue 29 Sep 2020 12:37:50 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int f_input = open("16_input.txt",O_RDWR|O_CREAT);
    int f_output = open(argv[1],O_RDWR|O_CREAT);
    int buf;
    for(int i = 0; i < 10; i++){
        buf = rand()%20;
        write(f_input,&buf,sizeof(int));
        printf("buf = %d\n",buf);
    }

    int n;
    lseek(f_input,0,SEEK_SET);
    while((n = read(f_input,&buf,sizeof(int))) > 0){
        buf = buf*buf;
        write(f_output,&buf,n);
    }
    close(f_input);close(f_output);

    return 0;
}
