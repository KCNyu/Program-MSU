/*================================================================
* Filename:IntegerPatition.cpp
* Author: KCN_yu
* Createtime:Sat 12 Sep 2020 12:47:35 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX 255

int IntegerPatition(int n){
    int dp[MAX][MAX];
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == 1 || j == 1) dp[i][j] = 1;
            else if(i == j) dp[i][j] = 1 + dp[i][j-1];
            else if(i < j) dp[i][j] = dp[i][i];
            else dp[i][j] = dp[i-j][j] + dp[i][j-1];
        }
    }
    return dp[n][n];
}
int main(int argc, char *argv[])
{
    for(int i = 1; i <= 20; i++)
        cout << IntegerPatition(i) << endl;
    return 0;
}
