/*================================================================
 * Filename:test13.cpp
 * Author: KCN_yu
 * Createtime:Wed 23 Dec 2020 04:09:07 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

template < class T >
T max (T & x, T & y) {
    return x > y ? x : y;
}
int main ( ) {
    double x = 1.5, y = 2.8, z;
    int i = 5, j = 12, k;
    char * s1 = "abft";
    char * s2 = "abxde", * s3;
    z = max ( x, y ); // max <double>
    cout << z << endl;
    k = max < int > (i, j); // max <int>
    cout << k << endl;
    //z = max (x, i); // Err! - неоднозначный выбор параметров
    z = max < double > ( y, j );
    cout << z << endl;
    s3 = max (s2, s1); // max < char * >,
    cout << s3 << endl;
    //// но происходит сравнение адресов
    return 0;
}
