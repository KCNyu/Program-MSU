/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Oct 2019 10:22:17 AM CST
 ************************************************************************/

#include<stdio.h>
void Print(int a, int b){
    if(a <= b){
        printf("%d\n",a);
        Print(a+1,b);
    }
    return;
}
int main(){
    Print(0,6);
    return 0;
}
