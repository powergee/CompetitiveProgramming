#include <iostream>

int main() {
    int cost[14][14] = {};
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            std::cin >> cost[i][j];
        }
    }

    int dp[7][2];
    dp[6][0] = dp[6][1] = 0;
    for (int g = 5; g >= 0; --g) {
        int l = g*2;
        int r = g*2+1;
        dp[g][0] = cost[l][r] + std::min(
            dp[g+1][0]+cost[r][(g+1)*2],
            dp[g+1][1]+cost[r][(g+1)*2+1]
        );
        dp[g][1] = cost[r][l] + std::min(
            dp[g+1][0]+cost[l][(g+1)*2],
            dp[g+1][1]+cost[l][(g+1)*2+1]
        );
    }

    std::cout << std::min(dp[0][0], dp[0][1]);

    return 0;
}