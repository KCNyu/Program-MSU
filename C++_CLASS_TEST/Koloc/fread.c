/*================================================================
* Filename:fread.c
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 06:46:42 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float mas[1];
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("ERROR!\n");
        return 0;
    }
    while(fread(mas,sizeof(float),1,fp))
        printf("%f\n",mas[0]);
    return 0;
}
