/*================================================================
* Filename:test9.cpp
* Author: KCN_yu
* Createtime:Thu 17 Dec 2020 06:40:24 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A {
 int i;
public:
 A(int x) { i = x; cout << "first" << endl; }
 virtual ~A() { cout << "second" << endl; }
 int f() const { return i + g() + h(); }
 virtual int g() const { return i; }
 int h() const { return 39; }
};
class B : public A {
public:
 B() : A(70) { cout <<"third" << endl; }
 ~B() { cout << "fourth" << endl; }
 int f() const { return g() - 2; }
 virtual int g() const { return 4; }
 int h() const { return 6; }
};
int main() {
 B b;
 A* p = &b;
 cout << "result = (" << p->f() <<';'<< b.f() << ')' << endl;
 return 0;
}
