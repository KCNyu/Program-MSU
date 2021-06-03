/*************************************************************************
	> File Name: Fibonacci.c
	> Author: 
	> Mail: 
	> Created Time: Tue 08 Oct 2019 10:34:47 PM CST
 ************************************************************************/

#include<stdio.h>
int Fibonacci(int n)
{
    if(n <= 2)
    return 1;
    else
    return Fibonacci(n-1)+Fibonacci(n-2);
}
const int NF = 12;
void ArrFint(int ArrF[])
{
    int i;
    for(i = 0;i < NF; i++)
    ArrF[i] = -1;
}
int FactArr(int n,int ArrF[])
{
    if(n <= 1)
    return 1;
    int T;
    T = ArrF[n];
    if(T >= 0)
    return T;
    T = FactArr(n-1,ArrF)*n;
    ArrF[n] = T;
    return T;
}
void PrintArray(int A[],int n)
{
    int i;
    for(i = 0; i < n; i++)
    printf("%d ",A[i]);
    printf("\n");
}
int Ack(int m,int n)
{
    if(m == 0)
    return n+1;

    if(n == 0)
    return Ack(m-1,1);

    return Ack(m-1,Ack(m,n-1));
}
const int M = 3;
const int N = 33000;
void ArrInit(int Arr[][])
{
    int i,j;
    for(j = 0; j <= N; j++)
    Arr[0][j] = j+1;
    for(i = 0; i <= M; i++)
        for(j = 0; j <= N; j++)
            Arr[i][j] = -1;
}

int main()
{
    int n,m,ArrF[NF];
    scanf("%d",&n);
    printf("Fibonacci(%d) = %d\n",n,Fibonacci(n));
    ArrFint(ArrF);
    printf("%d! = %d\n",n,FactArr(n,ArrF));
    scanf("%d%d",&m,&n);
    int Arr[M+1][N+1];
    printf("Ack(%d,%d) = %d\n",m,n,Ack(m,n));
}
