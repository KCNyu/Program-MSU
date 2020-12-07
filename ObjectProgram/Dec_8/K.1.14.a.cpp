/*================================================================
* Filename:K.1.14.cpp
* Author: KCN_yu
* Createtime:Sat 05 Dec 2020 02:07:00 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Ball
{
    private:
        string color;
        int size;
    public:
        Ball(string c = "white", int sz = 0){ color = c; size = sz; }
        Ball(int sz = 0){ color = "white"; size = sz; }
        int Getsize() { return size; }
        ~Ball(){ cout << color << endl; }
};

int smallest(Ball &t){ return t.Getsize(); }

template <typename Ball, typename... Argv>
int smallest(Ball &t, Argv& ...args){ return min(smallest(t),smallest(args...)); }

int main(int argc, char *argv[])
{
    Ball gb("green",20), wb(12), b(10);
    cout << "The smallest: " << smallest(gb,wb,b) << " end" << endl;
    return 0;
}
