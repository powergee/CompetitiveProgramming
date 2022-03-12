#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

typedef long long Long;

const Long INF = Long(1e12);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::tuple<int, int, Long>> edges;
    std::vector<std::vector<Long>> dist(n+1, std::vector<Long>(n+1, INF));
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        edges.emplace_back(u, v, c);
        dist[u][v] = c;
        dist[v][u] = c;
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = std::min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }

    int answer = 0;
    for (auto [u, v, c] : edges) {
        int removable = 0;
        for (int k = 1; k <= n; ++k) {
            if (dist[u][k] + dist[k][v] <= dist[u][v]) {
                removable = 1;
            }
        }
        answer += removable;
    }
    printf("%d", answer);

    return 0;
}