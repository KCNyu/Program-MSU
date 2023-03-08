int P(int x)
{
    int y1 = x, y2 = 1, y3 = x;

    do
    {
        while (y2 < y3)
        {
            y1 = y1 + x;
            y2 = y2 + 1;
        }
        if (y3 != x)
        {
            break;
        }
        else
        {
            y3 = y1;
            continue;
        }
    } while (1);

    int z = y1;
    return z;
}