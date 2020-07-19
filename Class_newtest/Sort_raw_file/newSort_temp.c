/*************************************************************************
	> File Name: Sort_temp.c
	> Author: 
	> Mail: 
	> Created Time: Fri 29 Nov 2019 12:15:49 PM CST
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 4096
void Print(int *A){
    for(int i = 0; i < N; i++)
        printf("%d ",A[i]);
    printf("\n");
}
void Rand(int *A){
    srand(time(NULL));
    for(int i = 0; i < N; i++)
        A[i] = rand()%10000;
}
void Swap(int *A, int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
void Sort(int *A, int start, int end){
    for(int i = start; i < end-1; i++){
        for(int j = start; j < end-1; j++){
            if(A[j] > A[j+1]){
                Swap(A,j,j+1);
            }
        }
    }
}
void InsertSort(int *A, int start, int end){
    int i,j,tmp;
    for(i = (start+end)/2; i < end; i++){
        tmp = A[i];
        for(j = i-1; j >= start; j--){
            if(A[j] > tmp){
                A[j+1] = A[j];
                A[j] = tmp;
            }
        }
    }
}
void Binary_sort(int *A, int start, int end){
    int len = end - start;
    int temp = end;
    if(len < 8){
        InsertSort(A,start,end);
        return;
    }
    if(len != 8){
        temp = (start+end)/2;
        Binary_sort(A,start,temp);
        Binary_sort(A,temp,end);
    }
    Sort(A,start,end/2);
    Sort(A,end/2,end);
    //InsertSort(A,start,end);
}
int main()
{
    int A[N];
    Rand(A);
    Binary_sort(A,0,N);
    Print(A);
    return 0;
}
