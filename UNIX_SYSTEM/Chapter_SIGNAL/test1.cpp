/*================================================================
 * Filename:test1.cpp
 * Author: KCN_yu
 * Createtime:Tue 25 May 2021 11:56:07 PM CST
 ================================================================*/

#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
using namespace std;
void SigHandlr(int s){
    cout << "hello\n" << endl;
    cout << "s: " << s << endl; // SIGALRMA-14
}
int main(int argc, char *argv[])
{
    struct itimerval it, otv;

    signal(SIGALRM,SigHandlr);

    it.it_value.tv_sec = 2;
    it.it_value.tv_usec = 0;
    //start from 2 seconds

    it.it_interval.tv_sec = 5;
    it.it_interval.tv_usec = 0;
    //evert interval 5 seconds

    if(setitimer(ITIMER_REAL, &it, &otv) == -1){
        perror("setitimer error\n");
        return -1;
    }
    while(1)
    {
        sleep(1);
        printf("otv: %ld, %ld, %ld, %ld\n", otv.it_value.tv_sec, otv.it_value.tv_usec, otv.it_interval.tv_sec, otv.it_interval.tv_sec);
    }
    // 2 1 0
    // 5 4 3 2 1
    // 5 4 3 2 1
    // ...

    return 0;
}

