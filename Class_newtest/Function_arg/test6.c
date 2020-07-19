/*************************************************************************
	> File Name: test6.c
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Oct 2019 10:14:00 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdarg.h>
double Average(int n, ...){
    va_list ap;
    va_start(ap,n);
    double sum = 0.0;
    int i,num;
    for(i = 0; i < n; i++){
        num = va_arg(ap,int);
        sum += num; 
    }
    double avg = sum/n;
    return avg;
}
int main()
{
    double avg = Average(5,1,2,3,4,1);
    printf("%lf\n",avg);
    return 0;
}
