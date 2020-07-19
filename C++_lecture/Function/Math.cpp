/*================================================================
* Filename:Math.cpp
* Author: KCN_yu
* Createtime:Wed 25 Mar 2020 09:35:43 PM CST
================================================================*/

#include <iostream>
using namespace std;

#define PI 3.14159265358979323846

double exponent(double x, double eps);
double cos(double x, double eps);
double sin(double x, double eps);
double ln(double x, double eps);
double arctg(double x, double eps);
double fabs(double x) { return x > 0 ? x : -x; }



//Далее используется расширение Маклафлина для вычисления значения функции

///////////////////////////////////////////////////////////////////////

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
double cos_temp(double x, double Eps){
    double Return = 0;
    double Tmp = 1;
    for(int i = 0; ; i++){
        Return += (i%2 == 0 ? (i%4 == 0 ? 1 : -1) * Tmp : 0);
        Tmp *= (x/(i+1));
        if(fabs(Tmp)<Eps) return Return;
    }
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

double arctg(double x, double eps){
    if(x < 0) return -arctg(-x,eps);
    if(x > 1) return PI/2 - arctg(1/x,eps);
    double result = 0;
    double term = x;
    int i = 3;
    while(fabs(term) > eps){
        result += term;
        term = (-1)*term*x*x*(i-2)/i;
        i += 2;
    }
    return result;
}
///////////////////////////////////////////////////////////////////////



//Далее используется интегральный метод и формула Симпсона для вычисления значения функции

///////////////////////////////////////////////////////////////////////

double F(double x){ return 1/x; }

double simpson(double a, double b){
    double c = a + (b-a)/2;
    return (F(a)+4*F(c)+F(b))*(b-a)/6;
}
double asr(double a, double b, double eps, double A){
    double c = a + (b-a)/2;
    double L = simpson(a,c), R = simpson(c,b);
    if(fabs(L+R-A) <= eps) return L+R+(L+R-A);
    return asr(a,c,eps,L) + asr(c,b,eps,R);
}
double asr(double a, double b, double eps){
    return asr(a,b,eps,simpson(a,b));
}
double ln(double x, double eps){
    return asr(1,x,eps);
}

///////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    cout << "e^21.5 = " << exponent(21.5,0.0000001) << endl;
    cout << "sin(11.7) = " << sin(11.7,0.0000001) << endl;
    cout << "cos(51.3) = " << cos(51.3,0.0000001) << endl;
    cout << "arctg(46.7) = " << arctg(46.7,0.0000001) << endl;
    cout << "ln(102.3) = " << ln(102.3,0.0000001) << endl;
    return 0;
}
