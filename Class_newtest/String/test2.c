/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Oct 2019 08:43:56 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    char c[100];
    scanf("%s",c);
    int sum = 0;
    int length = 0;
    while(c[length] != '\0'){
        sum += c[length] - '0';
        length++;
    }
    printf("sum = %d\n",sum);
    return 0;
}
