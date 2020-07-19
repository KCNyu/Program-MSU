/*************************************************************************
	> File Name: test10.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Nov 2019 06:25:06 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
struct point {
    int x;
    int y;
};
struct point create_point1(int a, int b){
    struct point p;
    p.x = a;
    p.y = b;
    return p;
}
/*
struct point *create_point2(int a, int b){
    struct point p;
    p.x = a;
    p.y = b;
    return &p;
}

struct point *create_point3(int a, int b){
    struct point *pp;
    pp->x = a;
    pp->y = b;
    return pp;
}
*/
struct point *create_point4(int a, int b){
    struct point *pp;
    pp = (struct point *)malloc(sizeof(struct point));
    pp->x = a;
    pp->y = b;
    return pp;
}

int main()
{
    struct point p1 = create_point1(1,2);
    printf("%d %d\n",p1.x,p1.y);
    struct point *p4 = create_point4(1,2);
    printf("%d %d\n",p4->x,p4->y);
    return 0;
}

