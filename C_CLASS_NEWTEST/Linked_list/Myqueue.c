/*================================================================
* Filename:Myqueue.c
* Author: KCN_yu
* Createtime:Tue 10 Dec 2019 04:45:56 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
struct Node{
    elemtype elem;
    struct Node* next;
}Node;
typedef struct Node* link;
typedef struct queue{
    link front;
    link rear;
}Queue;

void Q_Init(Queue *Q){
    Q->front = Q->rear = NULL;
}
void Enqueue(Queue* Q, elemtype el){
    link temp = (link)malloc(sizeof(Node));
    temp->elem = el;
    temp->next = NULL;
    if(Q->rear == NULL){
        Q->front = temp;
        Q->rear = temp;
    }
    else{
        Q->rear->next = temp;
        Q->rear = temp;
    }
}

elemtype Dequeue(Queue *Q){
    elemtype tmp;
    link p = Q->front;
    if (Q->front == NULL) {
        fprintf(stderr, "error\n");
        exit(1);
    }
    tmp = p->elem;
    Q->front = p->next;
    if (Q->front == NULL) {
        Q->rear = NULL;
    }
    free(p);
    return tmp;
}
int main()
{
    Queue Q;
    Q_Init(&Q);

    int number;

    while(1){
        scanf("%d",&number);
        if(number < 0)
            Enqueue(&Q,number);
        else if(number > 0)
            printf("%d ",number);
        else if(number == 0)
            break;
    }
    while(Q.front != NULL)
        printf("%d ",Dequeue(&Q));
    putchar('\n');

    return 0;
}
