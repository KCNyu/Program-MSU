/*************************************************************************
	> File Name: test18.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 01:28:25 PM CST
 ************************************************************************/

#include<stdio.h>
int try_to_change_it(int);
int main()
{
    int i = 4, j;
    j = try_to_change_it(i);
    printf("i = %d, j = %d\n",i,j);
    return 0;
}
int try_to_change_it(int k)
{
    printf("k1 = %d\n",k);
    k += 33;
    printf("k2 = %d\n",k);
    return k;
}
