/*************************************************************************
	> File Name: test37.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Nov 2019 09:40:24 PM CST
 ************************************************************************/

#include<stdio.h>
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1],"r");
    int count[128] = {0};
    char c;
    while((c = fgetc(fp)) != EOF)
        count[(int)c]++;
    fclose(fp);
    
    int max = 0;
    int max_i = count[0];
    for(int i = 1; i < 128; i++){
        if(count[i] > max_i){
            max = i;
            max_i = count[i];
        }
    }
    printf("%c\n",(char)max);
    return 0;
}
