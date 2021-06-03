/*================================================================
* Filename:test12.cpp
* Author: KCN_yu
* Createtime:Thu 17 Dec 2020 07:09:23 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;


struct S {
static double d;
virtual S & g () { cout << "g ( ) from S" << endl; }
};

struct T: S {
virtual T & g ( ) { cout << "g ( ) from T" << endl; }
};
double S::d = 1.5;
int main () {
 T t; S s , *ps = &t;
ps -> g ();
s.d = 5; t.d = 7;
cout << s.d << ' ' << t.d << ' ' << S::d << endl;
 return 0;
}
