/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Wed 02 Dec 2020 04:55:42 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class complex{
private:
    double re, im;
public:
    complex(double r = 0, double i = 0){
        re = r;
        im = i;
    }
    /*
    friend complex operator+(const complex& a, const complex& b){
        complex temp(a.re+b.re,a.im+b.im);
        return temp;
    }
    */
    complex operator+(const complex& a){
        complex temp(re+a.re,im+a.im);
        return temp;
    }
    void print(){ cout << re << " " << im << endl; }
};
int main(int argc, char *argv[])
{
    complex x(1,2), y(5,8),z;
    double t = 7.5;
    z = x+y;
    z.print();
    z = z+t;// z.operator+(complex(t))
    z.print();
    z = x+t;
    z.print();
    return 0;
}
