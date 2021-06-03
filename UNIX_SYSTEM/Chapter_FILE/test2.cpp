/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Tue 18 May 2021 01:19:29 AM CST
================================================================*/

#include <iostream>
#include <unistd.h>
using namespace std;

#define BUFFSIZE 4096
int main(int argc, char *argv[])
{
    int n;
    char buf[BUFFSIZE];
    while((n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0){
        if(write(STDOUT_FILENO,buf,n) != n){
            cerr << "write error" << endl;
        }
    }
    if(n < 0){
        cerr << "read error" << endl;
    }
    return 0;
}
