/*================================================================
* Filename:test7.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 04:30:21 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

void f(int i){ cout << 1;}
void f(long l){ cout << 2;}
template<class T>
void f(T t){ cout << 3;}
int main(int argc, char *argv[])
{
    short s = 1;
    f(s);
    f(1L);
    return 0;
}
