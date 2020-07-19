/*************************************************************************
	> File Name: test4.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Oct 2019 09:21:30 PM CST
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 1000
int LengthString(char *S){
    int length = 0;
    while(*(S + length) != '\0'){
        length++;
    }
    return length;
}
int main()
{
    char S[N];
    scanf("%s",S);
    printf("length = %d\n",LengthString(S));

    return 0;

}
