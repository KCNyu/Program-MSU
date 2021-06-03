/*************************************************************************
	> File Name: test24.c
	> Author: 
	> Mail: 
	> Created Time: Sun 17 Nov 2019 10:35:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 5
void Input_rand_matrix(int (*A)[N]){
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            A[i][j] = rand()%5;
}
void Print_matrix(int (*A)[N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }   
}
int Multiply_vector(int *A, int *B){
    int S = 0;
    for(int i = 0; i < N; i++)
        S += A[i] * B[i];
    return S;
}
void Transpose_matrix(int (*A)[N]){
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}
void Multiply_matrix(int (*A)[N], int (*B)[N], int (*C)[N]){
    Transpose_matrix(B);
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            C[i][j] = Multiply_vector(*(A+i),*(B+j));
}
int main()
{
    srand(time(NULL));
    int A[N][N],B[N][N],C[N][N];
    Input_rand_matrix(A);
    Input_rand_matrix(B);
    Print_matrix(A);
    printf("\n");
    Print_matrix(B);
    printf("\n");
    Multiply_matrix(A,B,C);
    Print_matrix(C);
    return 0;
}
