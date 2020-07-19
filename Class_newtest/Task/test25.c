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
void Max_min_matrix(int (*A)[N]){
    int max,min;
    printf("min: ");
    for(int i = 0; i < M; i++){
        min = A[i][0];
        for(int j = 0; j < N; j++){
            if(A[i][j] < min)
                min = A[i][j];
        }
        printf("%d ",min);
        if(i == 0)
            max = min;
        if(min > max)
            max = min;
    }
    printf("\nmax: %d\n",max);
}
int main()
{
    srand(time(NULL));
    int A[M][N];
    Input_rand_matrix(A);
    Print_matrix(A);
    Max_min_matrix(A);
    return 0;
}
