/*************************************************************************
	> File Name: test7.c
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Nov 2019 06:55:36 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n,r = 2,count = 1;
    scanf("%d",&n);
    while(n >= r){
        r <<= 1;
        count++;
    }
    printf("%d\n",count);
    return 0;
}
