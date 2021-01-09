/*================================================================
* Filename:VVK.9.31.cpp
* Author: KCN_yu
* Createtime:Tue 05 Jan 2021 12:02:07 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>

using namespace std;

template <typename Container>
void f(const Container& c){
    typename Container::const_reverse_iterator i = c.rbegin();
    i++;
    while(i != c.rend()){
        cout << *i << endl;
        i++;
        if(i == c.rend()) break;
        i++;
    }
}
int main(int argc, char *argv[])
{
    list<int> l = {1,2,3,4,5};
    vector<char> v = {'a','b','c','d'};
    f(l);
    f(v);
    return 0;
}


