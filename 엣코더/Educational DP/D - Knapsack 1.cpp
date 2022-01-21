#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int n, w;
    scanf("%d %d", &n, &w);

    std::vector<std::vector<Long>> dp(n, std::vector<Long>(w+1, 0LL));
    std::vector<Long> weight(n), value(n);

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &weight[i], &value[i]);
    }

    for (int i = weight[0]; i <= w; ++i) {
        dp[0][i] = value[0];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= w; ++j) {
            if (j < weight[i]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]);
            }
        }
    }

    printf("%lld", dp[n-1][w]);

    return 0;
}