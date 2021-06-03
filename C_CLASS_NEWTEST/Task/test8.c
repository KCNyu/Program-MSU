/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 21 Oct 2019 12:40:10 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int count = 0;
double Myfabs(double n){
    if(n < 0)
        return -n;
    else
        return n;
}
double Mysqrt(double x,double e){
    double a0 = 1,a1;
    do
    {
        a1 = (a0 + x/a0)*0.5;
        count++;
        if(Myfabs(a0 - a1) < e){
            return a1;
        }
        a0 = (a1 + x/a1)*0.5;
        count++;
    }while(Myfabs(a0 - a1) >= e);
   
    return a0;
}
int main()
{
    for(double i = 2; i <= 100; i++){
        printf("%lf^1/2 = %lf\n",i,Mysqrt(i,0.00001));
        printf("count = %d\n",count);
        count = 0;
    }
    return 0;
}
