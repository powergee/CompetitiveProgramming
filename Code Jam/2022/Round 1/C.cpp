#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>

void solve() {
    int e, w;
    std::cin >> e >> w;

    std::vector<std::vector<int>> need(e, std::vector<int>(w));
    std::vector<std::vector<int>> dp(e, std::vector<int>(e, INT32_MAX));
    std::vector<std::vector<int>> common(e, std::vector<int>(e));
    for (int i = 0; i < e; ++i) {
        int sum = 0;
        for (int j = 0; j < w; ++j) {
            std::cin >> need[i][j];
            sum += need[i][j];
        }
        dp[i][i] = sum*2;
    }

    for (int i = 0; i < e; ++i) {
        std::vector<int> bucket = need[i];
        for (int j = i+1; j < e; ++j) {
            for (int k = 0; k < w; ++k) {
                bucket[k] = std::min(bucket[k], need[j][k]);
            }
            common[i][j] = std::accumulate(bucket.begin(), bucket.end(), 0);
        }
    }
    
    for (int width = 2; width <= e; ++width) {
        for (int i = 0; i+width-1 < e; ++i) {
            int j = i+width-1;
            for (int m = i; m < j; ++m) {
                dp[i][j] = std::min(dp[i][j], dp[i][m] + dp[m+1][j] - 2*common[i][j]);
            }
        }
    }
    std::cout << dp[0][e-1] << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}