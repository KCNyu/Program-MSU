/*************************************************************************
	> File Name: test30.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Nov 2019 04:08:11 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;
void Swap(char *c1, char *c2){
    char temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}
void Reverse1(char *s){
    int length = strlen(s);
    char temp;
    for(int i = 0; i < length/2; i++){
        Swap(s+length-1-i,s+i);
    }
}
int main(int argc, char *argv[])
{
    int i;
    
    for(i = argc-1; i > 0; i--){
        Reverse1(argv[i]);
        printf("%s%s",argv[i],(i > 0) ? " " : "");
    }
    printf("\n");
    return 0;
}
