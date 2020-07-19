/*************************************************************************
	> File Name: fread.c
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Nov 2019 12:44:21 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    int mas[1];
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("ERROR!\n");
        return 0;
    }
    while(fread(mas,sizeof(int),1,fp))
        printf("%d\n",mas[0]);
    return 0;
}
