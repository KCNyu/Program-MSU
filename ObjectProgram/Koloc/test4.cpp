/*================================================================
* Filename:test4.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 04:18:50 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A{
    public:
        void operator()(){}
};
int main(int argc, char *argv[])
{
    A c;
    c();
    return 0;
}
