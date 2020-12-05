/*================================================================
* Filename:test4.cpp
* Author: KCN_yu
* Createtime:Thu 03 Dec 2020 06:40:11 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class B{
    private:
        int n;
    public:
        B(int t = 10){ n = t; }
        B(const B& B_t){ n = B_t.n + 10; }
        int get() { return n; }
};

class C{
    private:
        int n;
    public:
        C(int t = 0){ n = 2*t; }
        C(const C& C_t) { n = C_t.n*2; }
        int get() { return n; }
    friend C operator+(const C& c1, const C& c2) { C tmp; tmp.n = (c1.n+c2.n); return tmp; }
};
class I{
    int i;
public:
    I():i(9){ cout << "sun" << endl; }
    I(int a):i(a){ cout << "venus " << i << endl; }
    I(const I& other):i(other.i){ cout << "earth " << i << endl; }
    ~I() { cout << "moon" << endl; }
    int get() { return i; }
    void operator+= (const I &op) { i += op.i; }
};
void f(I& x, I y){
    y += 1000;
    x += y;
}
int main(int argc, char *argv[])
{
    /*
    B b1, b2 = b1, b3(b2);
    cout << b1.get() << b2.get() << b3.get() << endl;
    C c1(7), c2 = 5, c3(c1+c2);
    cout << c1.get() <<" " << c2.get() <<" " << c3.get() <<" "<< endl;
    */
    I i1;
    I i2(20);
    i2 += 400;
    f(i1,i2);
    cout << i1.get() << " "<< i2.get() << endl;
    return 0;
}
