/*================================================================
* Filename:quicksort.cpp
* Author: KCN_yu
* Createtime:Sun 21 Mar 2021 06:20:22 PM CST
================================================================*/

#include <iostream>
#include <vector>
using namespace std;
void Quicksort(vector<int>& arr, int left, int right){
    if(left >= right) return;
    int i = left;
    int j = right;
    int key = arr[left];
    while(true){
        while(arr[++i] < key){
            if(i == right) break;
        }
        cout << "i = " << i << endl;
        while(arr[--j] > key){
            if(j == left) break;
        }
        cout << "j = " << j << endl;
        if(i >= j) break;
        swap(arr[i],arr[j]);
    }
    swap(arr[left],arr[j]);
    for(auto &it:arr) cout << it << " ";
    cout << endl;
    Quicksort(arr,left,j-1);
    Quicksort(arr,j+1,right);
}
int main(int argc, char *argv[])
{
    vector<int> v{3,7,1,9,2};
    for(auto &it:v) cout << it << " ";
    cout << endl;
    Quicksort(v,0,v.size());
    for(auto &it:v) cout << it << " ";
    cout << endl;
    return 0;
}

