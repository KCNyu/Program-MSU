/*************************************************************************
	> File Name: students.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Oct 2019 12:26:19 AM CST
 ************************************************************************/
#include<string>
#include<iostream>
#include"students.h"
using namespace std;

void Students::set_name(string student_name){
    Students::name = student_name;
}
string Students::get_name(){
    return Students::name;
}
void Students::set_last_name(string student_last_name){
    Students::last_name = student_last_name;
}
string Students::get_last_name(){
    return Students::last_name;
}
void Students::set_scores(int scores[]){
    int i;
    for(i = 0; i < 5; ++i){
        Students::scores[i] = scores[i];
    }
}
void Students::set_average_ball(float ball){
    Students::average_ball = ball;
}
float Students::get_average_ball(){
    return Students::average_ball;
}
