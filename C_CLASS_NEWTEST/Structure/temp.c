/*************************************************************************
	> File Name: temp.c
	> Author: 
	> Mail: 
	> Created Time: Fri 08 Nov 2019 09:31:18 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int c[3] = {1,2,3};
    int foo = 1;
    c[--foo] = c[foo++];
    printf("foo = %d\n%d %d %d\n",foo,c[0],c[1],c[2]);
    return 0;
}
