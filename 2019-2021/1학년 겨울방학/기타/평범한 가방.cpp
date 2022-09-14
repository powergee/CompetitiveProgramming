#include <iostream>
#include <algorithm>

int dp[100001][100];
int n, k;
int w[100], v[100];

int TryToPut(int space, int last)
{
    if (space <= 0 || last < 0)
        return 0;

    int& result = dp[space][last];
    if (result != -1)
        return result;
    
    if (space >= w[last])
        return result = std::max(TryToPut(space - w[last], last - 1) + v[last], TryToPut(space, last - 1));
    
    return result = TryToPut(space, last - 1);
}

int main()
{
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d %d", w + i, v + i);

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    printf("%d", TryToPut(k, n - 1));

    return 0;
}