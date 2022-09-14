#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> height(n+1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> height[i];
    }

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> prereq = height;
    std::function<bool(int, int)> findAnswer = [&](int curr, int parent) -> bool {
        prereq[curr] = 2*prereq[parent] - height[curr];
        if (prereq[curr] > 1000000) {
            return false;
        }
        for (int next : graph[curr]) {
            if (next == parent) { continue; }
            if (prereq[curr] <= height[next] || findAnswer(next, curr)) {
                return true;
            }
        }
        return false;
    };

    std::cout << (findAnswer(k, k) ? "1" : "0");

    return 0;
}