/*************************************************************************
	> File Name: test5.c
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Oct 2019 09:58:19 PM CST
 ************************************************************************/

#include<stdio.h>
char getletter(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return c;
    }
    else
        return -1;
}
int main()
{
    char c,d;
    c = getchar();
    d = getletter(c);
    if(d == c)
        printf("%c\n",d);
    else
        printf("%d\n",d);
    return 0;
}
