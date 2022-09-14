#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> cost(n+1);
    std::vector<std::vector<int>> child(n+1);
    std::vector<int> dp(n+1, -1);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &cost[i]);
        int count;
        scanf("%d", &count);
        child[i].resize(count);
        for (int j = 0; j < count; ++j) {
            scanf("%d", &child[i][j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        int childMaxCost = 0;
        for (int ch : child[i]) {
            childMaxCost = std::max(childMaxCost, dp[ch]);
        }
        dp[i] = childMaxCost + cost[i];
    }

    printf("%d", *std::max_element(dp.begin(), dp.end()));

    return 0;
}