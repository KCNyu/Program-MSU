/*================================================================
* Filename:VVK.4.7.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 01:43:09 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class T {
public:
    virtual void f (int x) {
        h (); cout << "T::f," << x << endl;
    }
    void g () {
        h (); cout << "T::g" << endl;
    }
    virtual void h () {
        cout << "T::h" << endl;
    }
};
class U: virtual public T {
public:
    void f (int y) {
        h (y); cout << "U::f," << y << endl;
    }
    virtual void g () {
        h (0); cout << "U::g" << endl;
    }
    void h (int k) {
        cout << "U::h," << k << endl;
    }
};
int main(){
    T t; U u; T * p = & u;
    p -> f (1);
    p -> g ();
    p -> h ();
    //p -> h (2);
}

