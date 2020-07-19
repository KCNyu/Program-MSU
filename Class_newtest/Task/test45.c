/*************************************************************************
	> File Name: test44.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Nov 2019 05:02:32 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
int main(int argc, char *argv[])
{
    int mas[1];
    int max;
    _Bool flag = true;
    FILE *fp = fopen(argv[1],"r");
    while(fread(mas,sizeof(mas[0]),1,fp)){
        if(flag){
            max = mas[0];
            flag = false;
        }
        if(mas[0] > max)
            max = mas[0];
    }
    printf("max = %d\n",max);
    return 0;
}
