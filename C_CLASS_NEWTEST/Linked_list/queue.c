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
  /* §ã §Ü§Ý§Ñ§Ó§Ú§Ñ§ä§å§â§í §Ó§Ó§à§Õ§Ú§ä§ã§ñ §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§î §è§Ö§Ý§í§ç §é§Ú§ã§Ö§Ý, §Ó §Ü§à§ß§è§Ö §á§à§ã§Ý§Ö§Õ§à§Ó§Ñ§ä§Ö§Ý§î§ß§à§ã§ä§Ú 0.
     §¯§Ñ§á§Ö§é§Ñ§ä§Ñ§ä§î §ã§ß§Ñ§é§Ñ§Ý§Ñ §Ó§ã§Ö §á§à§Ý§à§Ø§Ú§ä§Ö§Ý§î§ß§í§Ö §é§Ú§ã§Ý§Ñ, §á§à§ä§à§Þ §Ó§ã§Ö §à§ä§â§Ú§è§Ñ§ä§Ö§Ý§î§ß§í§Ö.
    ...  */



}
