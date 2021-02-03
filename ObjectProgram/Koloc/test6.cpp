/*================================================================
* Filename:test6.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 04:27:29 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class C{
public:
    C(){ cout << 'a'; }
    ~C(){ cout << 'b'; }
    void operator=(const C&a){ cout << 'c'; }
};
int main(int argc, char *argv[])
{
    C a;
    cout <<'d';
    C b(a);
    b = a;
    return 0;
}
