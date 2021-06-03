/*================================================================
* Filename:Complex.cpp
* Author: KCN_yu
* Createtime:Thu 12 Mar 2020 01:23:00 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

#define PI 3.14159265358979323846
double fabs(double x) { return x > 0 ? x : -x; }

class Complex{
    private:
        double X, Y;
    public:
        Complex() {}
        Complex(double X, double Y) { Init(X,Y); }
        Complex(const Complex& C) {Init(C); }
        Complex operator*(const Complex& C);
        void Init(double X, double Y) { this->X = X; this->Y = Y; }
        void Init(const Complex& C) { Init(C.X, C.Y); }
        double GetX() { return X; }
        double GetY() { return Y; }
        friend ostream& operator<<(ostream&os, const Complex& C);
};
ostream& operator<<(ostream&os, const Complex& C){
        os << '(' << C.X << ',' << C.Y << ')' << endl;
        return os;
}
double exponent(double x, double eps){
    if(x < 0) return 1/exponent(-x,eps);
    double result = 0;
    double term = 1.0;
    int i = 1;
    while(term > eps){
        result += term;
        term = term*x/i++;
    }
    return result;
}
double cos(double x, double eps){
    if(x > 2*PI || x < -2*PI) x -= (int)(x/(2*PI))*2*PI;
    if(x > PI) x -= 2*PI;
    if(x < -PI) x += 2*PI;
    double result = 0;
    double term = 1.0;
    int i = 1;
    while(fabs(term) > eps){
        result += term;
        term = (-1)*term*x*x/(i*(i+1));
        i += 2;
    }
    return result;
}
double sin(double x, double eps){
    if(x > 2*PI || x < -2*PI) x -= (int)(x/(2*PI))*2*PI;
    if(x > PI) x -= 2*PI;
    if(x < -PI) x += 2*PI;
    double result = 0;
    double term = x;
    int i = 2;
    while(fabs(term) > eps){
        result += term;
        term = (-1)*term*x*x/(i*(i+1));
        i += 2;
    }
    return result;
}
Complex Formula_exponent(Complex& C, double eps){
    Complex result;
    double X = C.GetX();
    double Y = C.GetY();
    double temp = exponent(X,eps);
    result.Init(temp*cos(Y,eps),temp*sin(Y,eps));
    return result;
}
int main(int argc, char *argv[])
{
    Complex C1(2,1);
    Complex C2 = Formula_exponent(C1,0.00001);
    cout << C2;
    return 0;
}
