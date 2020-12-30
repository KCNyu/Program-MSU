/*================================================================
 * Filename:test1.cpp
 * Author: KCN_yu
 * Createtime:Tue 29 Dec 2020 04:12:59 PM CST
 ================================================================*/

#include <iostream>
#include <list>

using namespace std;
int g (list <int> & lst){
        int S=0;
        list<int> :: iterator p = lst.begin();
        while (p != lst.end())
        {
            S += * p;
            cout << "*p = " << *p << endl;
            p++;
            if(p != lst.end()) p++;
        }
        return S;
};
int main(int argc, char *argv[])
{
    list<int> l = {1,2,3,4,5,6};
    cout << g(l) << endl;
    return 0;
}
