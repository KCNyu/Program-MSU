/*************************************************************************
	> File Name: test5.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Nov 2019 01:32:11 PM CST
 ************************************************************************/

#include<stdio.h>
char str[] = "SSSWILTECH1\1\11W\1WALLMP1";
int main()
{
    int i;
    char c;
    for(i = 2; (c = str[i]) != '\0'; i++){
        switch(str[i]){
            case 'a':putchar('i');continue;
            case '1':break;
            case 1: while((c = str[++i]) != '\1' && c != '\0');
            case 9: putchar('S');
            case 'E': continue;
            case 'L': continue;
            default: putchar(c);
            continue;
        }
        putchar(' ');
    }
    putchar('\n');
    return 0;
}
