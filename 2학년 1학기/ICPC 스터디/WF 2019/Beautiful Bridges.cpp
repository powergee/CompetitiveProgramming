#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>

typedef long long Long;

int n, h, alpha, beta;
std::pair<Long, Long> ground[10000];
Long dp[10000];

Long calcCost(int start)
{
    if (start == n - 1)
        return alpha * (h - ground[start].second);

    Long& result = dp[start];
    if (result)
        return result;
    result = LLONG_MAX;

    double minD = 0, maxD = 2 * (h - ground[start].second);
    for (int i = start + 1; i < n; ++i)
    {
        Long currD = ground[i].first - ground[start].first;
        Long currH = h - ground[start].second;
        printf("%lld %lld %lld\n", ground[i].first, ground[start].first, ground[start].second);
        
        if (2*currH <= currD)
            minD = std::max(minD, 2*currD + 2*currH - sqrt(8*currD*currH));
        maxD = std::min(maxD, 2*currD + 2*currH + sqrt(8*currD*currH));

        printf("%lf %lf\n", minD, maxD);
        printf("-> %lld %lld\n", currD, currH);
        
        if (minD > maxD || currD > maxD)
            break;
        if (minD <= currD && currD <= maxD)
        {
            Long next = calcCost(i);
            if (next != -1)
                result = std::min(result, alpha * currH + beta * currD * currD + next);
        }
    }

    if (result == LLONG_MAX)
        return result = -1;
    else return result;
}

int main()
{
    scanf("%d %d %d %d", &n, &h, &alpha, &beta);

    for (int i = 0; i < n; ++i)
    {
        scanf("%lld %lld", &ground[i].first, &ground[i].second);
    }
    
    Long minCost = calcCost(0);
    if (minCost == -1)
        printf("impossible");
    else printf("%lld", minCost);

    return 0;
}