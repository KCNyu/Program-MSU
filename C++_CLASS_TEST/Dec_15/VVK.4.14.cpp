/*================================================================
* Filename:VVK.4.14.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 01:57:11 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct B {
    virtual void f (int n) { cout << "f (int) from B" << endl; }
    static int i;
};
struct D: B {
    virtual void f (char n) { cout << "f (char) from D" << endl; }
};
int B::i = 1;
int main () {
    D d;
    B b1, b2, *pb = &d;
    pb -> f ('a');
    b1.i += 2;
    b2.i += 3; d.i += 4;
    cout << b1.i << ' ' << b2.i << ' ' << d.i << ' ' << B::i << endl;
    return 0;
}
