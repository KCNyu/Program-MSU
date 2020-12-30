/*================================================================
 * Filename:VVK.8.4.cpp
 * Author: KCN_yu
 * Createtime:Sun 27 Dec 2020 08:03:54 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

template <class T>
T max1(char* x,char* y) {
    cout << 1 << endl;
    return strcmp(x,y) < 0 ? x : y;
}
template <class T>
T max1 (T& x, T& y) {
    cout << 2 << endl;
    return x > y ? x : y;
}
char* max1(char* x,char* y) {
    return strcmp(x,y) < 0 ? x : y;
}
int main () {
    double x = 1.5, y = 2.8, z;
    int i = 5, j = 12, k;
    char * s1 = "abft";
    char * s2 = "abxde", * s3;
    z = max1 (x, y);
    cout << "z = "<< z << endl;
    k = max1 <int>(i, j);
    cout << "k = "<< k << endl;
    z = max1 (x, (double &) i);
    cout << "z = "<< z << endl;
    z = max1 (y, (double &) j);
    cout << "z = "<< z << endl;
    s3 = max1 <char*>(s1, s2);
    cout << "s3 = "<< s3 << endl;
    s3 = max1 (s1, s2);
    cout << "s3 = "<< s3 << endl;
    cout << "Выбор сделан!" << endl; return 0;
}
