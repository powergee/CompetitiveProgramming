#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> heights(n), dp(n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &heights[i]);
    }

    dp[0] = 0;
    dp[1] = std::abs(heights[1]-heights[0]);

    for (int i = 2; i < n; ++i) {
        dp[i] = std::min(
            dp[i-1]+std::abs(heights[i]-heights[i-1]),
            dp[i-2]+std::abs(heights[i]-heights[i-2])
        );
    }

    printf("%d", dp[n-1]);

    return 0;
}