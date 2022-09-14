#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> map(n, std::vector<int>(m));
    std::vector<std::vector<Long>> dp(n, std::vector<Long>(m, 0LL));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    for (int i = 0; i < m; ++i) {
        if (map[n-1][i] == 1) {
            dp[n-1][i] = 1;
        }
    }

    for (int i = n-2; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 0) {
                continue;
            }
            if (j == 0) {
                dp[i][j] = dp[i+1][j] + dp[i+1][j+1];
            } else if (j == m-1) {
                dp[i][j] = dp[i+1][j] + dp[i+1][j-1];
            } else {
                dp[i][j] = dp[i+1][j] + dp[i+1][j-1] + dp[i+1][j+1];
            }
            dp[i][j] %= 1000000007LL;
        }
    }

    printf("%lld", std::accumulate(dp[0].begin(), dp[0].end(), 0LL)%1000000007LL);

    return 0;
}