/*************************************************************************
	> File Name: test44.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Nov 2019 05:02:32 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    int mas[1];
    FILE *fp = fopen(argv[1],"r");
    while(fread(mas,sizeof(mas[0]),1,fp)){
        printf("%d\n",mas[0]);
    }
    return 0;
}
