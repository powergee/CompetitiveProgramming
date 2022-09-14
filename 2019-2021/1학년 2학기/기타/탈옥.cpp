#include <iostream>
#include <algorithm>

typedef long long Long;

int L, G;
Long Ci[8001];
Long sum[8001];

Long dp[801][8001], properK[801][8001];

Long Cost(Long a, Long b)
{
    return (sum[b] - sum[a - 1]) * (b - a + 1);
}

void Find(int offiNum, int l, int r, int p, int q)
{
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    dp[offiNum][mid] = -1;
    properK[offiNum][mid] = -1;

    for (int k = p; k <= q; ++k)
    {
        Long current = dp[offiNum - 1][k] + Cost(k+1, mid);
        if (dp[offiNum][mid] == -1 || dp[offiNum][mid] > current)
        {
            dp[offiNum][mid] = current;
            properK[offiNum][mid] = k;
        }
    }

    Find(offiNum, l, mid - 1, p, properK[offiNum][mid]);
    Find(offiNum, mid + 1, r, properK[offiNum][mid], q);
}

int main()
{
    scanf("%d %d", &L, &G);

    for (int i = 1; i <= L; ++i)
    {
        scanf("%lld", Ci + i);
        sum[i] = sum[i-1] + Ci[i];
    }

    for (int i = 1; i <= L; ++i)
        dp[1][i] = Cost(1, i);

    for (int offiNum = 2; offiNum <= G; ++offiNum)
        Find(offiNum, 1, L, 1, L);

    printf("%lld", dp[G][L]);

    return 0;
}