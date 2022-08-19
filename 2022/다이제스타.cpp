#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, Long>>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        Long w;
        std::cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    auto compare = [](std::pair<int, Long> p, std::pair<int, Long> q) { return p.second < q.second; };
    for (int v = 1; v <= n; ++v) {
        std::sort(graph[v].begin(), graph[v].end(), compare);
    }

    int src, dst;
    std::cin >> src >> dst;

    // dist[현재 정점][이전에 지난 간선의 가중치]
    std::vector<std::map<int, Long>> dist(n+1);
    dist[src][0] = 0;
    std::queue<std::pair<int, Long>> q;
    q.emplace(src, 0);

    while (!q.empty()) {
        auto [curr, prevWeight] = q.front();
        q.pop();

        auto it = std::upper_bound(graph[curr].begin(), graph[curr].end(), std::make_pair(0, prevWeight), compare);
        for (; it != graph[curr].end(); ++it) {
            auto [next, weight] = *it;
            if (dist[next].find(weight) == dist[next].end()) {
                dist[next][weight] = INT64_MAX/2;
            }
            if (dist[curr][prevWeight]+weight < dist[next][weight]) {
                dist[next][weight] = dist[curr][prevWeight]+weight;
                q.emplace(next, weight);
            }
        }
    }

    if (dist[dst].empty()) {
        std::cout << "DIGESTA\n";
    } else {
        Long answer = INT64_MAX;
        for (auto [_, d] : dist[dst]) {
            answer = std::min(answer, d);
        }
        std::cout << answer << "\n";
    }

    return 0;
}