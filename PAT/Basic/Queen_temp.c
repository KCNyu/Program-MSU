/*================================================================
* Filename:Queen.c
* Author: KCN_yu
* Createtime:Tue 25 Feb 2020 04:12:35 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

int Queenes[8]={0},Counts=0;
int Check(int line,int list){
    for(int index=0; index<line; index++){
        int data=Queenes[index];
        if(list==data) return 0;
        if((index+data)==(line+list)) return 0;
        if((index-data)==(line-list)) return 0;
    }
    return 1;
}
void print(){
    for(int line = 0; line < 8; line++)
    {
        int list;
        for(list = 0; list < Queenes[line]; list++)
            printf("0");
        printf("#");
        for(list = Queenes[line] + 1; list < 8; list++)
            printf("0");
        printf("\n");
    }
    printf("================\n");
}
void eight_queen(int line){
    for(int list=0; list<8; list++) {
        if(Check(line, list)) {
            Queenes[line]=list;
            if (line==7){
                Counts++;
                print();
                Queenes[line]=0;
                return;
            }
            eight_queen(line+1);
            Queenes[line]=0;
        }
    }
}
int main() {
    eight_queen(0);
    printf("摆放的方式有%d种\n",Counts);
    return 0;
}
