/*================================================================
* Filename:test1.cpp
* Author: KCN_yu
* Createtime:Wed 25 Nov 2020 02:51:06 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
/*
void swap(int& a, int& b){
    a = b-a;
    b = b-a;
    a = a+b;
}

void swap(int& a, int& b){
    a = a^b;
    b = a^b;
    a = a^b;
}
*/
void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
int main(int argc, char *argv[])
{
    //cout << "Hello,World" << endl;
    /*
    int a,b;
    cin >> a >> b;

    cout << "a = " << a << endl << "b = " << b << endl;
    swap(a,b);
    cout << "a = " << a << endl << "b = " << b << endl;
    */
    int a = 1;
    int& refa = a;
    refa = a+1;
    cout << a << endl;
    cout << refa << endl;
    return 0;
}
