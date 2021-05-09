#include <iostream>
#include <algorithm>

typedef long long Long;

int n;
int arr[2000];
Long dp[2000][2000];

Long getMaxProfit(int left, int right) {
    if (left == right) {
        return arr[left] * n;
    }

    Long& result = dp[left][right];
    if (result != -1) {
        return result;
    }

    int time = left + (n-1-right) + 1;
    return result = std::max(getMaxProfit(left+1, right)+time*arr[left], getMaxProfit(left, right-1)+time*arr[right]);
}

int main() {
    std::fill(&dp[0][0], &dp[0][0]+sizeof(dp)/sizeof(Long), -1);
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    printf("%lld", getMaxProfit(0, n-1));

    return 0;
}