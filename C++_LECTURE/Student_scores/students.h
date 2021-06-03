/*************************************************************************
	> File Name: students.h
	> Author: 
	> Mail: 
	> Created Time: Thu 10 Oct 2019 11:55:32 PM CST
 ************************************************************************/

#ifndef _STUDENTS_H
#define _STUDENTS_H
#pragma once
#endif
#include <string>
using namespace std;
class Students{
    private:
        float average_ball;
        string name;
        string last_name;
        int scores[5];
    public:
        void set_name(string);
        string get_name();
        void set_last_name(string);
        string get_last_name();
        void set_scores(int []);
        void set_average_ball(float);
        float get_average_ball();
};
