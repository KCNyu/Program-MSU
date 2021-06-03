/*================================================================
* Filename:Search_tree.c
* Author: KCN_yu
* Createtime:Mon 23 Dec 2019 04:05:19 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct tNode *tree;
typedef int elemtype_t;
typedef struct tNode
{
    elemtype_t elem;
    tree left;
    tree right;
} tNode;

void Insert(tree *t, elemtype_t value){
    tree temp = (tree)malloc(sizeof(tNode));
    temp->elem = value;
    temp->left = temp->right = NULL;
    if(*t == NULL)
        *t = temp;
    else{
        tree tmp = *t;
        while(tmp != NULL){
            if(value > tmp->elem){
                if(tmp->right == NULL){
                    tmp->right = temp;
                    return;
                }
                else
                    tmp = tmp->right;
            }
            else{
                if(tmp->left == NULL){
                    tmp->left = temp;
                    return;
                }
                else
                    tmp = tmp->left;
            }
        }
    }
}
void Sort(int *A, int n){
    int i,j,tmp;
    for(i = 0; i < n; i++){
        tmp = A[i];
        for(j = i-1; j >= 0; j--){
            if(A[j] > tmp){
                A[j+1] = A[j];
                A[j] = tmp;
            }
        }
    }
}
tree Create_idealtree(int start, int end, int *A){
    int n = end-start;
    tree t = (tree)malloc(sizeof(tNode));
    t->elem = A[(end+start)/2];
    t->left = NULL;
    t->right = NULL;
    if(n != 0){
        int mid = (start+end)/2;
        t->left = Create_idealtree(start,mid-1,A);
        t->right = Create_idealtree(mid+1,end,A);
    }
    return t;
}
tree idealtree(int n, int *A){
    for(int i = 0; i < n; i++)
        A[i] = rand()%1000;
    Sort(A,n);
    return Create_idealtree(0,n-1,A);
}
_Bool Find(tree t, elemtype_t elem){
    if(t == NULL) return false;
    if(elem == t->elem) return true;
    return elem > t->elem ? Find(t->right,elem) : Find(t->left,elem);
}
_Bool Judge(tree t){
    if(t == NULL)
        return true;
    else if(t->left == NULL && t->right == NULL)
        return true;
    else if(t->left != NULL && t->right == NULL){
        if(t->left->elem > t->elem) return false;
        else return Judge(t->left);
    }
    else if(t->left == NULL && t->right != NULL){
        if(t->right->elem < t->elem) return false;
        else return Judge(t->left);
    }
    else{
        if(t->left->elem > t->elem || t->right->elem < t->elem) return false;
        else return Judge(t->left) && Judge(t->right);
    }
}

tree Search_node(tree t, elemtype_t elem){
    if(t == NULL) return NULL;
    if(elem == t->elem) return t;
    else if(elem > t->elem) Search_node(t->right,elem);
    else Search_node(t->left,elem);
}
tree Search_parent(tree t, tree child){
    tree parent = NULL;
    if(t == NULL) return NULL;
    if(t->right == child || t->left == child)
        parent = t;
    else if(child->elem < t->elem)
        parent = Search_parent(t->left,child);
    else
        parent = Search_parent(t->right,child);

    return parent;
}
tree Search_min_node(tree t){
    if(t == NULL) return NULL;
    while(t->left != NULL)
        t = t->left;
    return t;
}
void Delete(tree *pt, elemtype_t elem){
    tree t = *pt;
    tree del = Search_node(t,elem);
    tree parent = Search_parent(t,del);
    if(t == NULL || del == NULL) return;
    if(del->left == NULL && del->right == NULL){
        if(*pt == del){
            free(t);
            *pt = NULL;
            return;
        }
        if(parent->left == del)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(del);
        return;
    }
    else if(del->left != NULL && del->right == NULL){
        if(t == del){
            *pt = t->left;
            free(t);
            return;
        }
        if(parent->left == del)
            parent->left = del->left;
        else
            parent->right = del->left;
        free(del);
        return;
    }
    else if(del->left == NULL && del->right != NULL){
        if(t == del){
            *pt = t->right;
            free(t);
            return;
        }
        if(parent->left == del)
            parent->left = del->right;
        else
            parent->right = del->right;
        free(del);
        return;
    }
    else{
        tree minRight = Search_min_node(del->right);
        del->elem = minRight->elem;
        parent = Search_parent(t,minRight);
        if(minRight == del->right)
            parent->right = minRight->right;
        else
            parent->left = minRight->right;
        free(minRight);
    }
}
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
typedef int elemtype_s;
typedef struct sNode{
    elemtype_s elem;
    struct sNode* next;
}sNode;
typedef struct sNode* stack;

elemtype_s Pop(stack *p){
    elemtype_s tmp;
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
void Push(stack *p, elemtype_s el){
    stack tmp = (stack)malloc(sizeof(sNode));
    tmp->elem = el;
    tmp->next = *p;
    *p = tmp;
}
void Print_every(tree t){
    if(t == NULL) return;
    Queue Q;
    Q_Init(&Q);
    Enqueue(&Q,t);
    tree currentNode = t;
    while(Q.front != NULL){
        tree tmp = Dequeue(&Q);
        printf("%d ",tmp->elem);
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
void Print_every_rev(tree t){
    if(t == NULL) return;
    Queue Q;
    Q_Init(&Q);
    Enqueue(&Q,t);
    stack st = NULL;
    while(Q.front != NULL){
        tree tmp = Dequeue(&Q);
        Push(&st,tmp->elem);
        if(tmp->left != NULL)Enqueue(&Q,tmp->left);
        if(tmp->right != NULL)Enqueue(&Q,tmp->right);
        if(Q.front == NULL)
            break;
    }
    while(st != NULL)
        printf("%d ",Pop(&st));
    putchar('\n');
}
int main()
{
    int len;
    scanf("%d",&len);
    srand(time(NULL));
    putchar('\n');

    tree t = NULL;
    for(int i = 0; i < len; i++){
        int n = rand()%1000;
        Insert(&t,n);
    }
    Print_every(t);
    putchar('\n');
    Print_every_rev(t);
    return 0;
}
