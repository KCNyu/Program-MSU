/*================================================================
* Filename:VVK.1.21.cpp
* Author: KCN_yu
* Createtime:Mon 07 Dec 2020 01:06:56 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct B {
    int x;
    B() { x = 7; cout << 7; }
    virtual ~B() { cout << 8; }
};
struct D : B {
    D(int d = 0) { x = d ; cout << 6; }
    ~D() { cout << 9; }
};
int main () {
    B * p1 = new B [1], * p2 = new D[1];
    delete [ ] p1;
    delete [ ] p2;
    return 0;
}

