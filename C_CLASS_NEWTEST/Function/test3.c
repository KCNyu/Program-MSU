/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 08:34:40 AM CST
 ************************************************************************/

#include<stdio.h>
double Formula1(){
    int i;
    double a;
    double sum = 0;
    for(i = 1; i <= 10000; i++){
        a = 1.0/i;
        if(i%2 == 0)
            sum += a*-1;
        else
            sum += a;
    }
    return sum;
}
double Formula2(){
    int i;
    double a;
    double sum = 0;
    for(i = 10000; i >= 1; i--){
        a = 1.0/i;
        if(i%2 == 0)
            sum += a*-1;
        else
            sum += a;
    }
    return sum;
}
double Formula3(){
    int i;
    double a;
    double sum1 = 0,sum2 = 0;
    for(i = 1; i <= 10000; i++){
        a = 1.0/i;
        if(i%2 == 0)
            sum2 += a; 
        else
            sum1 += a;
    }
    double sum = sum1-sum2;
    return sum;
}
double Formula4(){
    int i;
    double a;
    double sum1 = 0,sum2 = 0;
    for(i = 10000; i >= 1; i--){
        a = 1.0/i;
        if(i%2 == 0)
            sum2 += a; 
        else
            sum1 += a;
    }
    double sum = sum1-sum2;
    return sum;
}
int main()
{
    double sum;
    sum = Formula4();
    printf("sum = %lf\n",sum);
    return 0;
}
