#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct Node * link;
typedef struct Node {
            elemtype elem;
            link next;
        } node;


typedef struct Queue {
                link front;
                link rear;
        } queue;

void init_queue(queue * q){(*q).front=NULL; (*q).rear=NULL;};


elemtype from_queue(queue *q){
  if ((*q).front==NULL){
    fprintf(stderr, "queue is empty \n");
  }
  else{
    link temp=(*q).front;
    elemtype res=((*q).front)->elem;
    (*q).front=(*q).front->next;
    if ((*q).front==NULL) (*q).rear=NULL;
    free(temp);
    return res;
  }
}

void in_queue(queue *q, elemtype elem){
  link temp=malloc(sizeof(node));
       temp->elem=elem;
       temp->next=NULL;
       if((*q).rear!=NULL){
            (*q).rear->next=temp;
       }
       (*q).rear=temp;
       if((*q).front==NULL) (*q).front=temp;
}

  int main()
{ queue q;
  init_queue(&q);
  /* �� �ܧݧѧӧڧѧ���� �ӧӧ�էڧ��� ����ݧ֧է�ӧѧ�֧ݧ�ߧ���� ��֧ݧ�� ��ڧ�֧�, �� �ܧ�ߧ�� ����ݧ֧է�ӧѧ�֧ݧ�ߧ���� 0.
     ���ѧ�֧�ѧ�ѧ�� ��ߧѧ�ѧݧ� �ӧ�� ���ݧ�اڧ�֧ݧ�ߧ�� ��ڧ�ݧ�, ������ �ӧ�� ����ڧ�ѧ�֧ݧ�ߧ��.
    ...  */



}
