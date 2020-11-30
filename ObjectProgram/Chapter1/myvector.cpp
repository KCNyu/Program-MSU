/*================================================================
* Filename:myvector.cpp
* Author: KCN_yu
* Createtime:Sun 29 Nov 2020 11:57:50 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <memory.h>
using namespace std;

class myvector
{
private:
    int len;
    int *v;
public:
    myvector();
    myvector(const myvector &a){
        len = a.len;
        v = new int[len*sizeof(int)];
        memcpy(v,a.v,len*sizeof(int));
    }
    myvector(const int *num, const int l){
        v = new int[(len = l)*sizeof(int)];
        memcpy(v,num,len*sizeof(int));
    }
    myvector next(const myvector &a);
    void print() { for (int i = 0; i < len; ++i) cout << v[i] << endl; }
    friend int operator*(const myvector &a, const myvector &b);
    friend myvector operator*(const myvector &a, const int c);
    friend myvector operator+(const myvector &a, const myvector &b);
};

myvector myvector::next(const myvector &a){
    myvector res(a);
    for(int i = 0; i < a.len; ++i) res.v[i] = a.v[i]+1;
    return res;
}
int operator*(const myvector &a, const myvector &b){
    if(a.len != b.len) throw "len != len";
    int sum = 0;
    for(int i = 0; i < a.len; ++i) sum += a.v[i]*b.v[i];
    return sum;
}
myvector operator*(const myvector &a, const int c){
    myvector res(a);
    for(int i = 0; i < a.len; ++i) res.v[i] *= c;
    return res;
}
myvector operator+(const myvector &a, const myvector &b){
    if(a.len != b.len) throw "len != len";
    myvector res(a);
    for(int i = 0; i < a.len; ++i) res.v[i] = a.v[i]+b.v[i];
    return res;
}
int main(int argc, char *argv[])
{
    int num1[5] = {1,2,3,4,5};
    int num2[5] = {5,4,3,2,1};
    myvector v1(num1,5);
    v1.print();
    myvector v2(num2,5);
    v2.print();
    cout << v1*v2 << endl;
    myvector v3 = (v1+v2)*2;
    v3.print();
    myvector v4 = v3.next(v3);
    v4.print();
    return 0;
}
