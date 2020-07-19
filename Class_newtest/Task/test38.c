/*************************************************************************
	> File Name: test38.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 10:08:08 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
void Print_max(FILE *fp){
    char text[100][100];
    int i = 0,j = 0;
    int max = 0,max_len = 0;
    char c;
    while((c = fgetc(fp)) != EOF){
        text[i][j++] = c;
        if(c == '\n' || c == ' '){
            if(strlen(text[i]) > max_len){
                max = i;
                max_len = strlen(text[i]);
            }
            text[i++][j] = '\0';
            j = 0;
        }
    }
    printf("%s",text[max]);
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
