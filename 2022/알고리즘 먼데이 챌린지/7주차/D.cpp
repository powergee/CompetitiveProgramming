#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<int> value(n+1);
    for (int v = 1; v <= n; ++v) {
        std::cin >> value[v];
    }

    std::vector<std::vector<std::pair<int, Long>>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    std::vector<std::vector<Long>> dist(n+1, std::vector<Long>(10, INT64_MAX));
    std::priority_queue<std::tuple<Long, int, int>> q;

    for (auto [next, cost] : graph[1]) {
        dist[next][1 % value[next]] = cost;
        q.emplace(-cost, next, 1 % value[next]);
    }

    Long answer = INT64_MAX;
    while (q.size()) {
        auto [distState, curr, prevMod] = q.top();
        q.pop();
        distState = -distState;

        if (curr == n) {
            answer = std::min(answer, distState);
        }
        if (distState > dist[curr][prevMod]) {
            continue;
        }
        for (auto [next, cost] : graph[curr]) {
            Long newDist = dist[curr][prevMod] + cost;
            int nextMod = next % value[curr];
            int currMod = curr % value[next];
            if (prevMod == nextMod && dist[next][currMod] > newDist) {
                dist[next][currMod] = newDist;
                q.emplace(-newDist, next, currMod);
            }
        }
    }

    if (answer == INT64_MAX) {
        std::cout << "-1";
    } else {
        std::cout << answer;
    }

    return 0;
}