/*================================================================
 * Filename:test2.cpp
 * Author: KCN_yu
 * Createtime:Tue 05 Jan 2021 12:23:22 PM CST
 ================================================================*/

#include <iostream>

using namespace std;

class BaseLang {
    public:
        BaseLang() { cout << "Я "; }
        virtual ~BaseLang() { cout << endl; }
        void f(int n) { cout << "люблю Паскаль "; }
        virtual void f() { cout << "люблю "; }
};
class Derived : public BaseLang {
    public:
        Derived() {}
        Derived(int x) { cout << "уже выучил "; }
        void f() { cout << "знаю "; }
        void f(int n) { cout << "выучу "; }
        ~Derived() { cout << "Си++"; }
};
int main() {
    BaseLang *pa = new BaseLang;
    pa->f(1);
    delete pa;
    pa = new Derived;
    {
        BaseLang &ra = *pa;
        ra.f();
        delete pa;
    }
    pa = new Derived;
    pa->BaseLang::f();
    delete pa;
    Derived *pb = new Derived;
    pb->f(1);
    delete pb;
    Derived b(1);
}
