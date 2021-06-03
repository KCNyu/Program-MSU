/*================================================================
* Filename:test3.cpp
* Author: KCN_yu
* Createtime:Thu 03 Dec 2020 06:16:54 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A
{
public:
    A (const A& x){
        a = x.a;
        b = x.b;
        cout << 1 << endl;
    }
    A (int a = 0,int b = 0){
        this->a = a;
        b = a;
        cout << 2 << endl;
    }
    A & operator= (const A& ra) {a=ra.a; b=ra.b; return * this;}
private:
    int a, b;
};
int main(int argc, char *argv[])
{
    A x(1);
    A y;
    A z = A(2.5,4);
    A s = 6;
    A w = z;
    x = z = w;
    return 0;
}
