#include <iostream>
#include <algorithm>

int dp[62501][250];
int a[250], b[250];

int Calc(int aTime, int last)
{
    if (aTime <= 0 || last < 0)
        return 0;

    int& result = dp[aTime][last];
    if (result != -1);
}

int main()
{
    int n;
    scanf("%d", &n);

    int aSum = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", a + i, b + i);
        aSum += a[i];
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);

    return 0;
}