/*================================================================
* Filename:VVK.6.4.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 08:35:36 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A{
public:
    static int x;
    void get_0() const;
};
int A::x;
int main () {
    const A a;
    a.x = 1;
    a.get_0();
    return 0;
}

