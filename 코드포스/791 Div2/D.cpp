#include <iostream>
#include <vector>
#include <functional>
#include <queue>

typedef long long Long;

int main() {
    Long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    std::vector<Long> weight(n+1);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &weight[i]);
    }

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
    }

    auto hasCycle = [&](int maxWeight) -> bool {
        std::vector<bool> visited(n+1, false);
        std::vector<bool> inStack(n+1, false);

        std::function<bool(int)> findCycle = [&](int start) -> bool {
            visited[start] = true;
            inStack[start] = true;

            for (int next : graph[start]) {
                if (weight[next] > maxWeight) {
                    continue;
                }
                if (inStack[next] || (!visited[next] && findCycle(next))) {
                    return true;
                }
            }

            inStack[start] = false;
            return false;
        };

        for (int u = 1; u <= n; ++u) {
            if (weight[u] <= maxWeight && !visited[u] && findCycle(u)) {
                return true;
            }
        }
        return false;
    };

    auto getMaxDist = [&](int maxWeight) -> int {
        std::vector<int> dp(n+1, -1);
        std::function<int(int)> DFS = [&](int start) -> int {
            if (dp[start] != -1) {
                return dp[start];
            }
            dp[start] = 0;
            for (int next : graph[start]) {
                if (weight[next] <= maxWeight) {
                    dp[start] = std::max(dp[start], 1+DFS(next));
                }
            }
            return dp[start];
        };

        int answer = -1;
        for (int i = 1; i <= n; ++i) {
            if (weight[i] <= maxWeight) {
                answer = std::max(answer, DFS(i));
            }
        }
        return answer;
    };

    int left = 0, right = *std::max_element(weight.begin(), weight.end());
    while (left < right) {
        int mid = (left+right) / 2;
        if (hasCycle(mid) || getMaxDist(mid) >= k-1) {
            right = mid;
        } else {
            left = mid+1;
        }
    }

    if (hasCycle(left) || getMaxDist(left) >= k-1) {
        printf("%d", left);
    } else {
        printf("-1");
    }

    return 0;
}