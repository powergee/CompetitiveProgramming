#include <iostream>
#include <algorithm>

int arr[10000];
int dp[10000];
int n;

int getMax(int start)
{
    if (n <= start)
        return 0;
    
    int& result = dp[start];
    if (result != -1)
        return result;
    
    result = getMax(start+1);
    result = std::max(getMax(start+2) + arr[start], result);
    if (start+1 < n)
        result = std::max(getMax(start+3) + arr[start] + arr[start+1], result);
    
    return result;
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", arr+i);
    
    std::fill(dp, dp + n, -1);
    printf("%d", getMax(0));

    return 0;
}