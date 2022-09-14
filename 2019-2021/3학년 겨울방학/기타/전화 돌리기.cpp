#include <iostream>
#include <vector>
#include <functional>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
    }

    std::vector<bool> dp(n+1, false);
    std::vector<bool> finished(n+1, false);
    std::vector<bool> inStack(n+1, false);

    std::function<bool(int)> canArriveToCycle = [&](int start) -> bool {
        if (finished[start]) {
            return dp[start];
        }
        if (inStack[start]) {
            return true;
        }

        inStack[start] = true;
        for (int next : graph[start]) {
            if (canArriveToCycle(next)) {
                dp[start] = true;
            }
        }

        inStack[start] = false;
        finished[start] = true;
        return dp[start];
    };

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        count += (canArriveToCycle(i) ? 0 : 1);
    }
    printf("%d", count);

    return 0;
}