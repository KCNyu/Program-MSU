/*************************************************************************
	> File Name: Singly_linked_list.c
	> Author:
	> Mail:
	> Created Time: Fri 29 Nov 2019 04:46:04 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node *link;
typedef char elemtype;

typedef struct Node{
    elemtype elem;
    link next;
}node;

typedef link list;

void print(list p){
    while(p != NULL){
        putchar(p->elem);
        p = p->next;
    }
    putchar('\n');
}

void rec_print(list p){
    if(p == NULL)
        return;
    rec_print(p->next);
    putchar(p->elem);
}

list create(char *s){
    link cur;
    list res;
    if(*s == '\0')return NULL;

    res = cur = (link)malloc(sizeof(node));
    cur->elem = *s++;

    while(*s != '\0'){
        cur = cur->next = (list)malloc(sizeof(node));
        cur->elem = *s++;
    }
    cur->next = NULL;

    return res;
}

void push(list *pl, elemtype el){
    link tmp = malloc(sizeof(node));
    tmp->elem = el;
    tmp->next = *pl;
    *pl = tmp;
}
int empty(list p){
    return p == NULL;
}
int rec_count(list p){
    if(p == NULL)
        return 0;
    return rec_count(p->next) + 1;
}
int Max(list p){
    int M;
    if(empty(p))
        return 0;
    M = p->elem;
    while(p != NULL){
        if(p->elem > M){
            M = p->elem;
        }
        p = p->next;
    }
    return M;
}
void in_last(list *p, char c){
    link q;
    link t;
    q = malloc(sizeof(node));
    q->elem = c;
    if(empty(*p))
        *p = q;
    else{
        t = *p;
        while(t->next != NULL){
            t = t->next;
        }
        t->next = q;
    }
}
void del_first(list *p){
    if(empty(*p))
        return;
    link t;
    t = (*p)->next;
    free(t);
}
void del_second(list *p){
    if(empty(*p) || empty((*p)->next))
        return;
    link t;
    t = (*p)->next;
    (*p)->next = (*p)->next->next;
    free(t);
}
void del_last(list *p){
    if(empty(*p))
        return;
    if((*p)->next == NULL){
        free(*p);
        *p = NULL;
        return;
    }
    link t;
    t = *p;
    while(t->next->next != NULL){
        t = t->next;
    }
    free(t->next);
    t->next = NULL;
}
elemtype pop(list *pl){
    elemtype tmp;
    link p = *pl;
    if(*pl == NULL){
        fprintf(stderr,"Error:empty stack\n");
        exit(1);
    }
    tmp = p->elem;
    *pl = p->next;
    free(p);
    return tmp;
}
void Exchange(list p){
    link q = p;
    elemtype tmp;
    if(empty(p))
        return;
    if(p->next == NULL)
        return;
    while(q->next != NULL){
        q = q->next;
    }
    tmp = p->elem;
    p->elem = q->elem;
    q->elem = tmp;
}
list copy(list p){
    if(empty(p))
        return NULL;
    link t,q;
    q = t = malloc(sizeof(node));
    t->elem = p->elem;
    p = p->next;
    while(p != NULL){
        t->next = malloc(sizeof(node));
        t = t->next;
        t->elem = p->elem;
        p = p->next;
    }
    t->next = NULL;
    return q;
}
list rec_copy(list p){
    link t;
    if(empty(p))
        return NULL;
    t = malloc(sizeof(node));
    t->elem = p->elem;
    t->next = rec_copy(p->next);
    return t;
}
void del_befor_a(list *lp){
    link q;
    if(*lp == NULL || (*lp)->next == NULL)
        return;
    while((*lp)->next != NULL){
        if((*lp)->next->elem == 'a'){
            q = *lp;
            *lp = (*lp)->next;
            free(q);
        }
        else
            lp = &((*lp)->next);
    }
}
int length(list ls){
    return (ls)? length(ls->next)+1 : 0;
}
void print1(list p){
    int len = length(p);
    int i = 0;
    while(i != len-1){
        //putchar(p->elem);
        p = p->next;
        i++;
    }
    putchar(p->elem);
    putchar('\n');
}
void Delete(list* p){
    list temp1 = *p;
    list temp2 = *p;
    if(temp2->elem == 'a' && temp2->next == NULL)
        return;
    if(temp2->next->elem == 'a' && temp2->next->next == NULL){
        *p = temp2->next;
        free(temp2);
        return;
    }
    while(temp1->next != NULL)
        temp1 = temp1->next;
    if(temp1->elem == 'a'){
        while(temp2->next->next->next != NULL)
            temp2 = temp2->next;
        temp2->next = temp1;
    }
    return;
}
int main()
{
    list lst;
    char *s = (char*)malloc(sizeof(char)*100);
    scanf("%s",s);
    lst = create(s);
    Delete(&lst);
    print(lst);
    return 0;
}
