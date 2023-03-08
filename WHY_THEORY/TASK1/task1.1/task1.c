#include <stdio.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
bool in_range(int32_t x)
{
    return x >= INT32_MIN && x <= INT32_MAX;
}
int32_t P1(int32_t x1, int32_t x2, int32_t x3)
{
    if (in_range(x1 - x3))
    {
        int32_t y = x1 - x3;
        if (in_range(x2 + y))
        {
            int32_t z = x2 + y;
            return z;
        }
        else
        {
            return 0; // handle overflow case
        }
    }
    else
    {
        return 0; // handle overflow case
    }
}
