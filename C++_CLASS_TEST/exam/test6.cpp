/*================================================================
* Filename:test6.cpp
* Author: KCN_yu
* Createtime:Wed 30 Dec 2020 04:36:56 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
void f(const char* s){}
void f(int a = 0, int b = 0){}
int main(int argc, char *argv[])
{
    f ("string");
    f (200);
    f ('+', 300); f ();
    return 0;
}

