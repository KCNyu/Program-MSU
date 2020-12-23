/*================================================================
* Filename:VVK.6.6.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 11:30:14 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class C {
public:
    C(int x = 0) {}
    virtual int f(int x) const{
        cout << "C::f," << x << endl;
        return h (x);
    }
    virtual int g() const{
        cout << "C::g" << endl;
        return 1;
    }
    virtual int h (int x) const{
        cout << "C::h," << x << endl;
        return x;
    }
    virtual operator int () { return 99; }
};
class D: public C {
public:
    int f(int x) {
        cout << "D::f," << x << endl;
        return h (x);
    }
    int g(int x) {
        cout << "D::g" << endl;
        return 1;
    }
    int h(int x) {
        cout << "D::h," << x << endl;
        return x;
    }
    D(int x = 0) {}
    operator int () { return 100; }
};
int main() {
    const D d;
    C  const * const t = &d;
    t -> f(3);
    //t -> f(d);
    t -> g();
    t -> h(5);
    return 0;
}
