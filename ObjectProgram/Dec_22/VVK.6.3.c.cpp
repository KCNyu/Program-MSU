/*================================================================
* Filename:VVK.6.3.c.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 08:33:15 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A {
public:
static int i;
void f() const {
    if (i < 0)
    g(i);
    cout << "f ()" << endl;
    }
    void g (int  n) const{
        i = n;
        f();
        cout << "g ()" << endl;
    }
};
int A::i = 1;
int main () {
    const A a;
    a.g(2);
    return 0;
}

