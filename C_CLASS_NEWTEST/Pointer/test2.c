/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Oct 2019 08:18:40 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10
void InputArray(int *A){
    int *p;
    for(p = A; p < A + N; p++)
        *p = rand()%100;
}
void PrintArray(int *A){
    int *p;
    for(p = A; p < A + N; p++)
        printf("%d ",*p);
    printf("\n");
}
int SearchMax(int *A){
    int *p,max = *A;
    for(p = A + 1; p < A + N; p++){
        if( max < *p)
            max = *p;
    }
    return max;   
}
int main()
{
    int A[N];
    srand(time(NULL));
    InputArray(A);
    PrintArray(A);
    printf("max = %d\n",SearchMax(A));
    return 0;
}
