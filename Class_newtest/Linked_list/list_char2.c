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
    char c;
    scanf("%c",&c);
    if(c == '\n')
        return NULL;
    cur->elem = c;
    while(c != '\n'){
        scanf("%c",&c);
        if(c == '\n')
            break;
        cur = cur->Next = (list)malloc(sizeof(Node));
        cur->elem = c;
    }
    cur->Next = NULL;
    return res;
}
void Print(list p){
    while(p != NULL){
        printf("%c",p->elem);
        p = p->Next;
    }
    putchar('\n');
}
void Print_reverse_rec(list p){
    if(p == NULL)
        return;
    Print_reverse_rec(p->Next);
    if(p->elem != '\0')
        putchar(p->elem);
}
elemtype Pop(list *p){
    elemtype tmp;
    list p_temp = *p;
    tmp = p_temp->elem;
    *p = p_temp->Next;
    free(p_temp);
    return tmp;
}
void Push(list *p,elemtype el){
    list tmp = (list)malloc(sizeof(Node));
    tmp->elem = el;
    tmp->Next = *p;
    *p = tmp;
}
void Insert(list *p, elemtype el, int position){
    list temp = (list)malloc(sizeof(Node));
    temp->elem = el;
    if(position == 0){
        temp->Next = *p;
        *p = temp;
    }
    else{
        list l = *p;
        while(position != 1){
            l = l->Next;
            position--;
        }
        temp->Next = l->Next;
        l->Next = temp;
    }
}
void in_order(list *p, elemtype elem){
    if(*p == NULL){
        Insert(p,elem,0);
        return;
    }
    else{
        list temp = *p;
        int position = 0;
        while(elem > temp->elem && temp->Next != NULL){
            position++;
            temp = temp->Next;
        }
        Insert(p,elem,position);
    }
}
list rev(list p){
    if(p == NULL || p->Next == NULL)
        return p;
    list newNode = rev(p->Next);
    p->Next->Next = p;
    p->Next = NULL;
    return newNode;
}
int main()
{
    list sentence1;
    sentence1 = Create();
    Print(sentence1);

    //list sentence2 = rev(sentence1);
    list sentence2 = sentence1;
    sentence2->elem = 'f';
    Print(sentence1);
    /*
    char c;
    scanf("%c",&c);
    in_order(&sentence1,c);
    Print(sentence1);
    */
    return 0;
}
