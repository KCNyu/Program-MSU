/*************************************************************************
	> File Name: test19.c
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 10:01:14 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int num = 1024;
    int *pi = &num;
    char *ps = "FishC";
    void *pv;

    pv = pi;
    printf("pi:%p, pv:%p\n",pi,pv);

    pv = ps;
    printf("ps:%p, pv:%p\n",ps,pv);

    return 0;
}
