#include<string.h>
#include<stdio.h>

void replace(void *self, int size, int elem_size, void *x, void *y) {
    int i = 0;
    while (i < size) {
        if (memcmp((char *)self + i * elem_size, x, elem_size) == 0) {
            memcpy((char *)self + i * elem_size, y, elem_size);
        }
        i++;
    }
}

void replace_uint(int *self, int size, int *x, int *y) {
    int i = 0;
    while(i < size) {
        if(self[i] == *x) {
            self[i] = *y;
        }
        i++;
    }
}

int main(void) {
    float a[] = {1.0, 2.6783, 9.89816732, 3.0, 1.0};
    float x = 1.0;
    float y = 4.0;
    replace(a, sizeof(a) / sizeof(a[0]), sizeof(x), &x, &y);
    int a1[] = {1, 3, 4, 5, 1};
    int x1 = 1;
    int y1 = 4;
    replace_uint(a1, sizeof(a1) / sizeof(a1[0]), &x1, &y1);
    for(int i = 0; i < 5; i++) {
        printf("%d ", a1[i]);
    }
    printf("\n");
}