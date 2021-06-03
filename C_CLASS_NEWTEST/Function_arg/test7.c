/*************************************************************************
	> File Name: test7.c
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Oct 2019 10:35:26 PM CST
 ************************************************************************/

#include<stdio.h>
int Factorial(int n){
    if(n == 0 || n == 1)
        return 1;
    else
        return Factorial(n-1)*n;
}
int Fibonacci(int n){
    if(n == 1 || n == 2)
        return 1;
    else
        return Fibonacci(n-1) + Fibonacci(n-2);
}
int main()
{
    int n;
    scanf("%d",&n);
    printf("n! = %d\nFibonacci(n) = %d\n",Factorial(n),Fibonacci(n));
    return 0;
}
