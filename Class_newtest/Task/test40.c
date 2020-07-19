/*************************************************************************
	> File Name: test39.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 11:23:21 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
_Bool Judge(char *s){
    int len = strlen(s),i;
    for(i = 0; *(s+i) == *(s+len-1-i) && i < len/2; i++);
    return i == len/2 ? true : false ;
}
int main(int argc, char *argv[])
{
    char *s = (char *)malloc(sizeof(char)*100);
    int i;
    for(i = 1; i < argc; i++)
        strcat(s,argv[i]);
    puts(s);
    printf("%d\n",Judge(s));
    return 0;
}
