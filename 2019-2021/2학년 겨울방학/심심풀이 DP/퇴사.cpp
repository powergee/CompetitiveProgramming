#include <iostream>
#include <algorithm>

int n;
int period[15];
int pay[15];
int dp[15];

int getMax(int start)
{
    if (n <= start)
        return 0;
    
    int& result = dp[start];
    if (result != -1)
        return result;
    
    result = getMax(start+1);
    if (period[start] + start <= n)
        result = std::max(result, getMax(start+period[start]) + pay[start]);
    
    return result;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d %d", period+i, pay+i);
    
    std::fill(dp, dp+n, -1);
    printf("%d", getMax(0));

    return 0;
}