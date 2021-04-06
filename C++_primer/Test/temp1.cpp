/*================================================================
* Filename:temp1.cpp
* Author: KCN_yu
* Createtime:Sun 21 Mar 2021 03:53:51 PM CST
================================================================*/

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    constexpr size_t sz = 5;
    int arr[sz] = {1,2,3,4,5};
    int *p = arr + 5;
    cout << *p << endl;
    int a = 1;
    cout << ('A' << 1) << endl;
    return 0;
}
