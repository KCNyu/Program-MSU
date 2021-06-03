/*================================================================
* Filename:KMP.cpp
* Author: KCN_yu
* Createtime:Sat 27 Mar 2021 12:40:56 AM CST
================================================================*/

#include <iostream>
#include <vector>
using namespace std;
void getNext(vector<int>& next, string str){
    int n = str.size();
    next[0] = 0;
    int j = 0;
    for(int i = 1; i < n; i++){
        while(j > 0 && str[i] != str[j]){
            j = next[j-1];
        }
        if(str[i] == str[j]){
            j++;
        }
        next[i] = j;
    }
    for(auto k : next) cout << k << endl;
}
int strStr(string haystack, string needle){
      int m = haystack.size(), n = needle.size();
      if(n == 0) return 0;
      vector<int> next(n);
      getNext(next,needle);
      int j = 0;
      for(int i = 0; i < m; i++){
          if(haystack[i] == needle[j]){
              if(j == n-1){
                  return i-n+1;
              }
              //if in the end of pattern string, then return then answer.
              j++;
          }
          else{
              if(j == 0){
                  continue;
              }
              //if at the start of pattern string, but doesn't have array next, that just mean str go to the next one.
              j = next[j-1];
              //think to the prefix.
              i--;
        }
    }
    return -1;
}
int main(int argc, char *argv[])
{
    string s{"abxabcabcaby"};
    string pattern("abcaby");
    cout << strStr(s,pattern) << endl;
    return 0;
}
