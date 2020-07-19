/*************************************************************************
	> File Name: test38.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 10:08:08 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Print_max(FILE *fp){
    char *text = (char*)malloc(sizeof(char)*100);
    char *max = (char*)malloc(sizeof(char)*100);
    int i = 0;
    int max_len = 0;
    char c;
    while((c = fgetc(fp)) != EOF){
        text[i++] = c;
        if(c == '\n'){
            if(strlen(text) > max_len){
                text[i] = '\0';
                strcpy(max,text);
                max_len = strlen(max);
            }
            i = 0;
        }
    }
    printf("%s",max);
    fclose(fp);
}
int main()
{ 
    char filename[100];
    scanf("%s",filename);
    FILE *fp = fopen(filename,"r");
    Print_max(fp);
    fclose(fp);
    return 0;
}
