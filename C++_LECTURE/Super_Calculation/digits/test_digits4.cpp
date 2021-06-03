/*================================================================
* Filename:test_digits4.cpp
* Author: KCN_yu
* Createtime:Mon 02 Mar 2020 05:43:30 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int count = 0;
    int sum = 0;
    for(int i = 0; i <= 36; i++){
        for(int a = 0; a <= 9; a++){
            for(int b = 0; b <= 9; b++){
                for(int c = 0; c <= 9; c++){
                    for(int d = 0; d <= 9; d++){
                        if(i == a+b+c+d) count++;
                    }
                }
            }
        }
        cout << "count_" << i << " = " << count << endl;
        sum += count*count;
        count = 0;
    }
    cout << "sum = " << sum << endl;
    return 0;
}
