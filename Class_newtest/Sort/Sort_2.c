/*************************************************************************
	> File Name: Sort_2.c
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Oct 2019 11:05:11 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define M 5
#define N 5
void InputArray(int A[][N])
{
    int i,j;
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            A[i][j] = rand()%100;
        }
    }
}
void PrintArray(int A[][N]){
    int i,j;
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
             printf("%3d ",A[i][j]);
        }
        printf("\n");
    }
}
void SortRow(int A[][N]){
    int i,j,k;
    int tmp;
    for(k = 0; k < M-1; k++){
        for(i = 0; i < N-1; i++){
            for(j = 0; j < N-1-i; j++){
                if(A[k][j] > A[k][j+1]){
                    tmp = A[k][j];
                    A[k][j] = A[k][j+1];
                    A[k][j+1] = tmp;
                }
            }
        }
    }   
}
void SortColumn(int A[][N]){
    int i,j,k;
    int tmp;
    for(k = 0; k < N-1; k++){
        for(i = 0; i < M-1; i++){
            for(j = 0; j < M-1-i; j++){
                if(A[j][k] > A[j+1][k]){
                    tmp = A[j][k];
                    A[j][k] = A[j+1][k];
                    A[j+1][k] = tmp;
                }
            }
        }
    }   
}
int main(){
    int A[M][N];
    int i,j,k,tmp;
    srand(time(NULL));
    InputArray(A);
    PrintArray(A);
    printf("\n");
    SortRow(A);
    SortColumn(A);
    PrintArray(A);
    return 0;
}
