/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Thu 26 Nov 2020 06:31:44 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
class Box{
private:
    int l;
    int w;
    int h;
public:
    int volume() const{ return l*w*h; }
    Box(int a, int b, int c){l = a; w = b; h = c;}
    Box(int s){l = w = h = s; }
    Box(){ w = h = 1; l = 2; }
    int get_l() const{ return l; }
    int get_w() const{ return w; }
    int get_h() const{ return h; }
    Box(const Box& a){ l = a.l; w = a.w; h = a.h; }
    Box & operator=(const Box &a){l = a.l; w= a.w; h = a.h; }
};
int main(int argc, char *argv[])
{
    Box a(1,2,3);
    Box b(a);
    Box c;
    c = b;
    Box d = b;
    cout << d.get_h() << endl;
    return 0;
}
