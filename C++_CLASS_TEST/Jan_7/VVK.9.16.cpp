/*================================================================
* Filename:VVK.9.16.cpp
* Author: KCN_yu
* Createtime:Tue 05 Jan 2021 11:00:22 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
void f(vector<char> vec){
    vec.erase(vec.begin()+1);
    vector<char>::reverse_iterator iter = vec.rbegin();
    while(iter != vec.rend()){
        cout << *iter << endl;
        iter++;;
    }
}
int main(int argc, char *argv[])
{
    vector<char> v = {'a','b','c','d'};
    f(v);
    return 0;
}

