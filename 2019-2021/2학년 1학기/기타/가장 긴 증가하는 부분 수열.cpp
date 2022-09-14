#include <iostream>
#include <algorithm>

int arr[1000];
int dp[1000][1001];
int n;

int GetMaxLength(int start, int prev)
{
    if (start >= n)
        return 0;
    
    int& result = dp[start][prev];
    if (result != -1)
        return result;
    
    if (arr[start] > prev)
        result = GetMaxLength(start + 1, arr[start]) + 1;
    result = std::max(result, GetMaxLength(start + 1, prev));

    return result;
}

int main()
{
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    printf("%d", GetMaxLength(0, 0));

    return 0;
}