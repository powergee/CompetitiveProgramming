#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    std::vector<int> costDP(1001, -1);
    std::function<int(int)> getTransCost = [&](int val) -> int {
        if (costDP[val] != -1) {
            return costDP[val];
        }

        if (val == 1) {
            return costDP[val] = 0;
        }

        costDP[val] = INT32_MAX/2;
        for (int prev = val-1; prev >= 1; --prev) {
            int floorVal = val - prev;
            // Find x which satisfy floor(prev/x) = floorVal
            int left = 1, right = prev;
            bool found = false;
            while (left <= right) {
                int mid = (left+right)/2;
                if ((prev / mid) == floorVal) {
                    left = right = mid;
                    found = true;
                    break;
                } else if ((prev / mid) < floorVal) {
                    right = mid-1;
                } else {
                    left = mid+1;
                }
            }
            if (found) {
                costDP[val] = std::min(costDP[val], getTransCost(prev)+1);
            }
        }

        return costDP[val];
    };

    int T;
    scanf("%d", &T);

    while (T--) {
        int n, w;
        scanf("%d %d", &n, &w);
        std::vector<int> weight(n), value(n);
        std::for_each(weight.begin(), weight.end(), [&](int& weightVal) {
            int goal;
            scanf("%d", &goal);
            weightVal = getTransCost(goal);
        });
        std::for_each(value.begin(), value.end(), [](int& v) { scanf("%d", &v); });

        if (w >= 12000) {
            printf("%d\n", std::accumulate(value.begin(), value.end(), 0));
        } else {
            std::vector<std::vector<int>> dp(n, std::vector<int>(w+1, 0));

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

            printf("%d\n", dp[n-1][w]);
        }
    }

    return 0;
}