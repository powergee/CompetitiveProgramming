#include <iostream>
#include <algorithm>
#include <limits>
#define INF (INT64_MAX / 2)

typedef long long Long;

Long diff[1001];
Long diffSum[1001];
Long dp[501][1001];

Long getCost(int i, int j)
{
    return (diffSum[j] - diffSum[i - 1]) * (j - i + 1);
}

Long find(int memCount, int chCount)
{
    Long& result = dp[memCount][chCount];
    if (result != -1)
        return result;

    if (memCount == 1)
        return result = getCost(1, chCount);

    Long minTime = INF;
    for (int i = memCount - 1; i < chCount; ++i)
        minTime = std::min(minTime, find(memCount - 1, i) + getCost(i + 1, chCount));

    return result = minTime;
}

int main()
{
    int k, n;
    scanf("%d %d", &k, &n);

    for (int i = 1; i <= k; ++i)
    {
        scanf("%lld", diff + i);
        diffSum[i] = diffSum[i - 1] + diff[i];
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1);

    printf("%lld", find(n, k));

    return 0;
}