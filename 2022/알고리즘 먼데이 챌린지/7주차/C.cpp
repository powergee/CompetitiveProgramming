#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    std::cin >> n >> m >> k;
    
    using Edge = std::pair<int, int>;
    std::vector<Edge> edges(m);
    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges[i] = { u, v };
        graph[u].push_back(i);
    }

    std::vector<bool> used(m, false);
    std::vector<int> dist(m, INT32_MAX);
    std::queue<int> q;
    for (int eid : graph[k]) {
        used[eid] = true;
        dist[eid] = 1;
        q.push(eid);
    }

    while (!q.empty()) {
        int currEid = q.front();
        q.pop();
        int curr = edges[currEid].second;
        
        for (int nextEid : graph[curr]) {
            if (!used[nextEid]) {
                used[nextEid] = true;
                dist[nextEid] = dist[currEid] + 1;
                q.push(nextEid);
            }
        }
    }

    int answer = INT32_MAX;
    for (int eid = 0; eid < m; ++eid) {
        auto [_, end] = edges[eid];
        if (end == k) {
            answer = std::min(answer, dist[eid]);
        }
    }

    if (answer == INT32_MAX) {
        std::cout << -1;
    } else {
        std::cout << answer;
    }

    return 0;
}