/*************************************************************************
	> File Name: test2.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Oct 2019 12:11:34 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Students{
    public:
    ~Students(){
        cout << "Memory has been cleaned. Good bye."
        << endl;
    }
};

int main(){
    Students *student = new Students;
    delete student;
    return 0;
}
