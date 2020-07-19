/*************************************************************************
	> File Name: test38.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 10:08:08 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
void Print_max(FILE *fp){
    int max_row = 0,max_len = 0,row_len = 0,row_num = 0;
    _Bool flag = true;
    char c;
    while((c = fgetc(fp)) != EOF){
        row_len++;
        if(c == '\n'){
            if(row_len > max_len){
                max_len = row_len;
                max_row = row_num;
            }
            row_num++;
            row_len = 0;
        }
    }
    rewind(fp);
    row_num = 0;
    while((c = fgetc(fp)) != EOF){
        if(c == '\n')
            row_num++;
        if(row_num == max_row){
            if(flag){
                flag = false;
                continue;
            }
            printf("%c",c);
        }
    }
    printf("\n");
    fclose(fp);
}
int main(int argc, char *argv[])
{ 
    FILE *fp = fopen(argv[1],"r");
    Print_max(fp);
    fclose(fp);
    return 0;
}
