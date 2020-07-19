/*================================================================
* Filename:test_digits2.cpp
* Author: KCN_yu
* Createtime:Mon 02 Mar 2020 05:43:30 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int count = 0;
    for(int a = 0; a <= 9; a++){
        for(int b = 0; b <= 9; b++){
            for(int c = 0; c <= 9; c++){
                for(int d = 0; d <= 9; d++){
                    if(a+b == c+d) count++;
                }
            }
        }
    }
    cout << "count = " << count << endl;
    return 0;
}
