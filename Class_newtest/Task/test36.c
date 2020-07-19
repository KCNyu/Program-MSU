/*************************************************************************
	> File Name: test36.c
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Nov 2019 05:19:22 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    FILE *fp = fopen("myfile1","r");
    char c;
    int count = 0;
    while(fscanf(fp,"%c",&c) != EOF)
        if(c == '\n')
            count++;
    fclose(fp);
    printf("%d\n",count);
    return 0;
}
