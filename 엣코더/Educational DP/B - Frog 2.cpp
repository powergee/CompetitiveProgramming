#include <iostream>
#include <vector>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<int> heights(n), dp(n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &heights[i]);
    }

    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
        dp[i] = INT32_MAX;
        for (int j = std::max(i-k, 0); j < i; ++j) {
            dp[i] = std::min(dp[i], dp[j] + std::abs(heights[j]-heights[i]));
        }
    }

    printf("%d", dp[n-1]);

    return 0;
}