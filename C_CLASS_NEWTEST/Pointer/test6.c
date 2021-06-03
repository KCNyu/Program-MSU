/*************************************************************************
	> File Name: test6.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Oct 2019 11:04:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10
void Selectsort(int *A){
    int i,j,min,tmp;
    for(i = 0; i < N-1; i++){
        min = i;
        for(j = i+1; j < N; j++){
            if(*(A+j) < *(A+min)){
                min = j;
            }
        }
        if(min != i){
            tmp = *(A+i);
            *(A+i) = *(A+min);
            *(A+min) = tmp;
        }
    }
}
void Insertsort(int *A){
    int i,j,tmp;
    for(i = 1; i < N; i++){
        tmp = *(A+i);
        for(j = i-1; j >= 0 && tmp < *(A+j); j--){
            *(A+j+1) = *(A+j);
        }
        *(A+j+1) = tmp;
    }
}
void Bubblesort(int *A){
    int i,j,tmp;
    for(i = 0; i < N-1; i++){
        for(j = 0; j < N-i-1; j++){
            if(*(A+j) > *(A+j+1)){
                tmp = *(A+j);
                *(A+j) = *(A+j+1);
                *(A+j+1) = tmp;
            }
        }
    }
}
void InputArray(int *A){
    int i;
    for(i = 0; i < N; i++){
        *(A+i) = rand()%100;
    }
}
void PrintArray(int *A){
    int i;
    for(i = 0; i < N; i++){
        printf("%d ",*(A+i));
    }
    printf("\n");
}
int main()
{
    int A[N];
    InputArray(A);
    PrintArray(A);
    Selectsort(A);
    PrintArray(A);
    
    InputArray(A);
    PrintArray(A);
    Insertsort(A);
    PrintArray(A);
    
    InputArray(A);
    PrintArray(A);
    Bubblesort(A);
    PrintArray(A);
    
    return 0;
}
