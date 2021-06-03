/*================================================================
* Filename:test1.cpp
* Author: KCN_yu
* Createtime:Thu 10 Dec 2020 06:07:18 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A {
int a, b;
public:
A ( A &x )  { a = x.a; b = x.b; cout << 1; }
A ( int a ) { this->a = a; b = a; cout << 2; }
};
void f () {
    A x ( 1 );
    A y;
    A z = A ( 2, 4 );
    A t ( 3.5, 2 );
    A s = 6;
    A w = z;
    t = z = w;
}
int main(int argc, char *argv[])
{
    f();
    return 0;
}
