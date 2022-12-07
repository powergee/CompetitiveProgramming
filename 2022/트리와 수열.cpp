#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using Long = long long;
const Long MOD = 1000000007;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    std::vector<Long> weight(n-1);
    for (int i = 0; i < n-1; ++i) {
        std::cin >> weight[i];
    }
    std::sort(weight.begin(), weight.end(), std::greater<>());

    std::vector<Long> treeSize(n+1, 0);
    std::vector<Long> count(n-1, 0);
    std::function<void(int)> initTreeSize = [&](int start) {
        treeSize[start]++;
        for (auto [next, eid] : graph[start]) {
            if (treeSize[next] == 0) {
                initTreeSize(next);
                treeSize[start] += treeSize[next];
                count[eid] = treeSize[next] * (n-treeSize[next]);
            }
        }
    };
    initTreeSize(1);

    std::sort(count.begin(), count.end());
    Long answer = 0;
    for (int i = 0; i < n-1; ++i) {
        answer += (weight[i] * count[i]) % MOD;
        answer %= MOD;
    }

    std::cout << answer;

    return 0;
}