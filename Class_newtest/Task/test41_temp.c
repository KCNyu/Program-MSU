/*************************************************************************
	> File Name: test38.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 10:08:08 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
_Bool Judge(char *s1, char *s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if(len1 != len2)
        return false;
    int i = 0;
    while(*(s1+i) == *(s2+i) && i < len1)
        i++;
    if(i == len1)
        return true;
    else
        return false;
}
int Count_1(FILE *fp){
    char text[100],text_1[100];
    int i = 0;
    int count = 0;
    _Bool flag = true;
    char c;
    while((c = fgetc(fp)) != EOF){
        text[i++] = c;
        if(c == '\n' || c == ' '){
            text[i] = '\0';
            if(flag){
                strcpy(text_1,text);
                flag = false;
            }
            if(Judge(text,text_1))
                count++;
            i = 0;
        }
    }
    fclose(fp);
    return count;
}
int main(int argc, char *argv[])
{ 
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("count = 0\n");
        return 0;
    }
    printf("count = %d\n",Count_1(fp));
    fclose(fp);
    return 0;
}
