#include <iostream>
#include <vector>
#include <functional>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> trash(n+1);
    for (int v = 1; v <= n; ++v) {
        std::cin >> trash[v];
    }

    std::vector<int> parent(n+1, 0);
    std::function<void(int, int)> initParent = [&](int start, int prev) {
        parent[start] = prev;
        for (int next : graph[start]) {
            if (next != prev) {
                initParent(next, start);
            }
        }
    };
    initParent(1, 0);

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(k+1, -1));
    std::function<int(int, int)> collectMaxTrash = [&](int start, int collected) -> int {
        int& result = dp[start][collected];
        if (result != -1) {
            return result;
        }

        int skipCurr = collected;
        int collectCurr;
        if (collected+trash[start] > k) {
            collectCurr = collected;
        } else {
            collectCurr = collected+trash[start];
        }

        result = std::max(skipCurr, collectCurr);
        for (int next : graph[start]) {
            if (next != parent[start]) {
                int cand1 = collectMaxTrash(next, skipCurr);
                int cand2 = collectMaxTrash(next, collectCurr);
                int sub = std::max(cand1, cand2);
                result = std::max(result, sub);
            }
        }
        return result;
    };

    std::cout << collectMaxTrash(1, 0);

    return 0;
}