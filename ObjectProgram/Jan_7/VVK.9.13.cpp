/*================================================================
* Filename:VVK.9.13.cpp
* Author: KCN_yu
* Createtime:Tue 05 Jan 2021 10:36:42 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;
int f(const list<int>& lst){
    int S=0;
    list<int> :: const_iterator p = lst.begin();
    while(p != lst.end()){
        if(*p > 0) S++;
        p++;
    }
    return S;
}
int main(int argc, char *argv[])
{
    list<int> l = {1,2,-3,4,5};
    cout << f(l) << endl;
    return 0;
}
