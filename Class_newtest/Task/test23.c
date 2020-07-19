/*************************************************************************
	> File Name: test23.c
	> Author: 
	> Mail: 
	> Created Time: Sun 17 Nov 2019 09:54:16 PM CST
 ************************************************************************/

#include<stdio.h>
void Input_vector(int *A,int n){
    for(int i = 0; i < n; i++)
        scanf("%d",&A[i]);
}
int Multiply_vector(int *A, int *B, int n){
    int S = 0;
    for(int i = 0; i < n; i++)
        S += A[i] * B[i];
    return S;
}
void Print_vector(int *A, int n){
    for(int i = 0; i < n; i++)
        printf("%d ",A[i]);
    printf("\n");
}
int main()
{
    int n;
    printf("Input n: ");
    scanf("%d",&n);
    int v_x[n], v_y[n];
    printf("Input vector_x: ");
    Input_vector(v_x,n);
    printf("Input vector_y: ");
    Input_vector(v_y,n);
    
    int S = Multiply_vector(v_x,v_y,n);
    Print_vector(v_x,n);
    Print_vector(v_y,n);
    
    printf("S = %d\n",S);
    return 0;
}
