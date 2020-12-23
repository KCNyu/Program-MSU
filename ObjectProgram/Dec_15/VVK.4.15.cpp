/*================================================================
* Filename:VVK.4.15.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 01:59:20 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct K {
    virtual void add_st ( K * n ) {
        st ++; cout << "add_st (K*) from K" << endl;
    }
    static int st;
};
struct L: K {
    virtual void add_st ( L * a ) {
        st++; cout << "add_st (L*) from L" << endl;
    }
};
int K::st = 2;
int main () {
    L ob, ob2;
    K k, *pl = &ob;
    pl -> add_st (& ob2);
    k.st ++; ++ob.st ;
    cout << k.st << ' ' << ob.st << ' ' << K::st << endl;
    return 0;
}

