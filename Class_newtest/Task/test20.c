/*************************************************************************
	> File Name: test20.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 01:36:21 PM CST
 ************************************************************************/

#include<stdio.h>
char *c[] = {"ENTER","NEW","POINT","FIRST"};
char **cp[] = {c+3,c+2,c+1,c};
char ***cpp = cp;

int main()
{
    printf("%s\n",**++cpp);//FIRST ++>> POINT
    printf("%s\n",*--*++cpp+3);//POINR ++>> NEW --(c+1-1)>> ENTER 3>> = ER (**cp[] = {c+3,c+2,c+1,c})
    printf("%s\n",*cpp[-2]+3);//ENTER (c+1 >> c+3)>> FIRST >> 3 = ST
    printf("%s\n",cpp[-1][-1]+1);//NEW >> 1 = EW
    
    return 0;
}
