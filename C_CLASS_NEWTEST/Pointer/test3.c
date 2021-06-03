/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: Mon 14 Oct 2019 08:35:58 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void InputVector(int *Vector){
    int *p;
    for(p = Vector; p < Vector + 2; p++){
        *p = rand()%100; 
    }
}
void PrintVector(int *Vector){
    printf("%d %d\n",*Vector,*(Vector+1));
}
double AddVector(int *Vector1, int *Vector2, int *Vector_sum){
    int *p;
    for(p = Vector_sum; p < Vector_sum + 2; p++){
        *p = *(Vector1 + (p - Vector_sum)) + *(Vector2 + (p - Vector_sum));
    }
   
    double sum = 0.0 + (*Vector_sum) * (*Vector_sum) + (*(Vector_sum + 1)) * (*(Vector_sum + 1));
    return sqrt(sum);
}
int main()
{
    int V1[2],V2[2];
    srand(time(NULL));

    InputVector(V1);
    InputVector(V2);
    PrintVector(V1);
    PrintVector(V2);

    int V_sum[2];
    float sum;
    sum = AddVector(V1,V2,V_sum);
    PrintVector(V_sum);
    printf("sum = %f\n",sum);

    return 0;
}
