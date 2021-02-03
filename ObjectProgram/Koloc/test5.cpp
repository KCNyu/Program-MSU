/*================================================================
* Filename:test5.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 04:21:06 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A{
public:
    virtual void f() const { cout << "A::f() ";}
};
class B: public A{
public:
    void f() const { cout << "B::f() "; }
};
int main(int argc, char *argv[])
{
    const A& a = B();
    a.A::f();
    return 0;
}
