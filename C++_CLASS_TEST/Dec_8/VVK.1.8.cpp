/*================================================================
* Filename:VVK.1.8.cpp
* Author: KCN_yu
* Createtime:Sun 06 Dec 2020 09:12:59 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class B{
private:
    int num;
public:
    B(int n1, int n2 = 5){ num = n1 + n2; }
    B(const B& b){ num = b.num;}
    B& operator+=(const B& b){ num += b.num; return *this; }
    int get(){ return num; }
};
int main(int argc, char *argv[])
{
    B b1 (1), b2(2,3), b3 (b1);
    b1 += b2 += b3;
    cout << b1.get() << ' ' << b2.get() << ' ' << b3.get () << endl;
    return 0;
}
