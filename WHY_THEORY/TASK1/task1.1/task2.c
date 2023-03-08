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
        int32_t y1 = x1 - x3;
        if (in_range(y1 + x2))
        {
            int32_t z = y1 + x2;
            return z;
        }
        else
        {
            return 0; // handle overflow case
        }
    }
    else if (in_range(x1 + x2))
    {
        int32_t y2 = x1 + x2;
        if (in_range(y2 - x3))
        {
            int32_t z = y2 - x3;
            return z;
        }
        else
        {
            return 0; // handle overflow case
        }
    }
    else if (in_range(x2 - x3))
    {
        int32_t y3 = x2 - x3;
        if (in_range(y3 + x1))
        {
            int32_t z = y3 + x1;
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