#include <iostream>
#include <algorithm>

int cost[1000][3];
int dp[1000][3];

int GetMin(int last, int select)
{
    if (last == 0)
        return cost[last][select];

    int& result = dp[last][select];
    if (result != 0)
        return result;

    result = 1e9;
    if (select != 0)
        result = std::min(result, GetMin(last - 1, 0) + cost[last][select]);
    if (select != 1)
        result = std::min(result, GetMin(last - 1, 1) + cost[last][select]);
    if (select != 2)
        result = std::min(result, GetMin(last - 1, 2) + cost[last][select]);

    return result;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d %d %d", &cost[i][0], &cost[i][1], &cost[i][2]);

    printf("%d", std::min(GetMin(n - 1, 0), std::min(GetMin(n - 1, 1), GetMin(n - 1, 2))));

    return 0;
}