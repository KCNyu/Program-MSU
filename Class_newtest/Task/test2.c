/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: Tue 05 Nov 2019 04:21:01 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int Fibonacci1(int n){
    if(n == 1 || n == 2){
        return 1;
    }
    int F1,F2,temp;
    F1 = 1;
    F2 = 1;
    for(int i = 2; i <= n; i++){
        temp = F1;
        F1 = F2 + temp;
        F2 = temp;
    }
    return F2;
}
int Fibonacci2(int n){
    if(n == 1 || n == 2){
        return 1;
    }
    else{
        return Fibonacci2(n-1) + Fibonacci2(n-2);
    } 
}
int Gcd1(int m, int n){
    while(m != n){
        if(m%n == 0){
            return n;
        }
        if(n%m == 0){
            return m;
        }
        if(m > n){
            m = m%n;
        }
        else{
            n = n%m;
        }
    }
    return m;
}
int Gcd2(int m, int n){
    if(m%n == 0){
        return n;
    }
    if(n%m == 0){
        return m;
    }
    if(m > n){
        Gcd2(m%n,n);
    }
    else{
        Gcd2(n%m,m);
    }
}
int Gcd3(int m, int n){
    while(m != n){
        if(m > n){
            m -= n;
        }
        else{
            n -= m;
        }
    }
    return m;
}
int Gcd4(int m, int n){
    if(m == n){
        return m;
    }
    if(m > n){
        Gcd4(m-n,n);
    }
    else{
        Gcd4(n-m,m);
    }
}
int Gcd5(int x, int y){
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
int Gcd6(int a, int b){
    while(b^=a^=b^=a%=b);
    return a;
}
unsigned binary_gcd(unsigned x, unsigned y){
    unsigned temp;
    unsigned common_power_of_two = 0;
    if(x == 0)
        return y;
    if(y == 0)
        return x;
    while(((x|y)&1) == 0){
        x >>= 1;
        y >>= 1;
        ++ common_power_of_two;
    }
    while((x&1) == 0)
        x >>= 1;
    while(y){
        while((y&1) == 0)
            y >>= 1;
        temp = y;
        if(x > y)
            y = x - y;
        else
            y = y - x;
        x = temp;
    }
    return (x << common_power_of_two);
}
int main()
{
/*  
    int n;
    scanf("%d",&n);
    printf("%d\n",Fibonacci1(n));
    printf("%d\n",Fibonacci2(n));
*/
    int m,n;
    scanf("%d%d",&m,&n);
//    printf("%d\n",Gcd6(m,n));
    printf("%d\n",Gcd5(m,n));
//    printf("%d\n",binary_gcd(m,n));
    return 0;
}
