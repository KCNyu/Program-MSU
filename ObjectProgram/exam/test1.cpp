/*================================================================
 * Filename:test1.cpp
 * Author: KCN_yu
 * Createtime:Wed 30 Dec 2020 03:51:44 PM CST
 ================================================================*/

#include <iostream>
using namespace std;
double a = 0;
void funct (double x){a = x; cout << "1" << endl; }
struct B {
    double a;
    void funct (){a = 2;}
    virtual void operator--(int) = 0;
};
class D: B {
    public:
        void funct (int a){::a = a; cout << "2" << endl; }
        void j ();
        void print() { cout << "a = " << a << endl; }
        void operator--(int){ a--; }
};
void D::j() {
    funct(1.2);
    //funct();
    a = 2;
    cout << a << endl;
}
int main () {
        D d;
        //funct();
        funct(6);
        d.j();
        d.print();
        d--;
        d.print();
        cout << a << endl;
        return 0;
}
