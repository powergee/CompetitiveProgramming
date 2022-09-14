#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

typedef long long Long;
typedef std::tuple<Long, Long, Long, Long> ArgType;
std::map<ArgType, Long> horDP, verDP;
Long countHor(Long size, Long y, Long x1, Long x2);
Long countVer(Long size, Long x, Long y1, Long y2);

int main()
{
    while (true)
    {
        Long n, x1, x2, y;
        scanf("%lld", &n);

        if (n == 0LL)
            break;
        
        scanf("%lld %lld %lld", &x1, &x2, &y);
        Long width = 1LL<<n;
        printf("%lld\n", countHor(width, y, x1, x2));
    }

    return 0;
}

Long countHor(Long size, Long y, Long x1, Long x2)
{
    std::map<ArgType, Long>::iterator found;
    ArgType args = std::tie(size, y, x1, x2);
    if ((found = horDP.find(args)) != horDP.end())
        return found->second;

    if (size == 2LL)
        return (y == 0LL || y == 2LL) ? 0LL : x2-x1;
    
    Long half = size/2LL;
    Long result = 0LL;

    if (y > half)
    {
        if (x1 < half)
            result += countVer(half, y-half, std::max(0LL, half-x2), half-x1);
        if (x2 > half)
            result += countVer(half, y-half, size-x2, std::min(half, size-x1));
    }
    else if (y == half)
    {
        if (x1 == 0LL)
            ++result;
        if (x2 == size)
            ++result;
    }
    else
    {
        if (x1 < half)
            result += countHor(half, y, x1, std::min(half, x2));
        if (x2 > half)
            result += countHor(half, y, size-x2);
    }

    return horDP[args] = result;
}

Long countVer(Long size, Long x, Long y1, Long y2)
{
    std::map<ArgType, Long>::iterator found;
    ArgType args = std::tie(size, x, y1, y2);
    if ((found = verDP.find(args)) != verDP.end())
        return found->second;

    if (size == 2LL)
        return (x == 0LL || x == 2LL) ? 0LL : (y1 == 0LL ? 1LL : 0LL);
    
    Long half = size/2LL;
    Long result = 0LL;

    if (x > half)
    {
        if (y1 < half)
            result += countVer(half, size-x, y1, std::min(half, y2));
        if (y2 > half)
            result += countHor(half, x-half, std::max(0LL, y1-half), y2-half);
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
            result += countHor(half, half-x, std::max(0LL, y1-half), y2-half);
    }

    return verDP[args] = result;
}