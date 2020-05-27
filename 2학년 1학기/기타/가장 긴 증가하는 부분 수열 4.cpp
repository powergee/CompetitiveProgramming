#include <iostream>

int arr[1001];
int dp[1001];
int next[1001];
int n;

int GetMaxLength(int start)
{
    if (start == n)
        return 1;
    
    int& result = dp[start];
    if (result != -1)
        return result;
    
    result = 1;
    for (int i = start + 1; i <= n; ++i)
    {
        if (arr[start] < arr[i])
        {
            int length = 1 + GetMaxLength(i);
            if (length > result)
            {
                result = length;
                next[start] = i;
            }
        }
    }

    return result;
}

int main()
{
    std::fill(&dp[0], &dp[0] + sizeof(dp) / sizeof(int), -1);
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i)
        scanf("%d", arr + i);

    int maxLength = 0;
    int maxStart = 0;
    for (int i = 1; i <= n; ++i)
    {
        int length = GetMaxLength(i);
        if (maxLength < length)
        {
            maxLength = length;
            maxStart = i;
        }
    }
    
    printf("%d\n", maxLength);
    for (int now = maxStart; now != 0; now = next[now])
        printf("%d ", arr[now]);

    return 0;
}