/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 08:09:35 AM CST
 ************************************************************************/

#include<stdio.h>
int Prime(int p){
    int i;
    if(p <= 1){
        return 0;
    }
    for(i = 2; i < p; i++){
        if(p%i == 0){
            return 0;
        }
    }
    return p;
}
int main()
{
    int i,n,p;
    scanf("%d",&n);
    for(i = 2; i <= n; i++){
        p = Prime(i);
        if(p != 0)
            printf("%d ",p);
    }
    printf("\n");

    return 0;
}
