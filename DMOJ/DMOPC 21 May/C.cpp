#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto getDistanceVector = [&](int start) -> std::vector<int> {
        std::queue<std::pair<int, int>> q;
        q.emplace(start, 0);
        std::vector<int> result(n+1, -1);
        result[start] = 0;

        while (!q.empty()) {
            auto [curr, dist] = q.front();
            q.pop();
            
            for (int next : graph[curr]) {
                if (result[next] == -1) {
                    q.emplace(next, dist+1);
                    result[next] = dist+1;
                }
            }
        }
        return result;
    };

    std::vector<std::vector<int>> dist(n+1);
    for (int i = 1; i <= n; ++i) {
        dist[i] = getDistanceVector(i);
    }

    int q;
    scanf("%d", &q);

    while (q--) {
        int s, t, x, u, v, y;
        scanf("%d %d %d %d %d %d", &s, &t, &x, &u, &v, &y);
        bool yes = true;
        if (dist[s][t] <= x || dist[u][v] <= y) {
            yes = true;
        } else {
            yes = (dist[s][u] + dist[t][v] + 2 <= x + y) || 
                  (dist[s][v] + dist[t][u] + 2 <= x + y);
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}