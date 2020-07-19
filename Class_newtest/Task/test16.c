/*************************************************************************
	> File Name: test16.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 12:24:16 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int ques(char *s1, char *s2){
    while(*s1 && *s2 && *s1 ++== *s2++);
    return *--s1-*--s2;
}
int main()
{
    char s1[100],s2[100];
    scanf("%s%s",s1,s2);
    printf("%d\n",ques(s1,s2));
    return 0;
}
