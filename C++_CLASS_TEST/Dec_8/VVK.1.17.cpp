/*================================================================
* Filename:VVK.1.17.cpp
* Author: KCN_yu
* Createtime:Mon 07 Dec 2020 01:06:00 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct S {
    int x;
    S(int n) { x = n; printf(" Cons "); }
    S(const S & a) { x = a.x; printf(" Copy "); }
    ~S() { printf("Des "); }
};
S f( S & y ) {
    y = S(3);
    return y;
}
int main () {
    S s(1);
    f (s);
    printf("%d ", s.x);
    return 0;
}

