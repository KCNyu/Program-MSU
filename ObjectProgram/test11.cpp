/*================================================================
* Filename:test11.cpp
* Author: KCN_yu
* Createtime:Thu 17 Dec 2020 07:08:17 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct S {
 virtual void f() const = 0;
 virtual ~S() {}
};
struct A {
 S s;
 int i;
};
