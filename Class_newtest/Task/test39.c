/*************************************************************************
	> File Name: test39.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 11:23:21 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    FILE *f_cp = fopen("copy","w");
    char c;
    while((c = fgetc(fp)) != EOF)
        fputc(c,f_cp);
    fclose(fp);
    fclose(f_cp);
    return 0;
}
