#include <iostream>
#include <algorithm>

typedef long long Long;

int n;
std::pair<Long, Long> points[300000];

std::pair<Long, Long> getIntersection(std::pair<Long, Long> i1, std::pair<Long, Long> i2)
{
    if (i1.second < i2.first || i2.second < i1.first)
        return {i1.first, i1.first - 1};

    Long arr[] = {i1.first, i1.second, i2.first, i2.second};
    std::sort(arr, arr + 4);
    return {arr[1], arr[2]};
}

std::pair<int, Long> tryToCover(int start, Long error, Long min)
{
    if (start >= n)
        return {n, min};

    std::pair<Long, Long> current = {std::max(points[start].second - error, min), points[start].second + error};
    if (current.first > current.second)
        return {start, min};
        
    int i = start + 1;
    while (i < n && current.first <= current.second)
    {
        current = getIntersection(current, {points[i].second - error, points[i].second + error});
        if (current.first <= current.second)
            ++i;
    }

    return {i, current.first};
}

bool isValid(Long error)
{
    int pos = 0;
    while (pos < n && points[pos].second <= error)
        ++pos;

    auto cover2nd = tryToCover(pos, error, 0);
    auto cover3rd = tryToCover(cover2nd.first, error, cover2nd.second);
    return cover3rd.first == n;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%lld %lld", &points[i].first, &points[i].second);
        points[i].second *= 2;
    }
    std::sort(points, points + n);

    Long left = points[0].first == 0 ? points[0].second : 0;
    Long right = 2e9;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (isValid(mid))
            right = mid;
        else
            left = mid + 1;
    }

    if (left % 2)
        printf("%lld.5", left/2);
    else
        printf("%lld.0", left/2);

    return 0;
}