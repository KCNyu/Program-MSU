/*************************************************************************
	> File Name: test15.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Nov 2019 12:39:59 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
struct s {
    int k; float *f; char *p[2];
};
int main()
{
    struct s *ps;
    char str[5] = "abcd";
    ps = (struct s*)malloc(sizeof(struct s));//ps is a pointer
    (*ps).k = 5;
    printf("%d\n",(*ps).k);
    (*ps).f = (float *)malloc(sizeof(float));//ps -> f
    *(ps -> f) = 3.1415;//*((*ps.f))
    printf("%f\n",*((*ps).f));
    (*ps).p[0] = (char*)malloc(5*sizeof(char));
    (*ps).p[1] = (char*)malloc(10*sizeof(char));
    (*ps).p[0] = str;
    (*ps).p[1] = "abcdefghi";
    printf("%s\n",(*ps).p[0]);
    printf("%s\n",(*ps).p[1]);

    return 0;
}
