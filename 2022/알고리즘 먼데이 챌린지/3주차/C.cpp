#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::queue<int> q;
    std::vector<int> dist(n+1, INT32_MAX);
    
    q.push(1);
    dist[1] = 0;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr]) {
            if (dist[next] == INT32_MAX) {
                dist[next] = dist[curr]+1;
                q.push(next);
            }
        }
    }

    std::cout << (dist[n] <= k ? "YES" : "NO");

    return 0;
}