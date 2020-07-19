/*************************************************************************
	> File Name: test34.c
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Nov 2019 11:30:37 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int c;
    FILE *fp = fopen("myfile","w");
    while((c = getchar()) != '\n')
        putc(c,fp);
    fclose(fp);
    return 0;
}
