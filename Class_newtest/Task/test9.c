/*************************************************************************
	> File Name: test9.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Nov 2019 03:49:18 PM CST
 ************************************************************************/

#include<stdio.h>
struct point {
    int x;
    int y;
};

void assign_to_point1 (struct point p, int a, int b){
    p.x = a;
    p.y = b;
}

void assign_to_point2 (struct point *p, int a, int b){
    (*p).x = a;
    (*p).y = b;
}

/*  
void assign_to_point3 (struct point *p, int a, int b){
    *p.x = a;
    *p.y = b;
}
*/

void assign_to_point4 (struct point *p, int a, int b){
    p->x = a;
    p->y = b;
}

int main()
{
    struct point p1,p2,p3,p4;
    assign_to_point1(p1,1,2);
    assign_to_point2(&p2,1,2);
//    assign_to_point3(&p3,1,2);
    assign_to_point4(&p4,1,2);

    printf("p1: %d %d\n",p1.x,p1.y);
    printf("p2: %d %d\n",p2.x,p2.y);
//    printf("p3: %d %d\n",p3.x,p3.y);
    printf("p4: %d %d\n",p4.x,p4.y);

    return 0;
}
