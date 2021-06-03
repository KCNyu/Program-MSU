/*************************************************************************
	> File Name: digits.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Oct 2019 12:19:03 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d,e,f;
    int count = 0;
    for(a = 0; a <= 9; a++){
        for(b = -9; b <= 9; b++){
            for(c = -9; c <= 9; c++){
                int bc = b+c;
                for(d = -9; d <= 9; d++){
                    int bcd = bc+d;
                    for(e = -9;e <= 9; e++){
                        int bcde = bcd + e;
                        for(f = -9; f <= 9; f++){
                            int bcdef = bcde + f;
                            if(a == bcdef){
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << count << endl;
    return 0;
}
