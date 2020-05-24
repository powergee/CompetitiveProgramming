#include <iostream>
#include <algorithm>
#define MOD 1000000007

typedef long long Long;

Long dp[11][1001];

Long Count(int length, int maxVal)
{
    if (maxVal == 1 || length <= 1)
        return 1;

    Long& result = dp[length][maxVal];
    if (result != 0)
        return result;

    for (int newMax = maxVal; newMax >= 1; --newMax)
    {
        result += Count(length - 1, newMax);
        result %= MOD;
    }

    return result;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);


}