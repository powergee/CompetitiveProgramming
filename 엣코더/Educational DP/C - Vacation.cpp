#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> gains(n, std::vector<int>(3));
    std::vector<std::vector<int>> dp(n, std::vector<int>(3, -1));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &gains[i][j]);
        }
    }

    std::function<int(int, int)> getMaxHappiness = [&](int start, int prev) -> int {
        if (start == n) {
            return 0;
        }

        int& result = dp[start][prev];
        if (result != -1) {
            return result;
        }

        for (int i = 0; i < 3; ++i) {
            if (i != prev) {
                result = std::max(result, gains[start][i] + getMaxHappiness(start+1, i));
            }
        }
        return result;
    };

    std::vector<int> cands = {
        gains[0][0] + getMaxHappiness(1, 0),
        gains[0][1] + getMaxHappiness(1, 1),
        gains[0][2] + getMaxHappiness(1, 2),
    };
    printf("%d", *std::max_element(cands.begin(), cands.end()));

    return 0;
}