/*================================================================
* Filename:K.2.4.cpp
* Author: KCN_yu
* Createtime:Sun 29 Nov 2020 11:33:16 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class rational
{
private:
    int num;
    int dem;
public:
    rational(int a = 0, int b = 1){ num = a; dem = b; simplify(); }
    void simplify();
    void print(){ cout << num << endl << dem << endl; }
    double value() { return (double)num/dem; }
    friend rational operator+(const rational &r1, const rational &r2);
    friend rational operator-(const rational &r1, const rational &r2);
    friend rational operator*(const rational &r1, const rational &r2);
    friend rational operator/(const rational &r1, const rational &r2);
    friend bool operator>(rational &r1,rational &r2) { return r1.value() > r2.value(); }
    friend bool operator<(rational &r1,rational &r2) { return r1.value() < r2.value(); }
};
void rational::simplify(){
    int t = __gcd(num,dem);
    num = num/t;
    dem = dem/t;
}
rational operator+(const rational &r1, const rational &r2){
    rational res;
    res.num = r1.num * r2.dem + r2.num * r1.dem;
    res.dem = r1.dem * r2.dem;
    res.simplify();
    return res;
}
rational operator-(const rational &r1, const rational &r2){
    rational res;
    res.num = r1.num * r2.dem - r2.num * r1.dem;
    res.dem = r1.dem * r2.dem;
    res.simplify();
    return res;
}
rational operator*(const rational &r1, const rational &r2){
    rational res;
    res.num = r1.num * r2.num;
    res.dem = r1.dem * r2.dem;
    res.simplify();
    return res;
}
rational operator/(const rational &r1, const rational &r2){
    rational res;
    res.num = r1.num * r2.dem;
    res.dem = r1.dem * r2.num;
    res.simplify();
    return res;
}
int main(int argc, char *argv[])
{
    rational r1(16,24);
    r1.print();
    rational r2(-8,16);
    r2.print();
    rational r3 = 5+r2;
    r3.print();
    cout << (r1 > r2) << endl;
    return 0;
}
