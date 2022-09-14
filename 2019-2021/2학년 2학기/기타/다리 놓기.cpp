#include <iostream>
#include <algorithm>

typedef long long Long;
Long dp[31][31];

Long getComb(int n, int m)
{
    if (n < m)
        return 0;
    if (n == 0 || m == 0)
        return 1;
    if (dp[n][m] != -1)
        return dp[n][m];
    
    return dp[n][m] = getComb(n-1, m-1) + getComb(n-1, m);
}

int main()
{
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1);
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        printf("%lld\n", std::max(getComb(n, m), getComb(m, n)));
    }

    return 0;
}