/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Fri 08 Nov 2019 08:25:00 AM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    struct Student{
        char *firstname;
        char *lastname;
        double avg;
    }class[] = {
        {"lai","gangxuan",5.0},
        {"da","shutian",2000}
    };

    printf("%s%s %lf\n",class[0].firstname,class[0].lastname,class[0].avg);
    printf("%s%s %lf\n",class[1].firstname,class[1].lastname,class[1].avg);
    return 0;
}
