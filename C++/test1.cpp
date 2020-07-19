/*************************************************************************
	> File Name: test1.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 10 Oct 2019 10:32:00 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int addArray(int *array, int n);

int main()
{
    int data[] = {0,1,2};
    int size = sizeof(data)/sizeof(data[0]);

    cout << "result is: " << addArray(data, size) << endl;
    return 0;
}
int addArray(int *array, int n)
{
    int sum = 0;
    int i;
    for(i = 0; i < n; i++)
    {
        sum += *array++;
    }
    return sum;
}
