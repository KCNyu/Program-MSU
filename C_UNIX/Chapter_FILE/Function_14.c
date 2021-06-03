/*================================================================
* Filename:Function_1.c
* Author: KCN_yu
* Createtime:Wed 23 Sep 2020 04:48:02 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAX 100

double F(double x){
    return exp(x)*sin(x)*cos(x);
}
int main(int argc, char *argv[])
{
    char *filename = argv[1];
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    double n = atof(argv[4]);
    double h = (b-a)/n;

    int f = open(filename,O_RDWR|O_CREAT);
    double buf;

    for(int i =0; i <= n; i++){
        double xi = a+i*h;
        buf = F(xi);
        write(f,&buf,sizeof(double));
    }
    lseek(f,0,SEEK_SET);
    for(int i = 0; i <= n; i++){
        read(f,&buf,sizeof(double));
        printf("%lf\n",buf);
    }
    return 0;
}

