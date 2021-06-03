/*================================================================
* Filename:VVK.6.4.c.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 09:33:06 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A{
public:
    static void g(){}
    void h()const{}
};
int main () {
    const A x;
    A::g();
    x.h();
return 0;
}

