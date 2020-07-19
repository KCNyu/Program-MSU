/*************************************************************************
	> File Name: fwrite.c
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Nov 2019 12:33:06 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    int mas[1];
    FILE *fp = fopen(argv[1],"w");
    if(fp == NULL){
        printf("ERROR!\n");
        return 0;
    }
    while(scanf("%d",&mas[0]) == 1)
        fwrite(mas,sizeof(int),sizeof(mas)/sizeof(int),fp);
    fclose(fp);
    return 0;
}
