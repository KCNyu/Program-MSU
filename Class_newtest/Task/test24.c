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
void Print_vector(int *A, int n){
    for(int i = 0; i < n; i++)
        printf("%d ",A[i]);
    printf("\n");
}
void Dominates_vector(int *A, int *B, int n){
    int flag = 0;
    for(int i = 0; i < n; i++)
        if(A[i] >= B[i])
            flag++;
    if(flag == n){
        Print_vector(A,n);
        return;
    }
    if(flag == 0){
        Print_vector(B,n);
        return;
    }
    else{
        printf("ERROR!\n");
        return;
    }
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
    
    Dominates_vector(v_x,v_y,n);
    return 0;
}
