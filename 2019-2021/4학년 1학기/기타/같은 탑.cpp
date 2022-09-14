#include <iostream>
#include <algorithm>
#include <vector>
#define INVALID -1

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> blocks(n);
    int total = 0;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &blocks[i]);
        total += blocks[i];
    }

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(total+1));

    dp[n][0] = 0;
    for (int diff = 1; diff <= total; ++diff) {
        dp[n][diff] = INVALID;
    }
    for (int bIdx = n-1; bIdx >= 0; --bIdx) {
        for (int diff = 0; diff <= total; ++diff) {
            dp[bIdx][diff] = dp[bIdx+1][diff];
            if (diff+blocks[bIdx] <= total && dp[bIdx+1][diff+blocks[bIdx]] != INVALID) {
                dp[bIdx][diff] = std::max(dp[bIdx][diff], blocks[bIdx]+dp[bIdx+1][diff+blocks[bIdx]]);
            }
            if (dp[bIdx+1][std::abs(diff-blocks[bIdx])] != INVALID) {
                dp[bIdx][diff] = std::max(dp[bIdx][diff], blocks[bIdx]+dp[bIdx+1][std::abs(diff-blocks[bIdx])]);
            }
        }
    }

    int used = dp[0][0];
    printf("%d", used == 0 ? -1 : used/2);

    return 0;
}