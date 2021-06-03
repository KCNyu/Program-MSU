/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Wed 26 May 2021 01:23:55 AM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void print_set(const sigset_t* set){
    for(int i = 1; i < 32; i++){
        if(sigismember(set, i)){
            cout << '1';
        }
        // Check whether there is a corresponding signal in the blocked signal set
        else{
            cout << '0';
        }
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    sigset_t set, oldset, pedset;

    int ret = 0;

    sigemptyset(&set);
    //empty initializ sigset
    sigaddset(&set, SIGINT);
    // block SIGINT <ctrl-c> = 2
    sigaddset(&set, SIGQUIT);
    // block SIGQUIT <ctrl-\> = 3
    sigaddset(&set, SIGBUS);
    // block SIGBUS = 7
    sigaddset(&set, SIGKILL);
    // try to block SIGKILL = 9, but it can't be blocked

    if((ret = sigprocmask(SIG_BLOCK, &set, &oldset)) == -1){
        cerr << "sigprocmask error" << endl;
        return -1;
    }
    // Bind the custom signal set to the system signal set
    while(1){
        if((ret = sigpending(&pedset)) == -1){
            cerr << "sigpending error" << endl;
            return -1;
        }
        // View the pending signal set of the system
        print_set(&pedset);
        sleep(1);
    }
    return 0;
}

