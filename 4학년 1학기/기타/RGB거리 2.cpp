#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> cost(n, std::vector<int>(3));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    std::vector<int> dp(n*3*3, -1);
    std::function<int(int, int, int)> getMinCost = [&](int start, int sColor, int eColor) -> int {
        if (start == n-1) {
            return sColor == eColor ? cost[start][sColor] : (INT32_MAX/2);
        }

        int& result = dp[3*3*start + 3*sColor + eColor];
        if (result != -1) {
            return result;
        }

        result = INT32_MAX;
        for (int next = 0; next < 3; ++next) {
            if (next != sColor) {
                result = std::min(result, cost[start][sColor] + getMinCost(start+1, next, eColor));
            }
        }

        return result;
    };
    
    std::vector<int> cands = {
        getMinCost(0, 0, 1),
        getMinCost(0, 0, 2),
        getMinCost(0, 1, 0),
        getMinCost(0, 1, 2),
        getMinCost(0, 2, 0),
        getMinCost(0, 2, 1),
    };

    printf("%d", *std::min_element(cands.begin(), cands.end()));

    return 0;
}