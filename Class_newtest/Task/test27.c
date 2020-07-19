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
void Input_rand_vector(int *A){
    for(int i = 0; i < N; i++)
        A[i] = rand()%5;
}
void Print_matrix(int (*A)[N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }   
}
void Print_vector(int *A){
    for(int i = 0; i < N; i++)
        printf("%3d ",A[i]);
    printf("\n");
}
int Multiply_vector(int *A, int *B){
    int S = 0;
    for(int i = 0; i < N; i++)
        S += A[i] * B[i];
    return S;
}
void Multiply_vector_matrix(int (*A)[N], int *B, int *C){
    for(int i = 0; i < N; i++)
        C[i] = Multiply_vector(*(A+i),B);
}
int main()
{
    srand(time(NULL));
    int A[N][N],B[N],C[N];
    Input_rand_matrix(A);
    Input_rand_vector(B);
    Print_matrix(A);
    printf("\n");
    Print_vector(B);
    printf("\n");
    Multiply_vector_matrix(A,B,C);
    Print_vector(C);
    return 0;
}
