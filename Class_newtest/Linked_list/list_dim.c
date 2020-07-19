/*************************************************************************
	> File Name: list_dim.c
	> Author: 
	> Mail: 
	> Created Time: Sun 08 Dec 2019 10:28:36 PM CST
 ************************************************************************/

#include<stdio.h>
void Printnum(stack p, int n){
    int i = 1;
    while(p->elem != '.'){
        putchar(p->elem);
        p = p->next;
    }
    putchar('.');
    p = p->next;
    while(p != NULL && i <= n){
        putchar(p->elem);
        i++;
        p = p->next;
    }
    while(i <= n){
        putchar('0');
        i++;
    }
    putchar('\n');
}
