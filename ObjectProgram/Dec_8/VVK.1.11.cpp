/*================================================================
* Filename:VVK.1.11.cpp
* Author: KCN_yu
* Createtime:Sun 06 Dec 2020 09:30:19 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class I {
    int i;
public:
    I() : i(6) { cout << "owl" << endl; }
    I(int a) : i(a) { cout << "sheep " << i << endl; }
    I(const I & other) : i(other.i) { cout << "horse " << i << endl; }
    ~I() { cout << "wolf" << endl; }
    int Get() { return i; }
    void operator*=(const I & op) { i*=op.i; }
};
void f(I x, I & y) {
    x *= 1;
    y *= x;
}
int main() {
    I i1;
    I i2(3);
    i1 *= 7;
    f(i1, i2);
    cout << i1.Get() << ' ' << i2.Get()<< endl;
    return 0;
}
