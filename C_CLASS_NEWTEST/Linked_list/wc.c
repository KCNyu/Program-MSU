/*************************************************************************
	> File Name: wc.c
	> Author: 
	> Mail: 
	> Created Time: Tue 03 Dec 2019 03:02:28 PM CST
 ************************************************************************/

#include<stdio.h>
void wc(FILE *f, int *l, int *w, int *c){
    char pred = ' ', cur;
    *l = *w = *c = 0;
    while(((cur) = fgetc(f)) != EOF){
        (*c)++;
        if(cur == '\n')
            (*l)++;
        else if((pred == ' ' || pred == '\t' || pred == '\n') && (cur != ' ') && (cur != '\t'))
            (*w)++;
        pred = cur;
    }
}
int main(int argc, char *argv[])
{
    int count1, count2, count3;
    FILE *fp = fopen(argv[1],"r");
    wc(fp,&count1,&count2,&count3);
    printf("%d %d %d\n",count1,count2,count3);
    return 0;
}
