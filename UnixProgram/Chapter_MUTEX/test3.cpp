/*================================================================
 * Filename:test3.cpp
 * Author: KCN_yu
 * Createtime:Fri 28 May 2021 01:32:00 AM CST
 ================================================================*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <cstdint>
using namespace std;
struct msg{
    int num;
    struct msg *next;
};

struct msg *head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;

void *produser(void *arg){
    while (1) {

        struct msg *mp = new msg;

        mp->num = rand() % 1000 +1;
        printf("--producer %d\n", mp->num);

        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_data);

        sleep(rand()%2);
    }

    return nullptr;
}
void *consumer(void *arg){
    while (1) {

        pthread_mutex_lock(&mutex);
        if(head == nullptr){
            pthread_cond_wait(&has_data, &mutex);
        }
        struct msg *mp;

        mp = head;
        head = mp->next;

        pthread_mutex_unlock(&mutex);
        printf("=======consumer:%d\n", mp->num);

        delete(mp);
        sleep(rand()%3);
    }

    return nullptr;
}
int main(int argc, char *argv[])
{
    int ret;
    pthread_t pid, cid;

    srand(time(nullptr));

    ret = pthread_create(&pid, nullptr, produser, nullptr);
    if(ret != 0){
        cerr << "pthread_create produser error: " << strerror(ret) << endl;
    }

    ret = pthread_create(&cid, nullptr, consumer , nullptr);
    if(ret != 0){
        cerr << "pthread_create consumer error: " << strerror(ret) << endl;
    }

    pthread_join(pid, nullptr);
    pthread_join(cid, nullptr);
    return 0;
}
