/*************************************************************************
	> File Name: Count.c
	> Author:
	> Mail:
	> Created Time: Mon 02 Dec 2019 08:51:45 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef char elemtype;
typedef struct Node{
    elemtype elem;
    struct Node *Next;
}Node;
typedef Node *list;

list Create(){
    list cur;
    list res;
    res = cur = (list)malloc(sizeof(Node));
    char c;
    scanf("%c",&c);
    if(c == '\n')
        return NULL;
    cur->elem = c;
    while(c != '\n'){
        scanf("%c",&c);
        if(c == '\n')
            break;
        cur = cur->Next = (list)malloc(sizeof(Node));
        cur->elem = c;
    }
    cur->Next = NULL;
    return res;
}
elemtype Pop(list *p){
    elemtype tmp;
    list p_temp = *p;
    tmp = p_temp->elem;
    *p = p_temp->Next;
    free(p_temp);
    return tmp;
}
int Count(list sentence, list word){
    int count = 0;
    while(sentence != NULL){
        list front_sentence = sentence;
        list front_word = word;
        while(front_sentence->elem == front_word->elem){
            front_sentence = front_sentence->Next;
            front_word = front_word->Next;
            if(front_sentence == NULL && front_word != NULL)
                return count;
            if(front_word == NULL){
                count++;
                break;
            }
        }
        Pop(&sentence);
    }
    return count;
}
int main()
{
    printf("Input the sentence: ");
    list sentence = Create();
    printf("Input the word: ");
    list word = Create();

    printf("count = %d\n",Count(sentence,word));
    return 0;
}
