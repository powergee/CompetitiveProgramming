#include <iostream>
#include <algorithm>
#include <string>
#define MOD 1000000007;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> map(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> map[i];
    }

    std::vector<std::vector<int>> dp(h, std::vector<int>(w, 0));
    for (int i = 0; i < w; ++i) {
        if (map[0][i] == '#') {
            break;
        }
        dp[0][i] = 1;
    }
    for (int i = 0; i < h; ++i) {
        if (map[i][0] == '#') {
            break;
        }
        dp[i][0] = 1;
    }

    for (int i = 1; i < h; ++i) {
        for (int j = 1; j < w; ++j) {
            if (map[i][j] == '#') {
                continue;
            }
            dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % MOD;
        }
    }

    std::cout << dp[h-1][w-1];

    return 0;
}