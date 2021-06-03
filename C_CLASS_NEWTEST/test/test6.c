/*************************************************************************
	> File Name: test6.c
	> Author: 
	> Mail: 
	> Created Time: Sat 12 Oct 2019 09:48:17 AM CST
 ************************************************************************/

#include<stdio.h>
#define N 100
int main(){
    char A[N],i;
    scanf("%s",A);
    int n = 0;
    while(A[n] != '\0'){
        n++;
    }
    for(i = 0; i < n-1; i++){
        if(A[i] == A[i+1]){
            printf("yes\n");
            return 0;
        }
    }
    printf("no\n");
    return 0;
}
