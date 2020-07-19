/*************************************************************************
	> File Name: list_calculator.c
	> Author:
	> Mail:
	> Created Time: Fri 06 Dec 2019 04:29:59 PM CST
 ************************************************************************/
//由于两个struct的elemtype类型出现char与int不兼容的问题，所以只能计算返回值小于等于127的数值

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int elemtype;
typedef struct Node{
    elemtype elem;
    struct Node* next;
}Node;
typedef struct Node* stack;

elemtype Pop(stack *p){
    elemtype tmp;
    stack p_tmp = *p;
    if(*p == NULL){
        fprintf(stderr,"Error:empty stack\n!");
        exit(1);
    }
    tmp = p_tmp->elem;
    *p = p_tmp->next;
    free(p_tmp);
    return tmp;
}
void Push(stack *p, elemtype el){
    stack tmp = (stack)malloc(sizeof(Node));
    tmp->elem = el;
    tmp->next = *p;
    *p = tmp;
}
_Bool isEmpty(stack st){
    return st == NULL;
}
_Bool Compare(char c1, char c2){
    if((c1 == '+' || c1 == '-') && (c2 == '*' || c2 == '/'))
        return true;
    return false;
}
int Eval_postfix(char *s){
    stack st = NULL;
    while(*s != '\0'){
        if('0' <= *s && *s <= '9')
            Push(&st,*s-'0');
        else if(*s == '+')
            Push(&st,Pop(&st)+Pop(&st));
        else if(*s == '*')
            Push(&st,Pop(&st)*Pop(&st));
        else if(*s == '-'){
            int digit = Pop(&st);
            Push(&st,Pop(&st)-digit);
        }
        else if(*s == '/'){
            int digit = Pop(&st);
            Push(&st,Pop(&st)/digit);
        }
        s++;
    }
    return Pop(&st);
}
int main()
{
    char *s = (char*)malloc(sizeof(char)*100);
    scanf("%s",s);
    printf("result = %d\n",Eval_postfix(s));
    return 0;
}
