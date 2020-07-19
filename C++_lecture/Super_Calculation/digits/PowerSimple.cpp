/*================================================================
* Filename:PowerSimple.cpp
* Author: KCN_yu
* Createtime:Thu 05 Mar 2020 01:18:33 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

double My_pow(double A, int B){
    double result;
    if(B == 0) return 1;
    if(B == 1) return A;
    result = My_pow(A, B >> 1);
    result *= result; // result^2;
    if((B & 0x01) == 1)
        result *= A;
    return result;
}
double My_pow_temp(double A, int B){
    double Return = 1;
    double AAA = A;
    for(;;){
        if(B == 0) return Return;
        if(B%2) Return *= AAA;
        AAA *= AAA;
        B /= 2;
    }
}
double PowerSimple(double A, int B){
    double result = 1.0;
    for(int i = 1; i <= B; i++)
        result *= A;
    return result;
}

int main(int argc, char *argv[])
{
    double A = 1.0000017;
    int B = 725;
    double C = My_pow_temp(A,B);
    cout << "result = " << C << endl;
    return 0;
}
