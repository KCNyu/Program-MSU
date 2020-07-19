/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Oct 2019 08:47:18 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    char s1[100];
    scanf("%s",s1);
    int i = 0;
    while(s1[i] != '\0'){
        if(s1[i] >= 'A' && s1[i] <= 'Z'){
            s1[i] = s1[i] + 32;
        }
        i++;
    }
    puts(s1);
    return 0;
}
