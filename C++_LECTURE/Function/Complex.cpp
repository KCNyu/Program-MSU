/*================================================================
* Filename:Complex.cpp
* Author: KCN_yu
* Createtime:Thu 12 Mar 2020 01:23:00 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>

using namespace std;

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
        //void Print() { cout << '(' << X << ',' << Y << ')' << endl; }
        void Add(const Complex& C1, const Complex& C2);
        void Mult(const Complex& C1, const Complex& C2);
        void Exponent1(int num);
        void Exponent2(const Complex& C, int num);
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
void Complex::Exponent1(int num){
    Complex C = *this;
    for(int i = 1; i < num; i++) *this = *this*C;
}
void Complex::Exponent2(const Complex& C, int num){
    *this = C;
    for(int i = 1; i < num; i++) *this = *this*C;
}
Complex My_pow(Complex& A, int B){
    Complex result;
    if(B == 0){
        result.Init(1,0);
        return result;
    }
    if(B == 1) return A;
    result = My_pow(A, B >> 1);
    result = result * result; // result^2;
    if((B & 0x01) == 1)
        result = result * A;
    return result;
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

double fabs(double x) { return x > 0 ? x : -x; }

Complex Formula_exponent(Complex& C, double eps){
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
int main(int argc, char *argv[])
{
    /*
    Complex C1(0.707,-0.707); cout << C1;
    Complex C2(-3,3); cout << C2;
    Complex CCC1; CCC1.Add(C1,C2); cout << CCC1;
    Complex CCC2; CCC2.Mult(C1,C2); cout << CCC2;
    Complex CCC3 = C1*C2; cout << CCC3;
    Complex CCC4; CCC4.Exponent2(C1,2); cout << CCC4;
    Complex CCC5 = My_pow(C1,1); cout << CCC5;
    */
    Complex C1(12,12);
    Complex C2 = Formula_exponent(C1,0.00001);
    cout << C2;
    return 0;
}
