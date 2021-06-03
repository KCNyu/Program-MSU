/*================================================================
* Filename:VVK.6.3.b.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 08:19:21 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A {
public:
    static int i;
    void f() const{
        if (i >= 0)
        i = -1, g();
        cout << "f()" << endl;
    }
    void g() const{
        f();
        cout << "g()" << endl;
    }
};
int A::i = 1;
int main () {
    A::i = 1;
    const A a;
    a.f();
    a.i = 0;
    return 0;
}

