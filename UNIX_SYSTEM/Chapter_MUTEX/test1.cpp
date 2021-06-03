/*================================================================
* Filename:test1.cpp
* Author: KCN_yu
* Createtime:Thu 27 May 2021 10:02:15 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
using namespace std;

pthread_mutex_t mutex;
// Define a mutex lock

void *tfn(void *arg){
    srand(time(NULL));

    while(1){
        pthread_mutex_lock(&mutex);
        // add lock

        cout << "hello ";
        sleep(rand() % 3);
        cout << "world" << endl;

        pthread_mutex_unlock(&mutex);
        // unlock

        sleep(rand() % 3);
    }
    return nullptr;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    srand(time(NULL));

    int ret = pthread_mutex_init(&mutex, NULL);
    if(ret != 0){
        cerr << "mutex init error" << strerror(ret) << endl;
    }

    pthread_create(&tid, NULL, tfn, NULL);
    while(1){
        pthread_mutex_lock(&mutex);
        // add lock

        cout << "HELLO ";
        sleep(rand() % 3);
        cout << "WORLD" << endl;

        pthread_mutex_unlock(&mutex);
        // unlock

        sleep(rand() % 3);
    }
    pthread_join(tid, nullptr);

    pthread_mutex_destroy(&mutex); // destroy mutex lock
    return 0;
}

