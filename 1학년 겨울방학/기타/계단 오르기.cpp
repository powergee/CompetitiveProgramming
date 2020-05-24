#include <iostream>
#include <algorithm>

int dp[301][2];
int point[301];

int GetMax(int last, int succ)
{
    if (last < 1)
        return 0;

    if (last == 1)
        return point[1];

    int& result = dp[last][succ];
    if (result != 0)
        return result;

    if (!succ)
        result = std::max(result, GetMax(last - 1, 1) + point[last]);
    result = std::max(result, GetMax(last - 2, 0) + point[last]);

    return result;
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%d", point + i);

    printf("%d", GetMax(n, 0));

    return 0;
}