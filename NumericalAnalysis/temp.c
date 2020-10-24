/*================================================================
* Filename:temp.c
* Author: KCN_yu
* Createtime:Thu 22 Oct 2020 10:49:36 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 256

double f(double x, double y){
    return y*0.5 + x;
}
double y(double i){
    if(i == 0) return 0;
    double temp = y(i-1);
    double k1 = f(i-1,temp);
    double k2 = f(i-1+0.5,temp+k1*0.5);
    double k3 = f(i-1+0.5,temp+k2*0.5);
    double k4 = f(i-1+1,temp+k3);
    return (k1+2*k2+2*k3+k4)/6+temp;
}
double y_t(int i){
    double Y[MAX] = {0} ;
    //for(int a = 0; a <= i; a++) Y[a] = 0;
    if(i == 0) return Y[0];
    for(int a = 1; a <= i; a++){
        double k1 = f(a-1.0,Y[a-1]);
        double k2 = f(a-1.0+0.5,Y[a-1]+k1*0.5);
        double k3 = f(a-1.0+0.5,Y[a-1]+k2*0.5);
        double k4 = f(a-1.0+1,Y[a-1]+k3);
        Y[a] = (k1+2*k2+2*k3+k4)/6.0+Y[a-1];
    }
    return Y[i];
}
int main(int argc, char *argv[])
{
    int i = 3;
    printf("y%d = %lf\n",i,y(i));
    printf("y%d = %lf\n",i,y_t(i));
    return 0;
}
