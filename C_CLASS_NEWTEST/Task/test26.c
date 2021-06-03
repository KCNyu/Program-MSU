/*************************************************************************
	> File Name: test24.c
	> Author: 
	> Mail: 
	> Created Time: Sun 17 Nov 2019 10:35:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define M 7
#define N 5
int A_t[N][M];
void Input_rand_matrix(int (*A)[N]){
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            A[i][j] = rand()%100;
}
void Print_matrix(int (*A)[N]){
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            printf("%3d ",A[i][j]);
        }
        printf("\n");
    }   
}
void Transpose_matrix(int (*A)[N]){
/*
    int A_t[N][M];
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            A_t[j][i] = A[i][j];
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%3d ",A_t[i][j]);
        }
        printf("\n");
    }
*/
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%3d ",A[j][i]);
        }
        printf("\n");
    }

}
int main()
{
    srand(time(NULL));
    int A[M][N];
    Input_rand_matrix(A);
    Print_matrix(A);
    printf("\n");
    Transpose_matrix(A);
    return 0;
}
