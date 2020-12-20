/*================================================================
* Filename:temp.cpp
* Author: KCN_yu
* Createtime:Wed 16 Dec 2020 02:05:54 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
/*
void f(double a, int b = 0){
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}
void f(int c, const char* str){
    cout << "c = " << c << endl;
    cout << "d = " << str << endl;
}
void f(int a = 0, int b = 0){
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}
void f(const char* str){
    cout << "d = " << str << endl;
}
void f(int a, const char* str){
    //cout << "a = " << a << endl;
    //cout << "str = " << str << endl;
    cout << "1" << endl;
}
void f(const char* str, int b){
    //cout << "b = " << b << endl;
    //cout << "str = " << str << endl;
    cout << "2" << endl;
}
struct X{
    X(int);
    operator int();
} x;
//void f(X a,const char* str);
void f(int a,const char* str);
void f(const char* str);
*/
void f(long int a = 0,const char* str = 0);
void f(const char* str);
int main(int argc, char *argv[])
{
    /*
    f(1);
    f('+','+');
    f(2.3);
    f(3,"str");
    f();
    f("abc");
    f(2);
    f('+',3);
    f(0,1);
    f(1,0);
    f(0,"m");
    f("n",0);
    f("p");
    f(x,0);
    f(0,0);
    f(x,"q");
    f(1,"r");
    */
    f(1000000000000);
    f(1);
    f();
    f(0, 0);
    f("t");
    f(1,"u");
    return 0;
}
