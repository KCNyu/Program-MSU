/*================================================================
* Filename:test6.cpp
* Author: KCN_yu
* Createtime:Thu 17 Dec 2020 06:02:52 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class X {
public:
 virtual int g (double x) {
 h (); cout << "X::g" << endl;
 return 1;
 }
 void h () { t (); cout << "X::h" << endl;}
 virtual void t () { cout << "X::t" << endl;}
};

class Z: public X {
public:
 int g (double y) {
 h (); cout << "Z::g" << endl;
 return 3;
 }
 virtual void h () { t (1); cout << "Z::h" << endl; }
 virtual void t (int k) { cout << "Z::t" << endl; }
};
int main(){
    X a; Z b; X * p = &b;
    p -> g(1.5);
    p -> h();
    //p -> t(5);
}
