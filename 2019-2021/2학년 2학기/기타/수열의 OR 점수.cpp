#include <iostream>
#include <algorithm>

typedef long long Long;

int n, k;
int arr[5001];
int orScore[5001][5001];
Long dp[5001][5001], properK[5001][5001];

void find(int t, int l, int r, int p, int q)
{
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    dp[t][mid] = -1;
    properK[t][mid] = -1;

    for (int k = p; k <= std::min(q, mid); ++k)
    {
        Long current = dp[t-1][k-1] + orScore[k][mid];
        if (dp[t][mid] < current)
        {
            dp[t][mid] = current;
            properK[t][mid] = k;
        }
    }

    find(t, l, mid - 1, p, properK[t][mid]);
    find(t, mid + 1, r, properK[t][mid], q);
}

int main()
{
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d", arr+i);

    for (int i = 0; i < n; ++i)
    {
        orScore[i][i] = arr[i];
        for (int j = i+1; j < n; ++j)
            orScore[i][j] = orScore[i][j-1] | arr[j];
    }

    for (int i = 0; i < n; ++i)
    {
        dp[0][i] = orScore[0][i];
        properK[0][i] = 1;
    }
    
    for (int t = 1; t < k; ++t)
        find(t, t, n-1, t, n-1);
    
    printf("%lld", dp[k-1][n-1]);

    return 0;
}