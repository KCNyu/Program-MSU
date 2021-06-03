/*================================================================
 * Filename:test14.cpp
 * Author: KCN_yu
 * Createtime:Wed 23 Dec 2020 04:11:52 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
template <class T> T m1 (T a, T b){
    cout << "m1_1\n";
    return a < b ? b : a;
}
template <class T, class B> T m1 (T a, T b, B c){
    cout << "m1_2\n";
    c = 0; return a < b ? b : a;
}
template <class T, class Z> T m1 (T a, Z b){
    cout << "m1_3\n";
    return a < b ? b : a;
}
int m1(int a, int b){
    cout << "m1_4\n";
    return a < b ? b : a;
}
int m1(int a, double b){
    cout << "m1_5\n";
    return a;
}
int main ()
{                                       // Если убрать первый шаблон:
    int i;
    m1 <int> (2, 3);        // m1_1     // m1_3
    m1 <int, int> (2, 3);   // m1_3     // m1_3
    m1 <int> (2, 3, i);     // m1_2     // m1_2
    m1 (1, 1);              // m1_4     // m1_4
    m1 (1.3, 1);            // m1_3     // m1_3
    m1 (1.3, 1.3);          // m1_1     // m1_3
    return 0;
}

