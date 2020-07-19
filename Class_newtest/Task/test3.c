B
/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: Tue 05 Nov 2019 05:02:26 PM CST
 ************************************************************************/

#include<stdio.h>
int Strlength(char *s){
    char *p = s;
    while(*p != '\0'){
        p++;
    }
    return p-s;
}
void Swap(char *c1, char *c2){
    char temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}
void Reverse1(char *s){
    int length = Strlength(s);
    char temp;
    for(int i = 0; i < length/2; i++){
        Swap(s+length-1-i,s+i);
    }
}
void Reverse2(char *s,int from, int to){
    if(from >= to){
        return;
    }
    else{
        Swap(s+from,s+to);
        Reverse2(s,from+1,to-1);
    }
}
void Reverse3(char *sl, char *sr){
    if(sl >= sr){
        return;
    }
    else{
        Swap(sl,sr);
        Reverse3(sl+1,sr-1);
    }
}
int main()
{
    char s[100];
    scanf("%s",s);
    int length = Strlength(s);
    Reverse3(s,s+length-1);
    puts(s);
    return 0;
}
