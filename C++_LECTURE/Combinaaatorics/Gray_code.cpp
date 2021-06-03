/*************************************************************************
	> File Name: Gray_code.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Nov 2019 08:10:28 AM CST
 ************************************************************************/

#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
void Change(char *c){
    *c = *c == '0' ? '1' : '0';
}
int main()
{
    int n;//length of Gray code
    scanf("%d",&n);
    int total = pow(2.0,(double)n);
    char gray_code[total][n+1];
    
    for(int i = 0; i < n; i++){
        gray_code[0][i] = '0';
    }//initialize
    for(int i = 0; i < total; i++){
        gray_code[i][n] = '\0';
    }
    for(int i = 1; i < total; i++){
        strcpy(gray_code[i],gray_code[i-1]); 
        if(i % 2 != 0){
            Change(&gray_code[i][n-1]);
        }
        else{
            for(int j = n-1; j > 0; j--){
                if(gray_code[i][j] == '1'){
                    Change(&gray_code[i][j-1]);
                    break;
                }
            }
        }
    }

    for(int i = 0; i < total; i++){
        cout << gray_code[i] << endl;
    }

    return 0;
}
