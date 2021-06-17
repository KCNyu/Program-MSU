/*================================================================
* Filename:test.cpp
* Author: KCN_yu
* Createtime:Thu 17 Jun 2021 04:50:48 PM CST
================================================================*/

#include <iostream>
#include <complex>
#include <vector>
using namespace std;

int main()
{
    vector<complex<double>> v;
    complex<double> c(1,2);
    cout << c << endl;
    v.emplace_back(move(c));
    cout << c << endl;
    c.real(3);
    cout << c << endl;
    cout << v[0] << endl;
}
