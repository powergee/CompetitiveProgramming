#include <iostream>
#include <algorithm>

typedef long long Long;

Long dp[201][12];

Long calcComb(int n, int m)
{
    if (n < m)
        return 0;
    if (n == 0 || m == 0)
        return 1;
    
    if (dp[n][m] != -1)
        return dp[n][m];
    
    return dp[n][m] = calcComb(n-1, m-1) + calcComb(n-1, m);
}

int main()
{
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1);

    int l;
    scanf("%d", &l);

    printf("%lld", calcComb(l-1, 11));

    return 0;
}