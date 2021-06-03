/*************************************************************************
	> File Name: digits1.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Oct 2019 03:23:28 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d,e,f,count = 0;
    for(a = 0; a <= 9; a++){
        for(b = 0; b <= 9; b++){
            for(c = 0; c <= 9; c++){
                for(d = 0; d <= 9; d++){
                    for(e = 0; e <= 9; e++){
                        for(f = 0; f <= 9; f++){
                            if(a == b+c+d+e+f){
                                count++;
                                continue;
                            }
                            if(b == a+c+d+e+f){
                                count++;
                                continue;
                            }
                            if(c == b+a+d+e+f){
                                count++;
                                continue;
                            }
                            if(d == b+c+a+e+f){
                                count++;
                                continue;
                            }
                            if(e == b+c+d+a+f){
                                count++;
                                continue;
                            }
                            if(f == b+c+d+e+a){
                                count++;
                                continue;
                            }
                           /* if(a+b == c+d+e+f){
                                count++;
                                continue;
                            }
                            if(a+c == b+d+e+f){
                                count++;
                                continue;
                            }
                            if(a+d == b+c+e+f){
                                count++;
                                continue;
                            }
                            if(a+e == b+c+d+f){
                                count++;
                                continue;
                            }
                            if(a+f == b+c+d+e){
                                count++;
                                continue;
                            }
                            if(b+c == a+d+e+f){
                                count++;
                                continue;
                            }
                            if(b+d == a+c+e+f){
                                count++;
                                continue;
                            }
                            if(b+e == a+c+d+f){
                                count++;
                                continue;
                            }
                            if(b+f == a+c+d+e){
                                count++;
                                continue;
                            }
                            if(c+d == b+a+e+f){
                                count++;
                                continue;
                            }
                            if(c+e == b+a+d+f){
                                count++;
                                continue;
                            }
                            if(c+f == b+a+d+e){
                                count++;
                                continue;
                            }
                            if(d+e == b+c+a+f){
                                count++;
                                continue;
                            }
                            if(d+f == b+c+a+e){
                                count++;
                                continue;
                            }
                            if(e+f == b+c+d+a){
                                count++;
                                continue;
                            }
                            if(a+b+c == d+e+f){
                                count++;
                                continue;
                            }
                            if(a+b+d == c+e+f){
                                count++;
                                continue;
                            }
                            if(a+b+e == c+d+f){
                                count++;
                                continue;
                            }
                            if(a+b+f == c+d+e){
                                count++;
                                continue;
                            }
                            if(a+c+d == b+e+f){
                                count++;
                                continue;
                            }
                            if(a+c+e == b+d+f){
                                count++;
                                continue;
                            }
                            if(a+c+f == b+d+e){
                                count++;
                                continue;
                            }
                            if(a+d+e == b+c+f){
                                count++;
                                continue;
                            }
                            if(a+d+f == b+c+e){
                                count++;
                                continue;
                            }
                            if(a+e+f == b+c+d){
                                count++;
                                continue;
                            }
                            if(b+c+d == a+e+f){
                                count++;
                                continue;
                            }
                            if(b+c+e == a+d+f){
                                count++;
                                continue;
                            }
                            if(b+c+f == a+d+e){
                                count++;
                                continue;
                            }
                            if(b+d+e == c+a+f){
                                count++;
                                continue;
                            }
                            if(b+d+f == a+c+e){
                                count++;
                                continue;
                            }
                            if(b+e+f == a+c+d){
                                count++;
                                continue;
                            }
                            if(c+d+e == b+a+f){
                                count++;
                                continue;
                            }
                            if(c+d+f == a+b+e){
                                count++;
                                continue;
                            }
                            if(c+e+f == b+d+a){
                                count++;
                                continue;
                            }
                            if(d+e+f == b+c+a){
                                count++;
                                continue;
                            }*/
                        }
                    }
                }
            }
        }
    }
    cout << "count = "<< count << endl;
    return 0;
}
