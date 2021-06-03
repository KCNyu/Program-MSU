/*************************************************************************
	> File Name: test4.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Nov 2019 12:55:57 PM CST
 ************************************************************************/

#include<stdio.h>
int main(){
    char s[100];
    char *ps = s;
    int count = 0;
    do{
        scanf("%c",ps);
        if(*ps == 'a'){
            count++;
        }
        ps++;
    }while(*(ps-1) != '.');
    *ps = '\0';

    printf("%d\n",count);
    return 0;
}
