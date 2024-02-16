#include <stdio.h>

typedef void *ELT;

int cmp(const ELT *a, const ELT *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;

    return (*pa > *pb) - (*pa < *pb);
}

void sort_three(ELT array[static 3])
{
    int *p1 = (int *)array[0];
    int *p2 = (int *)array[1];
    int *p3 = (int *)array[2];

    // if cmp return negative(sign bit = 1) which means need to swap
    int t=(cmp(p1,p2)>>31)&(*p1^*p2);
    *p1^=t;
    *p2^=t;

    t=(cmp(p1,p3)>>31)&(*p1^*p3);
    *p1^=t;
    *p3^=t;

    t=(cmp(p2,p3)>>31)&(*p2^*p3);
    *p2^=t;
    *p3^=t;
}



int main()
{
    ELT array[] = {(ELT)&(int){1}, (ELT)&(int){3}, (ELT)&(int){2}};

    // Before sorting
    printf("Before sorting: %d, %d, %d\n", *((int *)array[0]), *((int *)array[1]), *((int *)array[2]));

    // Sort the array
    sort_three(array);

    // After sorting
    printf("After sorting: %d, %d, %d\n", *((int *)array[0]), *((int *)array[1]), *((int *)array[2]));

    printf("Size of int: %lu bytes\n", sizeof(int));
    return 0;
}

