/*================================================================
* Filename:list_period.c
* Author: KCN_yu
* Createtime:Mon 09 Dec 2019 08:36:42 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char elemtype;
struct Node{
    elemtype elem;
    struct Node* next;
}Node;
typedef struct Node* list;

list Create(char *s){
    list ls;
    list head;
    list temp;
    _Bool flag = false;
    if(*s == '\0')return NULL;

    head = ls = (list)malloc(sizeof(Node));
    ls->elem = *s++;
    while(*s != '\0' && *s != '('){
        ls = ls->next = (list)malloc(sizeof(Node));
        ls->elem = *s++;
        ls->next = NULL;
    }
    if(*s == '('){
        flag = true;
        s++;
    }
    while(*s != '\0' && *s != ')'){
        ls = ls->next = (list)malloc(sizeof(Node));
        ls->elem = *s++;
        if(flag){
            temp = ls;
            flag = false;
        }
        ls->next = NULL;
    }
    if(*s == ')')
        ls->next = temp;

    return head;
}
int Judge_length(list head){
    list fast, slow;
    fast = slow = head;
    _Bool flag = false;
    int length = 0;

    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            flag = true;
            break;
        }
    }
    if(flag){
        slow = slow->next;
        length++;
        while(slow != fast){
            slow = slow->next;
            length++;
        }
    }
    return length;
}
int main()
{
    char *s = (char*)malloc(sizeof(char)*100);
    scanf("%s",s);
    list dig = Create(s);
    printf("%d\n",Judge_length(dig));
    return 0;
}


