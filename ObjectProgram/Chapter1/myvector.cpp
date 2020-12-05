/*================================================================
* Filename:myvector.cpp
* Author: KCN_yu
* Createtime:Sun 29 Nov 2020 11:57:50 PM CST
================================================================*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <cmath>
using namespace std;

class myvector
{
private:
    int len;
    int *v;
public:
    myvector();
    myvector(const myvector &a){
        //v = new int[len*sizeof(int)];
        v = new int[(len = a.len)];
        //memcpy(v,a.v,len*sizeof(int));
        for (int i = 0; i < len; ++i) {
            v[i] = a.v[i];
        }
    }
    myvector(const int *num, const int l){
        v = new int[len = l];
        memcpy(v,num,len*sizeof(int));
    }
    myvector& next();
    double module() { return sqrt((*this) * (*this)); }
    void print() { for (int i = 0; i < len; ++i) cout << v[i] << " "; cout << endl; }
    int operator*(const myvector &b);
    myvector operator*(int c);
    myvector operator+(const myvector &b);
};
/*
myvector myvector::next(){
    for(int i = 0; i < len; ++i) v[i] += 1;
}*/
myvector& myvector::next(){
    for(int i = 0; i < len; ++i) v[i] = v[i]+1;
    return *this;
}
int myvector::operator*(const myvector &b){
    if(len != b.len) throw "len != len";
    int sum = 0;
    for(int i = 0; i < len; ++i) sum += v[i]*b.v[i];
    return sum;
}
myvector myvector::operator*(int c){
    myvector res(*this);
    for(int i = 0; i < len; ++i) res.v[i] *= c;
    return res;
}
myvector myvector::operator+(const myvector &b){
    if(len != b.len) throw "len != len";
    myvector res(*this);
    for(int i = 0; i < len; ++i) res.v[i] = v[i]+b.v[i];
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
    cout << v2.module() << endl;
    myvector v3 = v1+v2;
    v3.print();
    myvector v4 = v1*3;
    v4.print();
    /*
    myvector v3 = (v1+v2)*2;
    v3.print();
    */
    //cout << v1*v2 << endl;
    /*
    myvector v4 = v3.next(v3);
    v4.print();
    myvector v5 = v1;
    v5.print();
    cout << v5.module() << endl;
    myvector v6(num1,5);
    v6.print();
    v6.next().next();
    v6.print();
    */
    return 0;
}
