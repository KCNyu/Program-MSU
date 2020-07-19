/*************************************************************************
	> File Name: test11.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Nov 2019 06:42:40 PM CST
 ************************************************************************/

#include<stdio.h>
typedef enum{
    red, blue, green = 5, yellow
}colortype;

colortype next_color (colortype color){
    switch(color){
        case red : return blue;
        case blue : return green;
        case green : return yellow;
        case yellow : return red;
    }
}
int main()
{
    printf("%d\n",next_color(green));
    return 0;
}
