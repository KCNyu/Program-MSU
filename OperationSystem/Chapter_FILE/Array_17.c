/*================================================================
* Filename:Array_17.c
* Author: KCN_yu
* Createtime:Tue 29 Sep 2020 12:43:17 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <complex.h>

int main(int argc, char *argv[])
{
    int f_input1 = open("17_input1.txt",O_RDWR|O_CREAT);
    int f_input2 = open("17_input2.txt",O_RDWR|O_CREAT);
    int f_output = open(argv[1],O_RDWR|O_CREAT);
    double buf1, buf2;

    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        buf1 = (double)(rand()%1000)/(rand()%100);
        write(f_input1,&buf1,sizeof(double));
        printf("buf1 = %lf\n",buf1);
        buf2 = (double)(rand()%1000)/(rand()%100);
        write(f_input2,&buf2,sizeof(double));
        printf("buf2 = %lf\n",buf2);
    }

    lseek(f_input1,0,SEEK_SET);
    lseek(f_input2,0,SEEK_SET);

    int n1, n2;
    complex double buf3;
    while((n1 = read(f_input1,&buf1,sizeof(double))) > 0 && ((n2 = read(f_input2,&buf2,sizeof(double)))) > 0){
        complex double buf3 = buf1 + buf2 * _Complex_I;
        write(f_output,&buf3,sizeof(complex double));
    }

    lseek(f_output,0,SEEK_SET);

    int n3;
    while((n3 = read(f_output,&buf3,sizeof(complex double))) > 0){
        printf("%lf+%lfI\n",creal(buf3),cimag(buf3));
    }

    close(f_input1);close(f_input2);close(f_output);
}
