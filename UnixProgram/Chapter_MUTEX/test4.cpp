/*================================================================
* Filename:test4.cpp
* Author: KCN_yu
* Createtime:Fri 28 May 2021 04:20:25 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <cstring>
#include <cstdint>
using namespace std;

#define NUM 5

int queue[NUM];
sem_t blank_number, product_number;

void *producer(void *arg){
    int i = 0;

    while (1) {
        sem_wait(&blank_number);
        queue[i] = rand() % 1000 + 1;
        printf("============Producer--%d\n",queue[i]);
        sem_post(&product_number);

        i = (i+1)%NUM;
        sleep(rand()%1);
    }
    return nullptr;
}
void *consumer(void *arg){
    int i = 0;

    while (1) {
        sem_wait(&product_number);
        printf("---Consumer--%d\n",queue[i]);
        queue[i] = 0;
        sem_post(&blank_number);

        i = (i+1)%NUM;
        sleep(rand()%3);
    }
}
int main(int argc, char *argv[])
{
    pthread_t pid, cid;
    sem_init(&blank_number,0,NUM);
    sem_init(&product_number,0,0);

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid,NULL);
    pthread_join(cid,NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);
    return 0;
}
