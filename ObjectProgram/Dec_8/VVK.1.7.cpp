/*================================================================
* Filename:VVK.1.7.cpp
* Author: KCN_yu
* Createtime:Sun 06 Dec 2020 08:56:28 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A{
    private:
        int num;
    public:
        A (int n = 7){ num = n; }
        A& operator*=(const A& a){ num *= a.num; return *this; }
        int get(){ return num; }
};
int main(int argc, char *argv[])
{
    A a1(5), a2 = 4, a3;
    a2 *= a1 *= 3;
    cout << a1.get( ) << ' ' << a2.get() << ' ' << a3.get( ) << endl;
    return 0;
}
