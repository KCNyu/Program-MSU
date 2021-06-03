/*================================================================
* Filename:test8.cpp
* Author: KCN_yu
* Createtime:Wed 30 Dec 2020 04:41:11 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Y {
      public:
            static void g () {cout << "g\n";}
            void f () const {cout << "f\n";}
};
int main () {
      const Y a;
      Y::g();
      a.f();
      return 0;
}
