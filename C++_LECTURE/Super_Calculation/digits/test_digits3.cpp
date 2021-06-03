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
    clock_t begintime = clock();
    int count = 0;
    for(int a = 0; a <= 9; a++){
        for(int b = 0; b <= 9; b++){
            int ab = a+b;
            for(int c = 0; c <= 9; c++){
                int abc = ab+c;
                for(int d = 0; d <= 9; d++){
                    for(int e = 0; e <= 9; e++){
                        for(int f = 0; f <= 9; f++){
                            if(abc == d+e+f) count++;
                        }
                    }
                }
            }
        }
    }
    cout << "count = " << count << endl;
    clock_t endtime = clock();
    cout << "time: " << endtime-begintime << endl;
    return 0;
}
