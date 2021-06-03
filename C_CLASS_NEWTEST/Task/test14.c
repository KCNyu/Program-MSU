/*************************************************************************
	> File Name: test14.c
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Nov 2019 01:15:12 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
struct rat{
    int num;
    int den;
};
int Gcd(int x, int y){
    x = abs(x);
    y = abs(y);
    int t, common_power_of_two = 0;
    if(x == 0)
        return y;
    if(y == 0)
        return x;
    while(((x & 1) == 0) && (y & 1) == 0){
        x >>= 1;
        y >>= 1;
        ++ common_power_of_two;
    }
    while(1){
        if(x < y)
            t = y, y = x, x = t; //swap(x,y)
        if((x -= y) == 0)
            return y << common_power_of_two;
        while((x & 1) == 0){
            x >>= 1;
        }
    }
}
void Simplify(struct rat *result){
    int common = Gcd((*result).num, (*result).den);
    (*result).num /= common;
    (*result).den /= common;
    if((*result).den < 0){
        (*result).num =-(*result).num;
        (*result).den =-(*result).den;
    }
}
struct rat Plus (struct rat x, struct rat y){
    struct rat sum;
    sum.num = x.num * y.den + x.den * y.num;
    sum.den = x.den * y.den;
    Simplify(&sum);
    return sum;
}
struct rat Minus(struct rat x, struct rat y){
    struct rat dif;
    dif.num = x.num * y.den - x.den * y.num;
    dif.den = x.den * y.den;
    Simplify(&dif);
    return dif;
}
struct rat Times(struct rat x, struct rat y){
    struct rat pro;
    pro.num = x.num * y.num;
    pro.den = x.den * y.den;
    Simplify(&pro);
    return pro;
}
struct rat Div(struct rat x, struct rat y){
    struct rat quo;
    quo.num = x.num * y.den;
    quo.den = x.den * y.num;
    Simplify(&quo);
    return quo;
}
int main()
{
    struct rat x;
    struct rat y;
    
    printf("Input x.num x.den:");
    scanf("%d%d",&x.num,&x.den);
    
    printf("Input y.num y.den:");
    scanf("%d%d",&y.num,&y.den);

    if(x.den == 0 || y.den == 0){
        printf("ERROR!\n");
        return 0;
    }
    struct rat sum = Plus(x,y);
    struct rat dif = Minus(x,y);
    struct rat pro = Times(x,y);
    struct rat quo = Div(x,y);
    
    printf("sum = %d/%d\n",sum.num, sum.den);
    printf("dif = %d/%d\n",dif.num, dif.den);
    printf("pro = %d/%d\n",pro.num, pro.den);
    printf("quo = %d/%d\n",quo.num, quo.den);

    return 0;
}
