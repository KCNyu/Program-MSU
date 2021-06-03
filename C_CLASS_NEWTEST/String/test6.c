/*************************************************************************
	> File Name: test6.c
	> Author: 
	> Mail: 
	> Created Time: Fri 25 Oct 2019 10:40:54 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    char s1[100];
    scanf("%s",s1);
    
    char s2[100];

    int i = 0;
    while(s1[i] != '\0'){
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';

    puts(s2);
    return 0;
}
