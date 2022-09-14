#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::set<int>> removed(n+1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        removed[u].insert(v);
        removed[v].insert(u);
    }

    std::vector<int> dist(n+1, -1);
    std::vector<int> remaining;
    for (int i = 1; i <= n; ++i) {
        remaining.push_back(i);
    }

    std::queue<std::pair<int, int>> q;
    q.emplace(1, 0);
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        dist[curr.first] = curr.second;
        std::vector<int> disconnected;
        for (int next : remaining) {
            if (next == curr.first) {
                continue;
            } else if (removed[curr.first].find(next) == removed[curr.first].end()) {
                q.emplace(next, curr.second+1);
            } else {
                disconnected.push_back(next);
            }
        }
        remaining = disconnected;
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d\n", dist[i]);
    }

    return 0;
}