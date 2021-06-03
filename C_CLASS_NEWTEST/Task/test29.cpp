/*************************************************************************
	> File Name: test29.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Nov 2019 04:08:11 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    int i;
    for(i = 1; i < argc; i++)
        printf("%s%s",argv[i],(i < argc-1) ? " " : "");
    printf("\n");
    return 0;
}
