/*************************************************************************
	> File Name: list.c
	> Author:
	> Mail:
	> Created Time: Mon 02 Dec 2019 08:51:45 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int elemtype;
typedef struct Node{
    elemtype elem;
    struct Node *Next;
}Node;
typedef Node *list;

list Create(){
    list cur;
    list res;
    int len;
    printf("Input length of list: ");
    scanf("%d",&len);
    printf("Input element of list: ");
    res = cur = (list)malloc(sizeof(Node));
    scanf("%d",&cur->elem);
    while(len != 1){
        cur = cur->Next = (list)malloc(sizeof(Node));
        scanf("%d",&cur->elem);
        len--;
    }
    cur->Next = NULL;
    return res;
}
int Length(list p){
    return (p) ? Length(p->Next)+1 : 0;
}
void Print(list p){
    while(p != NULL){
        printf("%d ",p->elem);
        p = p->Next;
    }
    putchar('\n');
}

int Sum(list p){
    int sum = 0;
    while(p != NULL){
        sum += p->elem;
        p = p->Next;
    }
    return sum;
}
int Sum_rec(list p){
    if(p == NULL)
        return 0;
    return Sum_rec(p->Next) + p->elem;
}

int Max(list p){
    if(p == NULL)
        return 0;
    int M;
    M = p->elem;
    while(p != NULL){
        if(p->elem > M)
            M = p->elem;
        p = p->Next;
    }
    return M;
}
int Max_rec(list p){
    if(p->Next == NULL)
        return p->elem;
    int M;
    return p->elem > (M = Max_rec(p->Next)) ? p->elem : M;
}
int Min_rec(list p){
    if(p->Next == NULL)
        return p->elem;
    int m;
    return p->elem < (m = Min_rec(p->Next)) ? p->elem : m;
}

_Bool Judge(list p){
    if(p == NULL)
        return false;
    while(p != NULL && (p->Next) != NULL){
        if(p->elem > (p->Next)->elem)
            return false;
        p = p->Next;
    }
    return true;
}
_Bool Judge_rec(list p){
    if(p == NULL)
        return false;
    if(p->Next == NULL)
        return true;
    return (p->elem) > (p->Next)->elem ? false : Judge_rec(p->Next);
}

int Sum_maxmin(list p){
    if(p == NULL)
        return 0;
    int max = p->elem, min = p->elem;
    while(p != NULL){
        if(p->elem > max)
            max = p->elem;
        if(p->elem < min)
            min = p->elem;
        p = p->Next;
    }
    return max + min;
}
int Sum_maxmin_rec1(list p){
    if(p == NULL)
        return 0;
    return Max_rec(p)+Min_rec(p);
}
int Sum_maxmin_rec_temp(list p, int *max, int *min){
    if(p == NULL)
        return *max + *min;
    max = p->elem > *max ? &p->elem : max;
    min = p->elem < *min ? &p->elem : min;
    return Sum_maxmin_rec_temp(p->Next,max,min);
}
int Sum_maxmin_rec2(list p){
    return Sum_maxmin_rec_temp(p,&p->elem,&p->elem);
}

void Exchange1(list p){
    list q = p;
    elemtype tmp;
    if(p == NULL || p->Next == NULL)
        return;
    while(q->Next != NULL)
        q = q->Next;
    tmp = p->elem;
    p->elem = q->elem;
    q->elem = tmp;
}
void Exchange2(list *p){
    list temp1 = *p;
    list temp2 = *p;
    if(Length(*p) > 2){
        while((temp2->Next)->Next != NULL)
            temp2 = temp2->Next;
        *p = temp2->Next;
        temp2->Next->Next = temp1->Next;
        temp2->Next = temp1;
        temp1->Next = NULL;
    }
    else{
        *p = temp1->Next;
        (temp1->Next)->Next = temp1;
        temp1->Next = NULL;
    }
}
void Exchange_rec_temp(list *p, list t){
    if(t->Next->Next != NULL)
        Exchange_rec_temp(p,t->Next);
    if(t->Next->Next == NULL){
        list temp = *p;
        *p = t->Next;
        t->Next->Next = temp->Next;
        t->Next = temp;
        temp->Next = NULL;
    }
}
void Exchange_rec(list *p){
    if((*p)->Next->Next == NULL){
        list temp = *p;
        *p = temp->Next;
        (temp->Next)->Next = temp;
        temp->Next = NULL;
        return;
    }
    return Exchange_rec_temp(p,(*p)->Next);
}
void Print_reverse(list p){
    if(p == NULL)
        return;
    int len = Length(p);
    elemtype *A = (int*)malloc(sizeof(elemtype)*len);
    for(int i = 0; i < len; i++){
        A[i] = p->elem;
        p = p->Next;
    }
    for(int i = len-1; i >= 0; i--)
        printf("%d ",A[i]);
    free(A);
}
void Print_reverse_rec(list p){
    if(p == NULL)
        return;
    Print_reverse_rec(p->Next);
    printf("%d ",p->elem);
}
_Bool Judge_same(list p){
    while(p != NULL){
        list temp = p->Next;
        while(temp != NULL){
            if(temp->elem == p->elem)
                return true;
            temp = temp->Next;
        }
        p = p->Next;
    }
    return false;
}
_Bool Judge_same_rec_temp(list p, list t){
    if(p->elem == t->elem)
        return true;
    if(p->Next->Next == NULL)
        return false;
    if(t->Next != NULL)
        return Judge_same_rec_temp(p,t->Next);
    if(p->Next != NULL && t->Next == NULL)
        return Judge_same_rec_temp(p->Next,p->Next->Next);
}
_Bool Judge_same_rec(list p){
    return Judge_same_rec_temp(p,p->Next);
}
elemtype Pop(list *p){
    elemtype tmp;
    list p_temp = *p;
    tmp = p_temp->elem;
    *p = p_temp->Next;
    free(p_temp);
    return tmp;
}
void Push(list *p){
    printf("Inuput the element: ");
    elemtype el;
    scanf("%d",&el);
    list tmp = (list)malloc(sizeof(Node));
    tmp->elem = el;
    tmp->Next = *p;
    *p = tmp;
}
void Empty(list *p){
    if((*p)->Next != NULL)
        Empty((&(*p)->Next));
    if((*p)->Next == NULL){
        free(*p);
        *p = NULL;
    }
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
int main()
{
    list number;
    number = Create();

    Print(number);
    /*
    Print_reverse(number);
    putchar('\n');

    printf("Sum of list = %d\n",Sum(number));
    printf("Sum of list = %d\n",Sum_rec(number));

    printf("Max of list = %d\n",Max_rec(number));
    printf("Min of list = %d\n",Min_rec(number));

    printf("Judge of list = %d\n",Judge(number));
    printf("Judge of list = %d\n",Judge_rec(number));

    printf("Sum_maxmin of list = %d\n",Sum_maxmin(number));
    printf("Sum_maxmin of list = %d\n",Sum_maxmin_rec1(number));
    printf("Sum_maxmin of list = %d\n",Sum_maxmin_rec2(number));

    printf("Judge of list have the same element = %d\n",Judge_same(number));
    printf("Judge of list have the same element = %d\n",Judge_same_rec(number));

    Exchange_rec(&number);
    printf("After exchange the first one element with the last one: ");
    Print(number);

    printf("Pop the firstelement = %d\n",Pop(&number));
    printf("After pop: ");
    Print(number);

    Push(&number);
    Print(number);

    Empty(&number);
    Print(number);
    */
    Print(number);

    return 0;
}
