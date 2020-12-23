/*================================================================
* Filename:VVK.6.5.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 10:00:58 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A {
public:
    static void f(int x) {
        //h (x);
        cout << "A::f," << x << endl;
    }
    void g() {
        cout << "A::g" << endl;
    }
    void h(int x) {
        g ();
        cout << "A::h," << x << endl;
    }
};
class B: virtual public A {
public:
    static void f(int x) {
        //h (x);
        cout << "B::f," << x << endl;
    }
    void g() {
        cout << "B::g" << endl;
    }
    void h (int x) {
        g ();
        cout << "B::h," << x << endl;
    }
};
int main() {
    B::f(0);
    B b;
    A * p = & b;
    p -> f(1);
    p -> g();
    p -> h(2);
    A::f(3);
    return 0;
}

