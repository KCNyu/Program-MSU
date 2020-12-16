/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Thu 10 Dec 2020 06:12:36 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A{
int a;
public:
A ( int x ){ a = x; cout << 1; }
A ( int x, int y ){ a = x / y; cout << 2; }
A ( int x, int y, int z = 1 ) { a = (x+y) / z; cout << 3; }
~A (){ cout << 4; }
void operator = ( A &b ){ a = b.a; cout << 5; } };
void f () {
    //A x;
    A y ( 1 );
   // A z ( 1, 2 );
    A t ( 1, 2, 3 );
    A w = 4;
    A v = y;
    y = t = v;
}
int main(int argc, char *argv[])
{
    f();
    return 0;
}
