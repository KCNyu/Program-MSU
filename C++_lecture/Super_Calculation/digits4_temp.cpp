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
    int a,b,c,d,count = 0;
    for(a = 0; a <= 9; a++){
        for(b = 0; b <= 9; b++){
            for(c = 0; c <= 9; c++){
                for(d = 0; d <= 9; d++){
                    if(a == b+c+d){
                        count++;
                        continue;
                    }       
                    if(b == a+c+d){
                        count++;
                        continue;
                    }       
                    if(c == b+a+d){
                        count++;
                        continue;
                    }       
                    if(d == b+c+a){
                        count++;
                        continue;
                    }       
                    if(a+b == c+d){
                        count++;
                        continue;
                    }       
                    if(a+c == b+d){
                        count++;
                        continue;
                    }       
                    if(a+d == b+c){
                        count++;
                        continue;
                    }       
                    if(b+c == a+d){
                        count++;
                        continue;
                    }       
                    if(b+d == c+a){
                        count++;
                        continue;
                    }       
                    if(c+d == a+b){
                        count++;
                        continue;
                    }       
                }
            }
        }
    }
    cout << "count = "<<count << endl;
}
