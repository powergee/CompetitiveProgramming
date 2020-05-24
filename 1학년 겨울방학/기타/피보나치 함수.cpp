#include <iostream>
#include <algorithm>
typedef std::pair<long long, long long> CountType;

CountType dp[41];

CountType Add(const CountType& a, const CountType& b)
{
    return {a.first + b.first, a.second + b.second};
}

CountType Count(int n)
{
    if (n == 0)
        return {1, 0};
    if (n == 1)
        return {0, 1};

    CountType& result = dp[n];
    if (dp[n].first != -1)
        return result;

    return result = Add(Count(n - 1), Count(n - 2));
}

int main()
{
    int T;
    scanf("%d", &T);
    std::fill(dp, dp + 41, std::make_pair(-1, -1));

    while (T--)
    {
        int n;
        scanf("%d", &n);
        auto result = Count(n);
        printf("%lld %lld\n", result.first, result.second);
    }

    return 0;
}