/*************************************************************************
	> File Name: test17.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 01:21:28 PM CST
 ************************************************************************/

#include<stdio.h>
/*
void swap1(char &x, char &y){
    char t;
    t = x, x = y, y = t;
}

void swap2(char x, char y){
    char *t;
    t = &x, &x = &y, &y = t;
}
*/
void swap3(char *x, char *y){
    char t;
    t = *x, *x = *y, *y = t;
}
int main()
{
    char a = 'a';
    char b = 'b';
    swap3(&a,&b);
    printf("a = %c\nb = %c\n",a,b);
    return 0;
}
