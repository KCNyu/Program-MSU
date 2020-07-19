/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 04 Nov 2019 10:13:37 PM CST
 ************************************************************************/

#include<stdio.h>
typedef enum SEASON{
    winter = 1, spring, summer, autumn
}season;
int main()
{
    enum SEASON season;
    season = autumn;
    printf("%d\n",season);
    return 0;
}
