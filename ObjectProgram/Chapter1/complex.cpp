/*================================================================
* Filename:complex.cpp
* Author: KCN_yu
* Createtime:Sun 29 Nov 2020 11:12:27 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class complex
{
private:
    double re, im;
public:
    complex(double a, double b);
    void print(){ cout << re << endl << im << endl; }
};
complex::complex(double a = 0, double b = 0){
    re = a;
    im = b;
}
int main(int argc, char *argv[])
{
    complex a(1,2);
    a.print();
    return 0;
}
