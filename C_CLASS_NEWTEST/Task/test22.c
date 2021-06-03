/*************************************************************************
	> File Name: test22.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 11:02:04 PM CST
 ************************************************************************/
#include<stdio.h>
int Count_abel_adel(){
    int count = 0;
    char c = getchar();
    while(1){
        if(c == EOF)
            break;
        else if(c != 'a'){
            c = getchar();
            continue;
        }
        else
            c = getchar();
        
        if(c != 'b' && c != 'd')
            continue;
        else
            c = getchar();

        if(c != 'e')
            continue;
        else
            c = getchar();
        
        if(c != 'l')
            continue;
        else{
            c = getchar();
            count++;
        }
    }
    return count;
}
int main()
{
    printf("\ncount = %d\n",Count_abel_adel());
    return 0;
}
