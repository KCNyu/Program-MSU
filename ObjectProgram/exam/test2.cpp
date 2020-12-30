/*================================================================
 * Filename:test2.cpp
 * Author: KCN_yu
 * Createtime:Wed 30 Dec 2020 04:10:28 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class B{
    private:
        int n;
    public:
        B(int a = 0):n(10*a){}
        B operator+(const B& b){ return B((n+b.n)/10); }
        int get(){ return n; }
};
int main() {
    B b1,  b2(10), b3(20);
    b1= b2+b3;
    cout << b1.get()<<b2.get()<<b3.get()<<endl;
}
