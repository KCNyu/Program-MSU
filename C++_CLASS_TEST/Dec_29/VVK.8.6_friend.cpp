/*================================================================
* Filename:VVK.8.6_friend.cpp
* Author: KCN_yu
* Createtime:Mon 28 Dec 2020 02:06:00 AM CST
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
    fr<T>& operator+();

    template <class F>
        friend fr<F> operator-(const fr<F> & y);
    template <class F>
        friend fr<F> operator+(const fr<F> & y, const fr<F> &z);
    template <class F>
        friend fr<F> operator-(const fr<F> & y, const fr<F> &z);
    template <class F>
        friend fr<F> operator*(const fr<F> & y, const fr<F> &z);
    template <class F>
        friend fr<F> operator/(const fr<F> & y, const fr<F> &z);
    template <class F>
        friend fr <F> operator+(const fr<F> &z, const F &y);
    template <class F>
        friend fr <F> operator-(const fr<F> &z, const F &y);
    template <class F>
        friend fr <F> operator*(const fr<F> &z, const F &y);
    template <class F>
        friend fr <F> operator/(const fr<F> &z, const F &y);
    template <class F>
        friend fr <F>& operator++(fr<F> &z){ z.a += z.b; return z; }
    template <class F>
        friend fr <F>& operator--(fr<F> &z){ z.a -= z.b; return z; }
    template <class F>
        friend bool operator==(const fr<F> & y, const fr<F> &z){ return y.a/y.b == z.a/z.b; }
    template <class F>
        friend bool operator!=(const fr<F> & y, const fr<F> &z){ return y.a/y.b != z.a/z.b; }
    template <class F>
        friend bool operator>(const fr<F> & y, const fr<F> &z){ return y.a/y.b > z.a/z.b; }
    template <class F>
        friend bool operator<(const fr<F> & y, const fr<F> &z){ return y.a/y.b < z.a/z.b; }
    template <class F>
        friend bool operator>=(const fr<F> & y, const fr<F> &z){ return y.a/y.b >= z.a/z.b; }
    template <class F>
        friend bool operator<=(const fr<F> & y, const fr<F> &z){ return y.a/y.b <= z.a/z.b; }
    template <class F>
        friend bool operator==(const fr<F> &z, const F &y){ return z.a/z.b == y; }
    template <class F>
        friend bool operator!=(const fr<F> &z, const F &y){ return z.a/z.b != y; }
    template <class F>
        friend bool operator>(const fr<F> &z, const F &y){ return z.a/z.b > y; }
    template <class F>
        friend bool operator<(const fr<F> &z, const F &y){ return z.a/z.b < y; }
    template <class F>
        friend bool operator>=(const fr<F> &z, const F &y){ return z.a/z.b >= y; }
    template <class F>
        friend bool operator<=(const fr<F> &z, const F &y){ return z.a/z.b <= y; }
    template <class F>
        friend ostream& operator<<(ostream& os, const fr<F> &y);
};
template <class T>
fr<T>& fr<T>::operator+(){
    T tmp = __gcd(a,b);
    a /= tmp;
    b /= tmp;
    return *this;
}
template <class T>
fr<T> operator-(const fr<T> &y){
    fr<T> w(-y.a,y.b);
    return w;
}

///////////////////////////////////////////////////////////////////////////////////

template <class T>
fr<T> operator+(const fr<T> &y, const fr<T> &z){
    fr<T> w;
    w.a=z.a*y.b+z.b*y.a;
    w.b=y.b*z.b;
    return +w;
}
template <class T>
fr<T> operator-(const fr<T> &y, const fr<T> &z){
    fr<T> w;
    w.a=z.a*y.b-z.b*y.a;
    w.b=y.b*z.b;
    return +w;
}
template <class T>
fr<T> operator*(const fr<T> &y, const fr<T> &z){
    fr<T> w;
    w.a=z.a*y.a;
    w.b=y.b*z.b;
    return +w;
}
template <class T>
fr<T> operator/(const fr<T> &y, const fr<T> &z){
    fr<T> w;
    w.a=z.a*y.b;
    w.b=z.b*y.a;
    return +w;
}
template <class T>
fr<T> operator+(const fr<T> &z, const T &y){
    fr<T> w;
    w.a=z.a+z.b*y;
    w.b=z.b;
    return +w;
}
template <class T>
fr<T> operator-(const fr<T> &z, const T &y){
    fr<T> w;
    w.a=z.a-z.b*y;
    w.b=z.b;
    return +w;
}
template <class T>
fr<T> operator*(const fr<T> &z, const T &y){
    fr<T> w;
    w.a=z.a*y;
    w.b=z.b;
    return +w;
}
template <class T>
fr<T> operator/(const fr<T> &z, const T &y){
    fr<T> w;
    w.a=z.a;
    w.b=z.b*y;
    return +w;
}
template <class T>
ostream& operator<< (ostream& os, const fr<T> &y){
    os << y.a << "/" << y.b << endl;
    return os;
}
int main(int argc, char *argv[])
{
    fr<int> a(25,10),b(18,24); int i;
    cout << a+b;
    cout << a+i;
    cout << +(a+b);
    cout << -(a+i);
    cout << +(a-b);
    cout << -(a-i);
    cout << a*b;
    ++a;
    cout << a;
    return 0;
}
