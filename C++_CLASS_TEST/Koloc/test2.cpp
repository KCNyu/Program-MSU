/*================================================================
* Filename:test2.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 03:55:12 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>

using namespace std;

void g(char* a,long double b){}
void g(std::vector<int> a,int b){}
void g(std::list<int> a, short b){}
int main(int argc, char *argv[])
{
    g(std::vector<int>(),1.2);
    return 0;
}
