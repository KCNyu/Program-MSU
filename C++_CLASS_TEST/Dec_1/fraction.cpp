/*================================================================
* Filename:fraction.cpp
* Author: KCN_yu
* Createtime:Sun 29 Nov 2020 11:33:16 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class fraction
{
private:
    int num;
    int dem;
public:
    fraction(int a, int b);
    void print(){ cout << num << endl << dem << endl; }
};
fraction::fraction(int a, int b = 1){
    //for(int i = a; i >= 1; i--){
    //    if((a%i == 0)&&(b%i == 0)){
    //        a = a/i;
    //        b = b/i;
    //    }
    //}
    //num = a;
    //dem = b;
    int t = __gcd(a,b);
    num = a/t;
    dem = b/t;
}
int main(int argc, char *argv[])
{
    fraction a(16,24);
    a.print();
    return 0;
}
