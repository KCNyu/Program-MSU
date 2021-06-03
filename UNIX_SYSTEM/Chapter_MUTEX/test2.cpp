/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Thu 27 May 2021 11:34:35 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <cstdint>
using namespace std;

int counter;
pthread_rwlock_t rwlock; // global read write lock

void *th_write(void *arg){
    int t;
    intptr_t i = reinterpret_cast<intptr_t>(arg);
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        t = counter;
        usleep(1000);
        printf("=========write %ld: %lu: counter = %d ++counter=%d\n", i, pthread_self(), t, ++counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(10000);
    }
    return NULL;

}
void *th_read(void *arg){
    intptr_t i = reinterpret_cast<intptr_t>(arg);

    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("-----------------------read %ld: %lu: %d\n", i, pthread_self(), counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[9];

    pthread_rwlock_init(&rwlock, nullptr);

    for(i = 0; i < 3; i++){
        pthread_create(&tid[i], nullptr, th_write, reinterpret_cast<void*>(i));
    }
    for(i = 0; i < 5; i++){
        pthread_create(&tid[i+3], nullptr, th_read, reinterpret_cast<void*>(i));
    }
    for (i = 0; i < 8; ++i) {
        pthread_join(tid[i],nullptr);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}

