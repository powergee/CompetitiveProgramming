#include <iostream>
#include <algorithm>

typedef unsigned int uint;
uint countHor(uint size, uint y, uint x1, uint x2);
uint countVer(uint size, uint x, uint y1, uint y2);

int main()
{
    while (true)
    {
        uint n, x1, x2, y;
        scanf("%u", &n);

        if (n == 0)
            break;
        
        scanf("%u %u %u", &x1, &x2, &y);
        uint width = 1U<<n;
        printf("%u\n", countHor(width, y, x1, x2));
    }

    return 0;
}

uint countHor(uint size, uint y, uint x1, uint x2)
{
    if (size == 2U)
        return (y == 0U || y == 2U) ? 0U : x2-x1;
    
    uint half = size/2U;
    uint result = 0U;

    if (y > half)
    {
        if (x1 < half)
            result += countVer(half, y-half, std::max(0U, half-x2), half-x1);
        if (x2 > half)
            result += countVer(half, size-y, std::max(0U, x1-half), x2-half);
    }
    else if (y == half)
    {
        if (x1 == 0U)
            ++result;
        if (x2 == size)
            ++result;
    }
    else
    {
        if (x1 < half)
            result += countHor(half, y, x1, std::min(half, x2));
        if (x2 > half)
            result += countHor(half, y, std::max(0U, x1-half), x2-half);
    }

    return result;
}

uint countVer(uint size, uint x, uint y1, uint y2)
{
    if (size == 2U)
        return (x == 0U || x == 2U) ? 0U : (y1 < y2 ? 1U : 0U);
    
    uint half = size/2U;
    uint result = 0U;

    if (x > half)
    {
        if (y1 < half)
            result += countVer(half, x-half, y1, std::min(half, y2));
        if (y2 > half)
            result += countHor(half, x-half, half-y2, std::min(half, size-y1));
    }
    else if (x == half)
    {
        if (y1 < half && half <= y2)
            ++result;
    }
    else 
    {
        if (y1 < half)
            result += countVer(half, x, y1, std::min(half, y2));
        if (y2 > half)
            result += countHor(half, half-x, std::min(0U, y1-half), y2-half);
    }

    return result;
}