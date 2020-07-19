/*************************************************************************
	> File Name: test3_temp.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Oct 2019 08:13:53 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    char c1[100];
    scanf("%s",c1);

    int length1 = 0;
    while(c1[length1] != '\0'){
        length1++;
    }
    
    char c2[100];
    scanf("%s",c2);
   
    int length2 = 0;
    while(c2[length2] != '\0'){
        c1[length1] = c2[length2];
        length2++;
        length1++;
    }
    c1[length1] = '\0';
    puts(c1);
    return 0;
}
