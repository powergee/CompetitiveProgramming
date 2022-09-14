#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

typedef long long Long;

Long n, h, alpha, beta;
std::pair<Long, Long> ground[10000];
double leftMaxDist[10000];
double rightMaxDist[10000];
Long dp[10000];

Long calcCost(int start)
{
    if (start == n - 1)
        return alpha * (h - ground[start].second);

    Long& result = dp[start];
    if (result)
        return result;
    result = LLONG_MAX;

    for (int i = start + 1; i < n; ++i)
    {
        Long dist = ground[i].first - ground[start].first;

        if (rightMaxDist[start] * 2 >= dist && leftMaxDist[i] * 2 >= dist)
        {
            Long costOfSegment = alpha*(h-ground[start].second) + beta*dist*dist;
            Long next = calcCost(i);
            if (next != -1 && costOfSegment + next < result)
                result = costOfSegment + next;
        }
    }

    if (result == LLONG_MAX)
        return result = -1;
    else return result;
}

int main()
{
    scanf("%lld %lld %lld %lld", &n, &h, &alpha, &beta);

    for (int i = 0; i < n; ++i)
        scanf("%lld %lld", &ground[i].first, &ground[i].second);
    
    for (int i = 0; i < n - 1; ++i)
    {
        rightMaxDist[i] = h - ground[i].second;

        for (int j = i + 1; j < n; ++j)
        {
            Long dx = ground[j].first - ground[i].first;
            Long dy = h - ground[j].second;
            double currDist = dx + dy + sqrt(2*dx*dy);
            rightMaxDist[i] = std::min(rightMaxDist[i], currDist);
        }
    }

    for (int i = 1; i < n; ++i)
    {
        leftMaxDist[i] = h - ground[i].second;

        for (int j = 0; j < i; ++j)
        {
            Long dx = ground[i].first - ground[j].first;
            Long dy = h - ground[j].second;
            double currDist = dx + dy + sqrt(2*dx*dy);
            leftMaxDist[i] = std::min(leftMaxDist[i], currDist);
        }
    }

    Long minCost = calcCost(0);

    if (minCost == -1)
        printf("impossible");
    else printf("%lld", minCost);

    return 0;
}