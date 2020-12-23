/*================================================================
* Filename:VVK.7.1.cpp
* Author: KCN_yu
* Createtime:Tue 22 Dec 2020 11:42:25 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class K { public: void g () { cout << "K::g"; } };
class L: public K { public: void f () { cout << "L::f"; } };
class M: public K { public: virtual void h () { cout << "M::h"; } };
class P: public L { public: void f () { cout << "P::f"; } };
class Q: public M { public: virtual void h () { cout << "Q::h"; } };
class R: public P {
    public: virtual void f () { cout << "R::f"; }
    virtual void h () { cout << "R::h"; }
};
class S: public Q {
    public: virtual void f () { cout << "S::f";}
    virtual void h () { cout << "S::h"; }
};
int main (){
    S os, * s = & os; K * k; L * l; M * m; P * p; Q * q; R * r;
    int a, b;
    k = dynamic_cast <K *>(s);
    k = s;
    //s = dynamic_cast <S *>(k);
    //l = dynamic_cast <L *>(k);
    m = dynamic_cast <M *>(s);
    m = s;
    //p = dynamic_cast <P *>(l);
    q = dynamic_cast <Q *>(m);
    r = dynamic_cast <R *>(q);
    //s = dynamic_cast <S *>(p);
    return 0;
}

