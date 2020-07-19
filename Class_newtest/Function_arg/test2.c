/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Oct 2019 10:03:27 AM CST
 ************************************************************************/

#include<stdio.h>
void print_a(void);
int main()
{
    int i;
    for(i = 0; i < 5; i++)
        print_a();
    return 0;
}
void print_a(){
    static int a = 1;
    printf("%d\n",a++);
    return;
}
