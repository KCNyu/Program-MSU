/*================================================================
* Filename:test4.cpp
* Author: KCN_yu
* Createtime:Wed 16 Dec 2020 02:42:45 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct A{
    virtual int f(int x, int y){
        cout << "A::f(int,int)\n";
        return x+y;
    }
    virtual void f(int x){
        cout << "A::f(int)\n";
    }
};
struct B : A{
    void f(int x){
        cout << "B::f(int)\n";
    }
};
struct C : B{
    virtual int f(int x, int y){
        cout << "C::f(int,int)\n";
        return x+y;
    }
};
int main(int argc, char *argv[])
{
    B b, *pb = &b;
    C c;
    A *pa = &b;
    pa->f(1);
    //pb->f(1,2);
    A& ra = c;
    ra.f(1,1);
    B& rb = c;
    //rb.f(0,0);
    return 0;
}
