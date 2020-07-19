/*************************************************************************
	> File Name: test5.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Oct 2019 10:05:44 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define N 1000
void PrintArray(char *s){
    while(*s != '\0'){
        printf("%c",*s);
        s++;
    }
    printf("\n");
}
int main()
{
    char S1[N],S2[N];
    printf("&S1 = %p &S2 = %p\n",S1,S2);
    scanf("%s",S1);
    PrintArray(S1);
    int i = 0;
    char *p;
    p = S2;
    while(*(S1 + i) != '\0'){
        *p = *(S1 + i);
        i++;
        p++;
    }
    *p = '\0';
    PrintArray(S2);
    printf("&p = %p\n",p);
    printf("&S1 = %p &S2 = %p\n",S1,S2);
    return 0;
}
