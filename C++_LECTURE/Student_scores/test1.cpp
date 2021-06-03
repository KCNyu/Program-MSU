/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Oct 2019 12:08:44 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
class Students{
    private:
    int scores[5];
    public:
    Students(int default_score){
        int i;
        for(i = 0; i < 5; ++i){
            scores[i] = default_score;
        }
    }
};

int main()
{
    Students *student = new Students(2);
    return 0;
}
