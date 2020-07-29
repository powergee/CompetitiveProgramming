#include <iostream>
#include <algorithm>
#include <climits>

int n, k;
std::pair<int, int> interval[2];
typedef long long Long;

Long step3(std::pair<int, int> interval, int count, Long request)
{
    Long current = ((Long)interval.second - interval.first) * count;
    if (current >= request)
        return 0;
    
    Long extra = request - current;
    return extra * 2;
}

Long step2(std::pair<int, int> front, std::pair<int, int> back, int count, Long request)
{
    Long current = ((Long)front.second - back.first) * count;
    if (current >= request)
        return 0;
    
    Long max = ((Long)back.second - front.first) * count;
    if (max < request)
        return step3(std::make_pair(front.first, back.second), count, request) + ((Long)back.second - front.second + back.first - front.first) * count;
    else
        return request - current;
}

Long step1(std::pair<int, int> front, std::pair<int, int> back, int count, Long request)
{
    int mid = (back.second - front.second) / 2;
    return ((Long)back.first - front.second) * count + step2({front.first, mid}, {mid+1, back.second}, count, request);
}

Long step2_2(std::pair<int, int> bigger, std::pair<int, int> smaller, int count, Long request)
{
    Long current = ((Long)smaller.second - smaller.first) * count;
    if (current >= request)
        return 0;
    
    Long max = ((Long)bigger.second - bigger.first) * count;
    if (max < request)
        return step3(bigger, count, request) + ((Long)smaller.first - bigger.first + bigger.second - smaller.second) * count;
    else
        return request - current;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d", &n, &k);
        scanf("%d %d", &interval[0].first, &interval[0].second);
        scanf("%d %d", &interval[1].first, &interval[1].second);
        std::sort(interval, interval + 2);

        Long result = LLONG_MAX;
        for (int i = 1; i <= n; ++i)
        {
            if (interval[0] == interval[1])
                result = std::min(result, step3(interval[0], i, k));
            else if (interval[0].second >= interval[1].second)
                result = std::min(result, step2_2(interval[0], interval[1], i, k));
            else if (interval[0].second <= interval[1].first)
                result = std::min(result, step2(interval[0], interval[1], i, k));
            else
                result = std::min(result, step1(interval[0], interval[1], i, k));
        }

        printf("%lld\n", result);
    }
}