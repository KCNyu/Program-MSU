/*************************************************************************
	> File Name: test35.c
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Nov 2019 05:08:30 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++){
        FILE *fp = fopen(argv[i],"r");
        char c;
        while(fscanf(fp,"%c",&c) != EOF)
            printf("%c",c);
        fclose(fp);
    }
    return 0;
}
