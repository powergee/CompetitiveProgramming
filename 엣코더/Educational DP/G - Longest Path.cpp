#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> graph(n+1);
    std::vector<int> dp(n+1, -1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
    }

    std::function<int(int)> findLongestPath = [&](int start) -> int {
        if (dp[start] != -1) {
            return dp[start];
        }

        dp[start] = 0;
        for (int next : graph[start]) {
            dp[start] = std::max(dp[start], findLongestPath(next)+1);
        }
        return dp[start];
    };

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        answer = std::max(answer, findLongestPath(i));
    }
    printf("%d", answer);

    return 0;
}