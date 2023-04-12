#include <string.h>
#include <stdio.h>
void replace(void *self, int size, int size_elem, void *x, void *y)
{
    int i = 0;
    while (i < size)
    {
        if (memcmp((char*)self + i * size_elem, x, size_elem) == 0)
        {
            memcpy((char*)self + i * size_elem, y, size_elem);
        }
        i++;
    }
}
void replace_new(int *self, int size, int *x, int *y)
{
    int i = 0;
    while (i < size)
    {
        if (self[i] == *x)
        {
            self[i] = *y;
        }
        i++;
    }
}
int main(int argc, char const *argv[])
{
    float a[] = {1.0, 2.6, 9.8, 3.0, 1.0};
    float x = 1.0;
    float y = 4.0;

    replace(a, sizeof(a)/sizeof(a[0]), sizeof(x), &x, &y);

    for (size_t i = 0; i < 5; i++)
    {
        printf("%f ", a[i]);
    }
    
    return 0;
}
