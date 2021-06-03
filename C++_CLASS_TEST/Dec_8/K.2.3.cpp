/*================================================================
* Filename:K.2.3.cpp
* Author: KCN_yu
* Createtime:Thu 10 Dec 2020 07:20:47 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class complex
{
public:
    complex (double x){ re = x; im = 1; };
    //virtual ~complex ();
    friend ostream& operator<<(ostream&os, const complex& C){
        os << '(' << C.re << ',' << C.im << ')' << endl;
        return os;
    }
private:
    int re,im;
};
int main(int argc, char *argv[])
{
    complex c(5);
    cout << c << endl;
    return 0;
}
