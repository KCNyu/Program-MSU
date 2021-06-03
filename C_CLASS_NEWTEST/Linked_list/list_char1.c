/*************************************************************************
	> File Name: list.c
	> Author:
	> Mail:
	> Created Time: Mon 02 Dec 2019 08:51:45 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef char elemtype;
typedef struct Node{
    elemtype elem;
    struct Node *Next;
}Node;
typedef Node *list;

list Create(){
    list cur;
    list res;
    printf("Input the sentence: ");
    res = cur = (list)malloc(sizeof(Node));
    scanf("%c",&cur->elem);
    while(cur->elem != '.'){
        cur = cur->Next = (list)malloc(sizeof(Node));
        scanf("%c",&cur->elem);
    }
    cur->Next = NULL;
    return res;
}
void Print_reverse_rec(list p){
    if(p == NULL)
        return;
    Print_reverse_rec(p->Next);
    if(p->elem != '.')
        putchar(p->elem);
}
int main()
{
    list sentence;
    sentence = Create();

    Print_reverse_rec(sentence);
    putchar('\n');

    return 0;
}
