/*================================================================
* Filename:Vision.cpp
* Author: KCN_yu
* Createtime:Sun 26 Jul 2020 12:05:38 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n,L;
    cin >> n >> L;
    vector<pair<int,int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        cin >> a[i].second;
    }
    vector<int> land(L);
    for(int i =0; i < n; i++){
        int l = max(a[i].first,0);
        int r = min(a[i].second,n);
        for(int j = l; j < r; j++)
            land[j] = max(land[j],r);
    }
    int ans = 0;
    int cur = 0;
    while(cur < L){
        if(land[cur] == 0){
            cout << -1 << endl;
            return 0;
        }
        cur = land[cur];
        ans++;
    }
    cout << ans << endl;
    return 0;
}
