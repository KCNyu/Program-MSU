/*************************************************************************
	> File Name: test31.c
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Nov 2019 05:25:18 PM CST
 ************************************************************************/

#include<stdio.h>
#include<setjmp.h>

jmp_buf begin;
char curlex;
void getlex(void);
double expr(void);
double add_minus(void);
double mult_div(void);
double Mypow(void);
double Pow1(double,double);
void error(void);

int main()
{
    double result;
    if(setjmp(begin) == 0)
        printf("==>");
    else
        printf("Try one more times\n==>");
    getlex();
    result = expr();
    if(curlex != '\n')
        error();
    printf("%lf\n",result);
    return 0;   
}

void getlex(void){
    while((curlex = getchar()) == ' ');
}

void error(void){
    printf("Error!\n");
    while(getchar() != '\n');
    longjmp(begin,1);
}

double expr(void){
    double e = add_minus();
    while(curlex == '+' || curlex == '-'){
        if(curlex == '+'){
            getlex();
            e += add_minus();
        }
        else{
            getlex();
            e -= add_minus();
        }
    }
    return e;
}
double add_minus(void){
    double a = mult_div();
    while(curlex == '*' || curlex == '/'){
        if(curlex == '*'){
            getlex();
            a *= mult_div();
        }
        else{
            getlex();
            double m = mult_div();
            if(m == 0)
                error();
            else
                a /= m;
        }
    }
    return a;
}
double mult_div(void){
    double e = Mypow();
    if(curlex == '^'){
        getlex();
        double m = mult_div();
        e = Pow1(e,m);
    }
    return e;
}
double Mypow(void){
    double m;
    switch(curlex){
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': m = curlex - '0'; break;
        case '(': getlex(); m = expr(); if(curlex == ')') break;
        default : error();
    }
    getlex();
    return m;
}
double Pow1(double a, double n){
	double t = a;
	int i;
    if(n == 0 && a == 0)
        error();
    if(n == 0)
	    return 1;
    if(n > 0){
        for(i = 1; i < n; i++)
            a *= t;
    }
    else{
        for(i = 0; i < -n+1; i++)
            a /= t;
    }
	return a;
}
