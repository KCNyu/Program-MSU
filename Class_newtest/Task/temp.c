/*************************************************************************
	> File Name: temp.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Nov 2019 09:25:47 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main()
{
    char s[100];
    int i = 0, c;
    while((c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
    printf("%s\n",s);
    return 0;
}
