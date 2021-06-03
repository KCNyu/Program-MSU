/*================================================================
* Filename:Complex.cpp
* Author: KCN_yu
* Createtime:Thu 12 Mar 2020 01:23:00 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////
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
        void Add(const Complex& C1, const Complex& C2);
        void Mult(const Complex& C1, const Complex& C2);
        void Divid(double i){ X /= i; Y /= i; }
        double GetX() { return X; }
        double GetY() { return Y; }
        friend ostream& operator<<(ostream&os, const Complex& C);
};
Complex Complex::operator*(const Complex& C){
    Complex CCC;
    CCC.X = this->X * C.X - this->Y * C.Y;
    CCC.Y = this->X * C.Y + this->Y * C.X;
    return CCC;
}
ostream& operator<<(ostream&os, const Complex& C){
        os << '(' << C.X << ',' << C.Y << ')' << endl;
        return os;
}
void Complex::Add(const Complex& C1, const Complex& C2){
    X = C1.X + C2.X;
    Y = C1.Y + C2.Y;
}
void Complex::Mult(const Complex& C1, const Complex& C2){
    X = C1.X*C2.X - C1.Y*C2.Y;
    Y = C1.X*C2.Y + C1.Y*C2.X;
}
/////////////////////////////////////////////////////////////////////////
//Это первый способ напрямую использовать формул Маклорена.

double fabs(double x) { return x > 0 ? x : -x; }

Complex Formula_exponent_1(Complex& C, double eps){
    Complex result(0,0);
    Complex term(1,0);
    for(int i = 1; ; i++){
        result.Add(result,term);
        term = term * C;
        term.Divid(i);
        double X = term.GetX();
        double Y = term.GetY();
        if(fabs(X) < eps && fabs(Y) < eps) break;
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////
//Это второй способ преобразования по формуле Эйлера.
// e^(a+bi) = e^a*cos(b) + e^a*sin(b)*i;   (e^a*cos(b),e^a*sin(b))

#define PI 3.14159265358979323846

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
Complex Formula_exponent_2(Complex& C, double eps){
    Complex result;
    double X = C.GetX();
    double Y = C.GetY();
    double temp = exponent(X,eps);
    result.Init(temp*cos(Y,eps),temp*sin(Y,eps));
    return result;
}

/////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    Complex C1(1,2);
    Complex C2 = Formula_exponent_1(C1,0.0000001);
    cout << C2;
    Complex C3 = Formula_exponent_2(C1,0.0000001);
    cout << C3;
    return 0;
}
