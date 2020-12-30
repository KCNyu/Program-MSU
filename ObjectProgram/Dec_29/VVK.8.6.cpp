/*================================================================
 * Filename:VVK.8.6_t.cpp
 * Author: KCN_yu
 * Createtime:Sun 27 Dec 2020 11:27:46 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

template <class T> class fr {
    T a,b;
    public:
    fr():a(0),b(1){}
    fr(T x, T y):a(x),b(y){}
    fr operator+(const fr & y);
    fr operator-(const fr & y);
    fr operator*(const fr & y);
    fr operator/(const fr & y);
    fr& operator=(const fr & y);
    fr& operator+=(const fr & y);
    fr& operator-=(const fr & y);
    fr& operator*=(const fr & y);
    fr& operator/=(const fr & y);
    fr operator+(const T & y);
    fr operator-(const T & y);
    fr operator*(const T & y);
    fr operator/(const T & y);
    fr& operator=(const T & y);
    fr& operator+=(const T & y);
    fr& operator-=(const T & y);
    fr& operator*=(const T & y);
    fr& operator/=(const T & y);
    fr<T>& operator+();
    fr<T> operator-();
    fr<T>& operator++(){ a += b; return *this; }
    fr<T>& operator--(){ a -= b; return *this; }
    fr<T> operator++(T){ fr<T> y = *this; y.a += y.b; return y; }
    fr<T> operator--(T){ fr<T> y = *this; y.a -= y.b; return y; }
    bool operator==(const fr & y){ return a/b == y.a/y.b; }
    bool operator!=(const fr & y){ return a/b != y.a/y.b; }
    bool operator>(const fr & y){ return a/b > y.a/y.b; }
    bool operator<(const fr & y){ return a/b < y.a/y.b; }
    bool operator>=(const fr & y){ return a/b >= y.a/y.b; }
    bool operator<=(const fr & y){ return a/b <= y.a/y.b; }
    bool operator==(const T & y){ return a/b == y; }
    bool operator!=(const T & y){ return a/b != y; }
    bool operator>(const T & y){ return a/b > y; }
    bool operator<(const T & y){ return a/b < y; }
    bool operator>=(const T & y){ return a/b >= y; }
    bool operator<=(const T & y){ return a/b <= y; }
    template <class F>
        friend ostream& operator<<(ostream& os, const fr<F> &y);
};
template <class T>
fr<T> fr<T>::operator+(const fr& y){
    fr z;
    z.a=a*y.b+b*y.a;
    z.b=y.b*b;
    return +z;
}
template <class T>
fr<T> fr<T>::operator-(const fr& y){
    fr z;
    z.a=a*y.b-b*y.a;
    z.b=y.b*b;
    return +z;
}
template <class T>
fr<T> fr<T>::operator*(const fr& y){
    fr z;
    z.a=a*y.a;
    z.b=b*y.b;
    return +z;
}
template <class T>
fr<T> fr<T>::operator/(const fr& y){
    fr z;
    z.a=a*y.b;
    z.b=b*y.a;
    return +z;
}
template <class T>
fr<T>& fr<T>::operator=(const fr& y){
    cout << "assign" << endl;
    a = y.a;
    b = y.b;
    return *this;
}
template <class T>
fr<T>& fr<T>::operator+=(const fr& y){
    a=a*y.b+b*y.a;
    b=b*y.b;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator-=(const fr& y){
    a=a*y.b-b*y.a;
    b=b*y.b;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator*=(const fr& y){
    a=a*y.a;
    b=b*y.b;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator/=(const fr& y){
    a=a*y.b;
    b=b*y.a;
    return +(*this);
}
template <class T>
fr<T> fr<T>::operator+(const T &y){
    fr z;
    z.a=a+b*y;
    z.b=b;
    return +z;
}
template <class T>
fr<T> fr<T>::operator-(const T &y){
    fr z;
    z.a=a+b*y;
    z.b=b;
    return +z;
}
template <class T>
fr<T> fr<T>::operator*(const T &y){
    fr z;
    z.a=a*y;
    z.b=b;
    return +z;
}
template <class T>
fr<T> fr<T>::operator/(const T &y){
    fr z;
    z.a=a;
    z.b=b*y;
    return +z;
}
template <class T>
fr<T>& fr<T>::operator=(const T &y){
    cout << "assign" << endl;
    a=y;
    b=1;
    return *this;
}
template <class T>
fr<T>& fr<T>::operator+=(const T &y){
    a += b*y;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator-=(const T &y){
    a -= b*y;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator*=(const T &y){
    a *= y;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator/=(const T &y){
    b *= y;
    return +(*this);
}
template <class T>
fr<T>& fr<T>::operator+(){
    T tmp = __gcd(a,b);
    a /= tmp;
    b /= tmp;
    return *this;
}
template <class T>
fr<T> fr<T>::operator-(){
    fr w(-a,b);
    return w;
}

///////////////////////////////////////////////////////////////////////////////////

template <class T>
ostream& operator<< (ostream& os, const fr<T> &y){
    os << y.a << "/" << y.b << endl;
    return os;
}

int main() {
    fr<int> a(25,10),b(18,24); int i;
    cout << a+b;
    cout << a+i;
    cout << +(a+b);
    cout << -(a+i);
    cout << +(a-b);
    cout << -(a-i);
    cout << a*b;
    fr<int> c;
    c = a;
    cout << c;
    fr<int> d = c; //doesn't have assign
    cout << d;
    //fr<int> e = 100; // doesn't have consturction from int to fr<int>
    fr<int> e;
    e = 100; // == e.=(100);
    cout << e;
    a += b;
    cout << a;
    a -= b;
    cout << a;
    a *= b;
    cout << a;
    a /= b;
    cout << a;
    cout << (a!=b) << endl;
    ++a;
    cout << a;
    --a;
    cout << a;
    cout << a++;
    cout << a--;
    return 0;
}
