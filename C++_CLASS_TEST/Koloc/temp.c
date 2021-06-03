/*================================================================
* Filename:temp.c
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 06:26:54 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
int F(float* P, float* Q, int M){
    if(P[M] < 0 && Q[M] < 0) return -1;
    else if(P[M] > 0 && Q[M] > 0) return 1;
    else return 1;
}
int main(int argc, char *argv[])
{
    int N;
    printf("Input N: ");
    scanf("%d",&N);
    float A[N],B[N],X[N];

    float Xmin, Xmax;
    printf("Input Xmin: ");
    scanf("%f",&Xmin);
    printf("Input Xmax: ");
    scanf("%f",&Xmax);
    float D = (Xmax-Xmin)/(N-1);
    for(int i = 0; i < N; i++){
        X[i] = Xmin+i*D;
        A[i] = (X[i]-1.0)*(X[i]+1.0);
        B[i] = (X[i]-2.0)*(X[i]+2.0);
    }
    FILE *fp = fopen("res.txt","w");
    if(fp == NULL){
        printf("ERROR!\n");
        return 0;
    }
    for(int i = 0; i < N; i++){
        fprintf(fp,"%f, %f, %f, %d\n",X[i],A[i],B[i],F(A,B,i));
    }
    fclose(fp);
    return 0;
}
