/*************************************************************************
	> File Name: test42.c
	> Author: 
	> Mail: 
	> Created Time: Mon 25 Nov 2019 06:35:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 5
void Transpose_matrix(int (*A)[N]){
    for(int i = 0; i < N-1; i++){
        for(int j = i+1; j < N; j++){
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}
void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void Exchange(int (*A)[N]){
    for(int i = 0; i < N; i++){
        Swap(&A[i][N-1-i],&A[i][i]);
    }
}
void Input_rand_matrix(int (*A)[N]){
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            A[i][j] = rand()%50;
}
void Print_matrix(int (*A)[N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    srand(time(NULL));
    int A[N][N];
    Input_rand_matrix(A);
    Print_matrix(A);
    printf("\n");
    //Transpose_matrix(A);
    Exchange(A);
    Print_matrix(A);
    return 0;
}
