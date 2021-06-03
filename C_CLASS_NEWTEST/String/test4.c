/*************************************************************************
	> File Name: test4.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Oct 2019 09:16:20 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    printf("input s:");
    char s[100];
    scanf("%s",s);

    getchar();

    printf("input c:");
    char c;
    scanf("%c",&c);

    int length = 0;
    while(s[length] != '\0'){
        length++;
    }
    int i,j;
    for(i = 0; i < length; i++){
        if(s[i] == c){
            for(j = i; j < length; j++){
                s[j] = s[j+1];
            }
            length--;
            i--;
        }
    }
    puts(s);
    return 0;
}
