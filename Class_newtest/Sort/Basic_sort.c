/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Wed 09 Oct 2019 08:10:08 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
void BubbleSort(int A[])
{
    int i,j,tmp;
    for(i = 0; i < N-1; i++)
    {
        for(j = 0; j < N-1-i; j++)
        {
            if(A[j] > A[j+1])
            {
                 tmp = A[j];
                 A[j] = A[j+1];
                 A[j+1] = tmp;
            }
        }
    }
}
void InsertSort(int A[])
{
    int i,j,tmp;
    for(i = 1; i < N; i++)
    {
        tmp = A[i];
        for(j = i-1; j >= 0; j--)
        {
            if(A[j] > tmp)
            {
                A[j+1] = A[j];
                A[j] = tmp;
            }
        }
    }
}
int SearchMax(int A[],int n)
{
    int i,max = A[0],max_index = 0;
    for(i = 0; i < n; i++)
    {
        if(A[i] > max)
        {
            max = A[i];
            max_index = i;
        }
    }
    return max_index;
}
void SelectSort(int A[])
{
    int i,max_index,tmp;
    for(i = N; i > 0; i--)
    {
        max_index = SearchMax(A,i);
        tmp = A[i-1];
        A[i-1] = A[max_index];
        A[max_index] = tmp;
    }
}
void PrintArray(int A[])
{
    int i;
    for(i = 0; i < N; i++)
        printf("%d ",A[i]);
    printf("\n");
}
void InputArray(int A[])
{
    int i;
    for(i = 0; i < N; i++)
        A[i] = rand()%100;
}
int main()
{
    int A[N];
    srand(time(NULL));

    InputArray(A);
    PrintArray(A);
    SelectSort(A);
    PrintArray(A);

    InputArray(A);
    PrintArray(A);
    BubbleSort(A);
    PrintArray(A);

    InputArray(A);
    PrintArray(A);
    InsertSort(A);
    PrintArray(A);
    return 0;
}
