/*================================================================
* Filename:VVK.1.13.cpp
* Author: KCN_yu
* Createtime:Sun 06 Dec 2020 08:31:38 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct mystr {
int a, b;
string s;
};

int i = sizeof(mystr);

int f(mystr s) {
return i;
}
int main(int argc, char *argv[])
{
    mystr s;
    cout << f(s) << endl;
    return 0;
}
