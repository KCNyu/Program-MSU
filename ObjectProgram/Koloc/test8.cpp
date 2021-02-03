/*================================================================
* Filename:test8.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 04:31:37 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;
int main(int argc, char *argv[])
{
    list<int> l;
    for( list <int>::iterator p = l.begin(); p!=l.end(); p++) { cout << *p << endl; }
    return 0;
}

