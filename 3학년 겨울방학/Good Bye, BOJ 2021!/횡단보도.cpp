#include <iostream>
#include <vector>
#include <queue>

typedef long long Long;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<std::pair<int, int>>> graph(n+1);
    std::vector<Long> dist(n+1, INT64_MAX/2);

    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].emplace_back(b, i);
        graph[b].emplace_back(a, i);
    }

    std::priority_queue<std::pair<Long, int>, std::vector<std::pair<Long, int>>, std::greater<std::pair<Long, int>>> q;
    q.emplace(0, 1);
    dist[1] = 0;

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();

        for (auto next : graph[curr.second]) {
            Long sigStart = curr.first / m * m + next.second;
            if (sigStart < curr.first) {
                sigStart += m;
            }
            if (sigStart+1 < dist[next.first]) {
                dist[next.first] = sigStart+1;
                q.emplace(sigStart+1, next.first);
            }
        }
    }

    printf("%lld", dist[n]);

    return 0;
}