#include <iostream>
#include <algorithm>
#define MOD ((Long)1000000000)

typedef long long Long;

Long dp[201][201];

Long Count(int n, int k)
{
    Long& result = dp[n][k];
    if (result != -1)
        return result;

    if (n == 0)
        return result = 1;
    if (k == 1)
        return result = 1;
    
    result = 0;
    for (int first = 0; first <= n; ++first)
        result = (result + Count(n - first, k - 1)) % MOD;

    return result;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1);

    printf("%lld", Count(n, k));
    return 0;
}