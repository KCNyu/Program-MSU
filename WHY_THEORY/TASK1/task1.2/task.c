int P(int x)
{
    int y1 = 0, y2 = 0, y3 = 1;
    y2 = y2 + y3;
    while (y2 <= x)
    {
        y1 = y1 + 1;
        y3 = y3 + 6 * y1;

        y2 = y2 + y3;
    }
    int z = y1;
    return z;
}