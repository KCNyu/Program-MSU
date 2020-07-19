/*************************************************************************
	> File Name: test19.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 01:32:33 PM CST
 ************************************************************************/

#include<stdio.h>
void compare(int, int *);
int main()
{
    int i = 4, j = 5;
    compare(i, &j);
    printf("i = %d, j = %d\n",i,j);
    return 0;
}
void compare(int k, int *m){
    printf("k1 = %d, *m1 = %d\n",k,*m);
    k++;
    (*m)++;
    printf("k2 = %d, *m2 = %d\n",k,*m);
}
