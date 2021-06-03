/*================================================================
* Filename:VVK.1.4.cpp
* Author: KCN_yu
* Createtime:Sun 06 Dec 2020 08:48:30 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class A{
    private:
        int num;
    public:
        A (int n = 0){ num = n; }
        A& operator*=(const A& a){ num *= a.num; return *this; }
        int get(){ return num; }
};
int main(int argc, char *argv[])
{
    A a1 (5), a2 = 3;
    a1 *= 10;
    a2 *= a1 *= 2;
    cout << a1.get() << endl << a2.get() << endl;
    return 0;
}
