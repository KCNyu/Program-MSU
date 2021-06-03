/*************************************************************************
	> File Name: test43.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Nov 2019 04:31:26 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    int i;
    int mas[1];
    FILE *fp = fopen(argv[1],"w");
    if(fp == NULL){
        printf("ERROR!\n");
        return 0;
    }
    while(scanf("%d",&i) == 1){
        mas[0] = i;
        fwrite(mas,sizeof(mas[0]),sizeof(mas)/sizeof(mas[0]),fp);
    }
    fclose(fp);
    return 0;
}
