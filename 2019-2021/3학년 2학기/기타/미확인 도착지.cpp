#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using Heap = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>;
using Graph = std::vector<std::vector<std::pair<int, int>>>;

bool areSameEdge(int u1, int v1, int u2, int v2) {
    if (u1 > v1) {
        std::swap(u1, v1);
    }
    if (u2 > v2) {
        std::swap(u2, v2);
    }
    return u1 == u2 && v1 == v2;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, t;
        scanf("%d %d %d", &n, &m, &t);
        int s, g, h, ghDist;
        scanf("%d %d %d", &s, &g, &h);

        Graph graph(n+1);
        for (int i = 0; i < m; ++i) {
            int a, b, d;
            scanf("%d %d %d", &a, &b, &d);
            graph[a].emplace_back(b, d);
            graph[b].emplace_back(a, d);
            if (areSameEdge(a, b, g, h)) {
                ghDist = d;
            }
        }

        auto getDistVector = [&](int start) -> std::vector<int> {
            std::vector<int> dist(n+1, INT32_MAX/2);
            dist[start] = 0;
            Heap q;
            q.emplace(0, start);

            while (!q.empty()) {
                auto curr = q.top();
                q.pop();
                for (auto edge : graph[curr.second]) {
                    int newDist = edge.second + curr.first;
                    if (newDist < dist[edge.first]) {
                        dist[edge.first] = newDist;
                        q.emplace(newDist, edge.first);
                    }
                }
            }
            return dist;
        };

        auto fromS = getDistVector(s);
        auto fromG = getDistVector(g);
        auto fromH = getDistVector(h);

        std::vector<int> queries(t);
        for (int i = 0; i < t; ++i) {
            scanf("%d", &queries[i]);
        }
        std::sort(queries.begin(), queries.end());

        for (int q : queries) {
            if (fromS[q] == std::min(fromS[g]+ghDist+fromH[q], fromS[h]+ghDist+fromG[q])) {
                printf("%d ", q);
            }
        }
        printf("\n");
    }

    return 0;
}