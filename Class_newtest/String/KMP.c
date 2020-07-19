/*================================================================
* Filename:KMP.c
* Author: KCN_yu
* Createtime:Wed 01 Jan 2020 11:40:55 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getNext(char *str, int *next, int len){
    next[0] = -1;
    int k = -1;
    for(int q = 1; q < len; q++){
        while(k > -1 && str[k+1] != str[q])
            k = next[k];
        if(str[k+1] == str[q])
            k++;
        next[q] = k;
    }
}
int KMP(char *str, int slen, char *ptr, int plen){
    int count = 0;
    int *next = (int*)malloc(sizeof(int)*plen);
    getNext(str,next,plen);
    int k = -1;
    for(int i = 0; i < slen; i++){
        while(k > -1 && ptr[k+1] != str[i])
            k = next[k];
        if(ptr[k+1] == str[i])
            k++;
        if(k == plen-1){
            count++;
            k = -1;
            i = i-plen+1;
        }
    }
    return count;
}
int main()
{
    printf("input str: ");
    char *str = (char*)malloc(sizeof(char)*100);
    scanf("%s",str);

    printf("input ptr: ");
    char *ptr = (char*)malloc(sizeof(char)*100);
    scanf("%s",ptr);

    printf("count = %d\n",KMP(str,strlen(str),ptr,strlen(ptr)));
    return 0;
}
