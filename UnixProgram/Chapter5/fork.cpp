/*================================================================
* Filename:fork.cpp
* Author: KCN_yu
* Createtime:Sun 23 May 2021 06:49:35 PM CST
================================================================*/

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main(int argc, char *argv[])
{
    int i;
    for(i = 0; i < 5; i++){
        if(fork() == 0){
            break;
        }
    }
    if(i == 5){
        sleep(5);
        cout << "====================" << endl;
        cout << "i am parent" << endl;
        cout << "my pid is " << getpid() << endl;
        cout << "my parent id is " << getppid() << endl;
    }
    else{
        sleep(i);
        cout << "i am " << i << "-th " << "child process" << endl;
        cout << "my pid is " << getpid() << endl;
        cout << "my parent id is " << getppid() << endl;
    }
    return 0;
}
