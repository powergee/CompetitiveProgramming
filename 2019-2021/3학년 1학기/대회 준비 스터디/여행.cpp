#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> graph[301];
int n, m, k;
int dp[301][301];

int getMaxSum(int start, int passed) {
    if (start == n) {
        if (passed < m) {
            return 0;
        } else {
            return -__INT32_MAX__;
        }
    }

    int& result = dp[start][passed];
    if (result != -1) {
        return result;
    }

    for (auto e : graph[start]) {
        result = std::max(e.second + getMaxSum(e.first, passed+1), result);
    }

    if (result == -1) {
        result = -__INT32_MAX__;
    }

    return result;
}

int main() {
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < k; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (b < a) {
            continue;
        }
        graph[a].emplace_back(b, c);
    }

    printf("%d", getMaxSum(1, 0));

    return 0;
}