/*================================================================
* Filename:Integral.cpp
* Author: KCN_yu
* Createtime:Mon 06 Apr 2020 09:55:59 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

double f1(double x){
    return 3/(pow(x-1,2)+1);
}
double f2(double x){
    return sqrt(x+0.5);
}
double f3(double x){
    return exp(-x);
}
double FindRoot(double f1(double), double f2(double), double a, double b, double eps){
    double x0 = a,x1;
    double d;
    do{
        x1 = x0-(b-x0)/((f1(b)-f2(b))-(f1(x0)-f2(x0)))*(f1(x0)-f2(x0));
        d = x1-x0;
        x0 = x1;
    }while(fabs(f1(x0)-f2(x0)) > eps && fabs(d) > eps);
    return x0;
}

double trapezoid(double a, double b, double f(double)){
    return (f(a)+f(b))*(b-a)/2;
}
double asr(double a, double b, double eps, double A, double f(double)){
    double c = a + (b-a)/2;
    double L = trapezoid(a,c,f), R = trapezoid(c,b,f);
    if(fabs(L+R-A) <= eps) return L+R+(L+R-A);
    return asr(a,c,eps,L,f) + asr(c,b,eps,R,f);
}
double Integral(double a, double b, double eps, double f(double)){
    return asr(a,b,eps,trapezoid(a,b,f),f);
}
double f_1_2(double x){
    return f1(x)-f2(x);
}
double f_1_3(double x){
    return f1(x)-f3(x);
}
int main(int argc, char *argv[])
{
    double eps = 0.00000001;

    double Root_1_2 = FindRoot(f1,f2,1,3,eps);
    double Root_1_3 = FindRoot(f1,f3,-1,0,eps);
    double Root_2_3 = FindRoot(f2,f3,0,1,eps);

    cout << "Root_1_2: " << Root_1_2 << endl;
    cout << "Root_1_3: " << Root_1_3 << endl;
    cout << "Root_2_3: " << Root_2_3 <<endl;

    double Square = Integral(Root_2_3,Root_1_2,eps,f_1_2) + Integral(Root_1_3,Root_2_3,eps,f_1_3);

    cout << "Square: " << Square << endl;

    return 0;
}
