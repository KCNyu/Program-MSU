/*================================================================
* Filename:VVK.1.14.cpp
* Author: KCN_yu
* Createtime:Thu 10 Dec 2020 07:15:50 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class smartstr
{
private:
    string s;
public:
    smartstr(string t){ t = s; }
};

int main(int argc, char *argv[])
{
    smartstr s1("hello");
    //smartstr s2 = new smartstr[1];
    return 0;
}
