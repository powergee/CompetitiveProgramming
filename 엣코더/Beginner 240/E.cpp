#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> tree(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    std::vector<bool> visited(n+1, false);
    std::vector<std::pair<int, int>> ranges(n+1);
    int globalCount = 0;
    std::function<std::pair<int, int>(int)> findLeaves = [&](int start) -> std::pair<int, int> {
        visited[start] = true;

        int left = INT32_MAX, right = INT32_MIN;
        for (int next : tree[start]) {
            if (!visited[next]) {
                auto range = findLeaves(next);
                left = std::min(left, range.first);
                right = std::max(right, range.second);
            }
        }

        if (right < left) {
            globalCount++;
            return ranges[start] = { globalCount, globalCount };
        } else {
            return ranges[start] = { left, right };
        }
    };
    findLeaves(1);

    for (int i = 1; i <= n; ++i) {
        printf("%d %d\n", ranges[i].first, ranges[i].second);
    }

    return 0;
}