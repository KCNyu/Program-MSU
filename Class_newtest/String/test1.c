/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Oct 2019 08:38:11 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    char s[100];
    int i;
    for(i = 0; i < n ; i++){
        s[i] = 'A' + i;
    }
    puts(s);
    return 0;
}
