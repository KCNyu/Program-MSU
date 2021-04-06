/*================================================================
 * Filename:quicksort.cpp
 * Author: KCN_yu
 * Createtime:Sat 06 Mar 2021 01:22:13 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
void swap(vector<int>& arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
int partition(vector<int>& arr, int left, int right){
    int first = arr[left];
    while(left < right){
        for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
        cout << endl;
        while(left < right && arr[right] >= first) right--;
        swap(arr,left,right);
        for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
        cout << endl;
        while(left < right && arr[left] <= first) left++;
        swap(arr, left ,right);
        for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
        cout << endl;
    }
    return left;
}
void quicksort(vector<int>& arr, int left, int right){
    if(left < right){
        int point = partition(arr, left, right);
        quicksort(arr, left, point-1);
        quicksort(arr, point+1, right);
    }
}
vector<int> MySort(vector<int>& arr) {
    quicksort(arr, 0, arr.size()-1);
    return arr;// write code here
}
int main(int argc, char *argv[])
{
    vector<int> arr = {5,3,1,6,9,2};
    MySort(arr);
    for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
