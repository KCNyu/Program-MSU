/*************************************************************************
	> File Name: test17.c
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 08:59:51 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int array[2][3] = {{0,1,2},{3,4,5}};
    int (*p)[3] = array;

    printf("*(*p+1): %d\n",*(*p+1));
    printf("array+1 = %p\n",array+1);
    printf("*(*array+1) = %d\n",*(*array+1));
    printf("array[0][1] = %d\n",array[0][1]);
    return 0;
}
