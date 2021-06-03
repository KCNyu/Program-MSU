/*================================================================
* Filename:Mydeque.c
* Author: KCN_yu
* Createtime:Tue 10 Dec 2019 04:45:56 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>


typedef int elemtype;
typedef struct dNode * link;
typedef struct dNode{
            elemtype elem;
            link prev;
            link next;
}dnode;

typedef struct Deque{
                link front;
                link rear;
}deque;

void Q_Init(deque *Q){
    Q->front = Q->rear = NULL;
}

void Push(deque *Q, elemtype el){
    link temp = (link)malloc(sizeof(dnode));
    temp->elem = el;
    temp->prev = NULL;
    if(Q->front == NULL){
        temp->next = NULL;
        Q->front = temp;
        Q->rear = temp;
    }
    else{
        temp->next = Q->front;
        Q->front->prev = temp;
        Q->front = temp;
    }
}
elemtype Pop(deque *Q){
    elemtype tmp;
    link p = Q->front;
    if (Q->front == NULL) {
        fprintf(stderr, "error\n");
        exit(1);
    }
    tmp = p->elem;
    Q->front = p->next;
    if (Q->front == NULL)
        Q->rear = NULL;
    free(p);
    return tmp;
}

void Push_end(deque* Q, elemtype el){
    link temp = (link)malloc(sizeof(dnode));
    temp->elem = el;
    temp->next = NULL;
    if(Q->rear == NULL){
        temp->prev = NULL;
        Q->front = temp;
        Q->rear = temp;
    }
    else{
        temp->prev = Q->rear;
        Q->rear->next = temp;
        Q->rear = temp;
    }
}
elemtype Pop_end(deque *Q){
    elemtype tmp;
    link p = Q->rear;
    if (Q->rear == NULL) {
        fprintf(stderr, "error\n");
        exit(1);
    }
    tmp = p->elem;
    Q->rear = p->prev;
    if (Q->rear == NULL)
        Q->front = NULL;
    free(p);
    return tmp;
}
int main()
{
    deque Q;
    Q_Init(&Q);

    int number;

    while(1){
        scanf("%d",&number);
        if(number < 0)
            Push(&Q,number);
        else if(number > 0)
            Push_end(&Q,number);
        else if(number == 0)
            break;
    }
    while(Q.front != NULL)
        printf("%d ",Pop(&Q));
    putchar('\n');
    return 0;
}
