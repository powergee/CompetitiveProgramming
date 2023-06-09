#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int dp[30001][3000];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> candy(n + 1, 0);
    std::vector<std::vector<int>> graph(n + 1);

    for (int v = 1; v <= n; ++v) {
        std::cin >> candy[v];
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<bool> visited(n + 1, false);
    std::function<std::pair<int, int>(int)> traverse_comp;
    traverse_comp = [&](int start) -> std::pair<int, int> {
        int size = 1, value = candy[start];
        for (int next : graph[start]) {
            if (!visited[next]) {
                visited[next] = true;
                auto [next_size, next_value] = traverse_comp(next);
                size += next_size;
                value += next_value;
            }
        }
        return {size, value};
    };

    std::vector<std::pair<int, int>> comp;
    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            visited[v] = true;
            comp.emplace_back(traverse_comp(v));
        }
    }

    for (int index = comp.size() - 1; index >= 0; --index) {
        for (int capacity = 0; capacity < std::min(comp[index].first, k);
             ++capacity) {
            dp[index][capacity] = dp[index + 1][capacity];
        }
        for (int capacity = comp[index].first; capacity < k; ++capacity) {
            dp[index][capacity] =
                std::max(dp[index + 1][capacity],
                         dp[index + 1][capacity - comp[index].first] +
                             comp[index].second);
        }
    }
    std::cout << dp[0][k - 1] << "\n";

    return 0;
}