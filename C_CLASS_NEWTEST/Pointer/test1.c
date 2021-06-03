/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Oct 2019 08:14:24 PM CST
 ************************************************************************/

#include<stdio.h>
void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
int main()
{
    int a = 1,b = 2;
    printf("a = %d\nb = %d\n",a,b);
    swap(&a,&b);
    printf("a = %d\nb = %d\n",a,b);
    return 0;
}
