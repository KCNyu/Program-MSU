/*************************************************************************
	> File Name: test21.c
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Nov 2019 04:41:06 PM CST
 ************************************************************************/

#include<stdio.h>
#define max1(x,y,z)  ((((x)>(y) ? (x):(y)) > ((x)>(z) ? (x):(z))) ? ((x)>(y) ? (x):(y)):((x)>(z) ? (x):(z)))
#define max2(x,y,z) ((x)>(y) ? ((x)>(z) ? (x):(z)) : ((y)>(z) ? (y):(z)))
int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    printf("%d\n",max2(a,b,c));
    return 0;
}
