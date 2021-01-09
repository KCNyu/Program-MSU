/*================================================================
* Filename:VVK.9.14.cpp
* Author: KCN_yu
* Createtime:Tue 05 Jan 2021 10:50:27 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
void f(const vector<bool>& vec){
    int t = 0;
    int f = 0;
    vector<bool>::const_iterator p = vec.begin();
    while(p != vec.end()){
        if(*p) t++;
        else f++;
        p++;
    }
    cout << "t: " << t << endl;
    cout << "f: " << f << endl;
}
int main(int argc, char *argv[])
{
    vector<bool> v = {true,false,true};
    f(v);
    return 0;
}
