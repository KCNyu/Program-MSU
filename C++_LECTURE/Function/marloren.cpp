/*================================================================
* Filename:marloren.cpp
* Author: KCN_yu
* Createtime:Wed 11 Mar 2020 09:35:43 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

double F(double X){
    return 1-2*log(X)+log(X)*log(X)-3*X+2*X*log(X);
}

double Root(double f(double), double L, double R, double eps){
    double M = (L+R) / 2.0;
    if(f(L)*f(R) >= 0) return M;
    if(R - L < eps) return M;
    if(f(L)*f(M) < 0) return Root(f,L,M,eps);
    return Root(f,M,R,eps);
}
double Formula_exponent(double x, double eps){
    double result = 0;
    double term = 1.0;
    int i = 1;
    while(term > eps){
        result += term;
        term = term*x/i++;
    }
    return result;
}
double Formula_cos(double x, double eps){
    double result = 0;
    double term = 1.0;
    int i = 1;
    while(abs(term) > eps){
        result += term;
        term = (-1)*term*x*x/(i*(i+1));
        i += 2;
    }
    return result;
}
double Formula_sin(double x, double eps){
    double result = 0;
    double term = x;
    int i = 2;
    while(abs(term) > eps){
        result += term;
        term = (-1)*term*x*x/(i*(i+1));
        i += 2;
    }
    return result;
}
double Formula_ln(double x, double eps){
}

double Formula_arctg(double x, double eps){
    double result = 0;
    double term = x;
    int i = 3;
    while(abs(term) > eps){
        result += term;
        term = (-1)*term*x*x*(i-2)/i;
        i += 2;
    }
    return result;
}// 0 <= x <= 1;

/*
double Root(double L, double R, double eps){
    double M = (L+R) / 2.0;
    return F(L)*F(R)>=0 ? M : R-L < eps ? M : F(L)*F(M)<0 ? Root(L,M,eps) : Root(M,R,eps);
}
*/
int main(int argc, char *argv[])
{
    cout << Root(F,4.0, 5.0, 0.00001) << endl;
    cout << "e^1.47 = " << Formula_exponent(1.47,0.00001) << endl;
    cout << "arctg(0.89) = " << Formula_arctg(0.89,0.00001) << endl;
    cout << "sin(0.73) = " << Formula_sin(40,0.00001) << endl;
    cout << "cos(0.19) = " << Formula_cos(0.19,0.00001) << endl;
    //cout << "ln(100) = " << Formula_arctg(1,0.00001) << endl;
    return 0;
}
