/*================================================================
* Filename:VVK.6.4.b.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 09:11:29 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A{
public:
    static const char a;
    static void f(){}
};
const char A::a = '+';
int main () {
A ob;
A::f();
return 0;
}
