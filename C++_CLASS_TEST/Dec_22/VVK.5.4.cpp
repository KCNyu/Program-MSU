/*================================================================
* Filename:VVK.5.4.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 02:38:25 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct X;
void f(X & x, int n);
struct X {
    X() {
        try { f(*this, -1);cout << 1 << endl; }
        catch (X) { cout << 2 << endl; }
        catch (int) { cout << 3 << endl; }
    }
    X (X &) { cout << 4 << endl; }
    ~X () { cout << 5 << endl; }
};
struct Y: X {
    Y (){ f(*this, -1);
    cout << 6 << endl; }
    Y (Y &) { cout << 7 << endl; }
    ~Y () { cout << 8 << endl; }
};
void f(X & x, int n) {
    try {
        if (n < 0) throw x;
        if (n > 0) throw 1;
        cout << 9 << endl;
    }
    catch (int) { cout << 10 << endl; }
    catch (X& a) {
        cout << 11 << endl;
        f(a, 1);
        cout << 12 << endl;
        throw;
    }
}
int main() {
    try { Y a; }
    catch (...) {
        cout << 13 << endl;
        return 0;
    }
    cout << 14 << endl;
    return 0;
}
