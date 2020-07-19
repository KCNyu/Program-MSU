/*************************************************************************
	> File Name: test13.c
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Nov 2019 12:43:52 PM CST
 ************************************************************************/

#include<stdio.h>
#include<math.h>
#define N 5

struct Func {
    char *name;
    double (*fp) (double);
}func [] = {
    {"sin",&sin},
    {"cos",&cos},
    {"log",&log},
    {"tan",&tan},
    {"atan",&atan}
};
int main()
{
    int beg = 1, step = 1, end = beg + (N-1)*step,
    numfuncs = sizeof(func)/sizeof(struct Func);

    int i, j;
    printf("\n");
    for(i = 0; i <= N; i++)
        printf("%7s","_______");

    printf("\n%7s"," f(x) |");
    for(i = beg; i <= end; i += step)
        printf("%5.2f |", (double) i);
    printf("\n");
    
    for(i = 1; i <= N+1; i++)
        printf("%7s","-------");
   
    for (i = 0; i < numfuncs; i++ ){
        printf("\n %-5s|",func[i].name);
        for(j = beg; j <= end; j += step){
            printf("%5.2f |",(*func[i].fp)((double)j));
        }
    }

    printf("\n");
    for(i = 1; i <= N+1; i++)
        printf("%7s","-------");
    printf("\n");
    return 0;
}
