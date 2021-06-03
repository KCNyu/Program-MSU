/*================================================================
* Filename:test5.cpp
* Author: KCN_yu
* Createtime:Wed 16 Dec 2020 03:04:37 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct B{
    virtual B& f(){
        cout << "f() from B\n";
        return *this;
    }
    virtual void g(int x, int y = 7){
        cout << "B::g\n";
    }
};
struct D : B{
    virtual D& f(){
        cout << "f() from D\n";
        return *this;
    }
    virtual void g(int x, int y){
        cout << "D::g y = " << y << endl;
    }
};

int main(int argc, char *argv[])
{
    D d;
    B b1, *pb = &d;
    pb->f();
    pb->g(1);
    pb->g(1,2);
    return 0;
}
