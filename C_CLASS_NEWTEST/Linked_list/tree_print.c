/*================================================================
* Filename:tree.c
* Author: KCN_yu
* Createtime:Fri 13 Dec 2019 04:30:10 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char elemtype_t;
typedef struct tNode *tree;
typedef struct tNode{
    elemtype_t elem;
    tree left;
    tree right;
}tNode;

typedef tree elemtype;
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
void Print_every(tree t){
    Queue Q;
    Q_Init(&Q);
    Enqueue(&Q,t);
    tree currentNode = t;
    while(Q.front != NULL){
        tree tmp = Dequeue(&Q);
        printf("%c ",tmp->elem);
        if(tmp->left != NULL)Enqueue(&Q,tmp->left);
        if(tmp->right != NULL)Enqueue(&Q,tmp->right);
        if(Q.front == NULL)
            break;
        if(tmp == currentNode){
            putchar('\n');
            currentNode = Q.rear->elem;
        }
    }
    putchar('\n');
}
tree Create(char *s){
    static char *p;
    tree t;
    p = s;
    if(*p == '<')p++;
    else return NULL;
    if(*p == '>'){
        p++;
        return NULL;
    }
    t = (tree)malloc(sizeof(tNode));
    t->elem = *p++;
    t->left = Create(p);
    t->right = Create(p);
    if(*p != '>')return NULL;
    else{
        p++;
        return t;
    }
}
int main()
{
    tree t = Create("<a<b<d<><>><e<><>>><c<><>>>>");
    Print_every(t);
    return 0;
}
